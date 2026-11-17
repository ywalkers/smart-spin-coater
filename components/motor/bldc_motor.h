/*
 * @Author: ywalkers 2078500453@qq.com
 * @Date: 2026-09-17 17:28:48
 * @LastEditors: ywalkers 2078500453@qq.com
 * @LastEditTime: 2026-09-19 22:44:40
 * @FilePath: \WIFI_STUDY\components\motor\bldc_motor.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef __BLDC_MOTOR_H__
#define __BLDC_MOTOR_H__

#include <stdint.h>
#include "esp_err.h"

#define MOTOR_PWM_PIN       41     // 蓝线：PWM 控制引脚
#define MOTOR_FG_PIN        40      // 黄线：FG 测速反馈引脚

#define MOTOR_PWM_FREQ      10000   // PWM 频率 10kHz
#define MOTOR_FG_PPR        9       // 电机每转一圈输出的脉冲数 (Pulses Per Revolution)
#define MOTOR_TASK_PERIOD   50      // 闭环控制周期，单位：毫秒 (50ms 算一次 PID)

/* ---------------- M/T 测速参数 ---------------- */
// FG 边沿消抖：间隔小于该值的重复边沿视为毛刺（6000RPM 时脉冲间隔约 1111us）
#define MOTOR_FG_MIN_INTERVAL_US  100
// 超过该时长没有任何新脉冲，判定为停转（对应 <8.3 RPM）
#define MOTOR_RPM_TIMEOUT_US      800000

typedef struct {
    float kp;               // 比例系数
    float ki;               // 积分系数
    float kd;               // 微分系数
    float target_rpm;       // 目标转速
    float current_rpm;      // 当前真实转速
    float error_sum;        // 误差积分累计
    float last_error;       // 上一次的误差 (用于算微分)
    float last_rpm;         // 这是为了“微分先行”
    uint32_t current_pwm;   // 当前输出的 PWM 占空比 (0-1023)
} motor_pid_t;

/**
 * @brief 初始化电机硬件 (LEDC, PCNT) 并创建 FreeRTOS 控制任务
 */
void motor_init(void);

/**
 * @brief 设置电机的目标转速 (供 LVGL 界面滑动条/按钮调用)
 * @param rpm 目标转速，设为 0 时电机完全停止
 */
void motor_set_target_rpm(float rpm);

/**
 * @brief 获取当前实际转速 (供 LVGL 界面实时显示)
 * @return 实时 RPM 值
 */
float motor_get_current_rpm(void);

/* ===================== 电机异常检测 ===================== */

// 故障检测阈值
#define STALL_PWM_THRESHOLD   600       // PWM 占空比 > 600/1023 视为"大力输出"
#define STALL_RPM_RATIO       0.10f     // 转速低于目标 10% 视为"没转起来"
#define STALL_DETECT_CYCLES   20        // 连续 20 个周期(50ms*20=1s)判定堵转
#define OVERSPEED_RATIO       1.20f     // 转速超过目标 120% 判定超速
#define MOTOR_MAX_RPM         6000.0f   // 绝对转速上限(超出即超速)

// 电机故障码
typedef enum {
    MOTOR_OK = 0,           // 正常
    MOTOR_ERR_STALL,        // 堵转/失速(大力输出但转速起不来)
    MOTOR_ERR_OVERSPEED,    // 超速/飞车(PID 失控)
} motor_err_t;

/**
 * @brief 查询电机当前故障状态
 * @return motor_err_t 故障码，MOTOR_OK 表示正常
 */
motor_err_t motor_get_error(void);

/**
 * @brief 清除电机故障(致命故障后需人工确认再重启)
 */
void motor_clear_error(void);

#endif
