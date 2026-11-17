#include "bldc_motor.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/ledc.h"
#include "driver/gpio.h"
#include "esp_timer.h"
#include "esp_attr.h"
#include "esp_log.h"
#include "esp_task_wdt.h"
#include "custom.h"

#define DEADZONE_RPM 15.0f  //死区

static const char *TAG = "MOTOR_CTRL";

/* ================= M/T 测速（GPIO 边沿时间戳） =================
 * ISR 单写者：累加边沿数 + 记录最后一个边沿的 μs 时间戳；
 * 控制任务每 MOTOR_TASK_PERIOD 做一次差，得到 "Δn 个脉冲 / Δt 时间"。
 * 因为时间窗与脉冲边界对齐，不存在 M 法那种 ±1 脉冲的量化误差。
 */
static volatile uint32_t s_edge_total = 0;   // 累计上升沿数（单调递增，无回绕）
static volatile int64_t  s_last_ts    = 0;   // 最后一个有效边沿的 μs 时间戳
static portMUX_TYPE      s_ts_mux     = portMUX_INITIALIZER_UNLOCKED;


static motor_pid_t pid_ctrl = {
    .kp = 0.2f,    
    .ki = 0.005f, 
    .kd = 0.00f,
    .target_rpm = 0.0f,
    .current_rpm = 0.0f,
    .error_sum = 0.0f,
    .last_error = 0.0f,
    .last_rpm = 0.0f,   // 初始化
    .current_pwm = 0
};

// 电机故障状态与堵转检测计数
static motor_err_t motor_err = MOTOR_OK;
static int stall_cnt = 0;

// 初始化 PWM
static void _motor_pwm_init(void) {
    ledc_timer_config_t ledc_timer = {
        .speed_mode       = LEDC_LOW_SPEED_MODE,
        .timer_num        = LEDC_TIMER_0,
        .duty_resolution  = LEDC_TIMER_10_BIT, // 10位分辨率 (0-1023)
        .freq_hz          = MOTOR_PWM_FREQ,  
        .clk_cfg          = LEDC_AUTO_CLK
    };
    ledc_timer_config(&ledc_timer);
    ledc_channel_config_t ledc_channel = {
        .speed_mode     = LEDC_LOW_SPEED_MODE,
        .channel        = LEDC_CHANNEL_0,
        .timer_sel      = LEDC_TIMER_0,
        .intr_type      = LEDC_INTR_DISABLE,
        .gpio_num       = MOTOR_PWM_PIN,
        .duty           = 0,
        .hpoint         = 0
    };
    ledc_channel_config(&ledc_channel);
    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, 0);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
}
// FG 上升沿中断：记录时间戳 + 累加脉冲数
static void IRAM_ATTR motor_fg_isr(void *arg) {
    static int64_t last_ts = 0;          // 仅本 ISR 访问，用于毛刺过滤
    int64_t now = esp_timer_get_time();  // 微秒级，可在 ISR 中调用
    if (now - last_ts < MOTOR_FG_MIN_INTERVAL_US) {
        return;                          // 间隔过短，判为抖动毛刺
    }
    last_ts      = now;
    s_last_ts    = now;
    s_edge_total++;
}

// 初始化 FG 测速引脚（GPIO 中断）
static void _motor_fg_init(void) {
    gpio_config_t cfg = {
        .pin_bit_mask = 1ULL << MOTOR_FG_PIN,
        .mode         = GPIO_MODE_INPUT,
        .pull_up_en   = GPIO_PULLUP_ENABLE,   // 黄线必须上拉，否则读不到信号
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type    = GPIO_INTR_POSEDGE,
    };
    gpio_config(&cfg);

    // 触摸屏驱动可能已安装过 ISR service，重复安装返回 INVALID_STATE，忽略即可
    esp_err_t err = gpio_install_isr_service(0);
    if (err != ESP_OK && err != ESP_ERR_INVALID_STATE) {
        ESP_LOGE(TAG, "gpio_install_isr_service failed: %s", esp_err_to_name(err));
    }
    gpio_isr_handler_add(MOTOR_FG_PIN, motor_fg_isr, NULL);
}

/* M/T 测速：Δn 个脉冲周期对应 Δt 微秒
 * 高速 → Δn 大，测量偏向计数（M 法特性）
 * 低速 → Δn 小，但 Δt 由 μs 定时器测得，偏向测周（T 法特性）
 * 同一个公式自动完成过渡。
 */
static float motor_measure_rpm(void) {
    static uint32_t prev_cnt       = 0;
    static int64_t  prev_ts        = 0;
    static int64_t  last_update_us = 0;
    static float    rpm            = 0.0f;

    uint32_t cnt;
    int64_t  ts;
    portENTER_CRITICAL(&s_ts_mux);
    cnt = s_edge_total;
    ts  = s_last_ts;
    portEXIT_CRITICAL(&s_ts_mux);

    uint32_t dn = cnt - prev_cnt;   // 本周期新增的脉冲数
    int64_t  dt = ts  - prev_ts;    // 与这些脉冲对应的时间跨度(μs)

    if (dn >= 1 && dt > 0) {
        // rpm = 60 / (PPR * 单周期秒数) = 60 * dn * 1e6 / (PPR * dt)
        rpm = 60.0f * (float)dn * 1e6f / ((float)MOTOR_FG_PPR * (float)dt);
        prev_cnt       = cnt;
        prev_ts        = ts;
        last_update_us = esp_timer_get_time();
    } else if (esp_timer_get_time() - last_update_us > MOTOR_RPM_TIMEOUT_US) {
        // 长时间无新脉冲：转速低于可测下限，判定停止
        rpm      = 0.0f;
        prev_cnt = cnt;
        prev_ts  = ts;
    }
    return rpm;
}
// 电机紧急停机：致命故障(堵转/超速)时立即停转 + 停工艺 + 锁存故障，需 motor_clear_error() 手动恢复
static void motor_emergency_stop(void) {
    pid_ctrl.target_rpm = 0.0f;
    pid_ctrl.error_sum = 0.0f;
    pid_ctrl.current_pwm = 0;
    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, 0);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
    stop_spin_process();   // 停掉旋涂工艺，同步清零 UI 目标转速与显示
    ESP_LOGE(TAG, "MOTOR EMERGENCY STOP! error=%d", (int)motor_err);
}

// FreeRTOS任务：电机PID控制
static void motor_pid_task(void *arg) {
    static float filtered_rpm = 0.0f;
    TickType_t last_wake = xTaskGetTickCount();   // 锁定固定控制周期

    // 加入任务看门狗：本任务卡死超过 5s 未喂狗则整机复位，防止电机飞车
    esp_task_wdt_add(NULL);

    while(1) {
        esp_task_wdt_reset();   // 每周期喂狗

        // 故障锁存：致命故障后强制停机，直到用户 motor_clear_error() 手动恢复
        if (motor_err != MOTOR_OK) {
            pid_ctrl.current_pwm = 0;
            ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, 0);
            ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
            vTaskDelayUntil(&last_wake, pdMS_TO_TICKS(MOTOR_TASK_PERIOD));
            continue;
        }

        // 1. 获取转速（M/T 法，分辨率约 1 RPM，取代原来的 133 RPM 计数法）
        float raw_rpm = motor_measure_rpm();
        // 反馈本身已较干净，低通系数可取大一些以减小相位滞后
        filtered_rpm = (0.7f * filtered_rpm) + (0.3f * raw_rpm);
        pid_ctrl.current_rpm = filtered_rpm;
        // 获取外部设定的目标转速
        pid_ctrl.target_rpm = spin_process.current_realtime_rpm;
        // 2. PID 核心逻辑分支
        float error = pid_ctrl.target_rpm - pid_ctrl.current_rpm;
        
        // 优先判断是否需要停车
        if (pid_ctrl.target_rpm == 0.0f) {
            pid_ctrl.error_sum = 0.0f; // 清空历史积分
            pid_ctrl.current_pwm = 0;  // 直接刹车
        } 
        else {
            // 评估死区与积分冻结
            if (error > -DEADZONE_RPM && error < DEADZONE_RPM) {
                error = 0.0f; 
                // 冻结积分：此处不累加 error_sum
            } else {
                pid_ctrl.error_sum += error;    
            }

            //  微分先行
            float d_current = pid_ctrl.current_rpm - pid_ctrl.last_rpm;

            // 计算理论输出 
            float theoretical_output = (pid_ctrl.kp * error) + 
                                       (pid_ctrl.ki * pid_ctrl.error_sum) - 
                                       (pid_ctrl.kd * d_current);

            // 物理限幅
            float actual_output = theoretical_output;
            if(actual_output > 1023.0f) {
                actual_output = 1023.0f;
            } else if (actual_output < 0.0f) {
                actual_output = 0.0f;
            }
            
            // 反向计算抗饱和
            float excess = actual_output - theoretical_output;
            float kb = 0.5f; 
            pid_ctrl.error_sum += (excess * kb);
            
            pid_ctrl.current_pwm = (int)actual_output;
        }
        // 3. 更新历史状态供下一周期使用
        pid_ctrl.last_error = error;
        pid_ctrl.last_rpm = pid_ctrl.current_rpm;

        // 3.5 电机异常检测(在输出 PWM 前执行，检测到致命故障则锁存并停机)
        if (pid_ctrl.target_rpm > 0.0f) {
            // 堵转/失速：大力输出但转速远低于目标
            if (pid_ctrl.current_pwm >= STALL_PWM_THRESHOLD &&
                pid_ctrl.current_rpm < pid_ctrl.target_rpm * STALL_RPM_RATIO) {
                stall_cnt++;
                if (stall_cnt >= STALL_DETECT_CYCLES) {
                    motor_err = MOTOR_ERR_STALL;
                    motor_emergency_stop();
                }
            } else {
                stall_cnt = 0;
            }

            // 超速/飞车：转速超过目标 120% 或绝对上限
            if (pid_ctrl.current_rpm > pid_ctrl.target_rpm * OVERSPEED_RATIO ||
                pid_ctrl.current_rpm > MOTOR_MAX_RPM) {
                motor_err = MOTOR_ERR_OVERSPEED;
                motor_emergency_stop();
            }
        }

        // 4. 执行输出与延时
        ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, pid_ctrl.current_pwm);
        ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);

        vTaskDelayUntil(&last_wake, pdMS_TO_TICKS(MOTOR_TASK_PERIOD));
    }
}

// 1. 初始化并启动外设与任务
void motor_init(void) {
    ESP_LOGI(TAG, "Initializing Motor Hardware...");
    _motor_pwm_init();
    _motor_fg_init();
    
    // 创建独立任务跑闭环控制
    xTaskCreate(motor_pid_task, "motor_pid_task", 4096, NULL, 5, NULL);
    ESP_LOGI(TAG, "Motor initialized and PID task started.");
}

// 2. 供外部其他文件 (如 UI) 调用的转速设置接口
void motor_set_target_rpm(float rpm) {
    pid_ctrl.target_rpm = rpm;
}

// 3. 供外部读取当前实际转速的接口
float motor_get_current_rpm(void) {
    return pid_ctrl.current_rpm;
}

// 4. 查询电机故障状态(供 UI 显示告警)
motor_err_t motor_get_error(void) {
    return motor_err;
}

// 5. 清除故障(致命故障后需人工确认再重启)
void motor_clear_error(void) {
    motor_err = MOTOR_OK;
    stall_cnt = 0;
    ESP_LOGI(TAG, "Motor error cleared, ready to restart");
}