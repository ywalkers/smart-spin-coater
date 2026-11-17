/*
* Copyright 2023 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/


/*********************
 *      INCLUDES
 *********************/
#include <stdio.h>
#include "lvgl.h"
#include "custom.h"

/*********************
 *      DEFINES
 *********************/
int g_current_step = 1;
char current_process_name[64] = "请选择";
char temp_selected_name[64] = "";
char current_recipe_file[32] = ""; // 默认空
char current_recipe_name[32] = ""; // 初始为空
// 实例化全局变量
SpinProcess_t spin_process = {0}; 
lv_timer_t * spin_timer = NULL;

int current_realtime_rpm = 0;
int timer_tick_count = 0; 
lv_timer_t * running_timer = NULL;


void spin_timer_callback(lv_timer_t * timer) {
    // 已切离首页时，screen 的控件已被 ui_load_scr_animation 删除，
    // 继续访问 screen_label_13 / screen_arc_1 会踩悬空指针导致崩溃重启。
    // 这里直接停止流程并让电机停车。
    if (lv_disp_get_scr_act(NULL) != guider_ui.screen) {
        spin_process.is_running = false;
        spin_process.is_decelerating = false;
        spin_process.current_realtime_rpm = 0.0f;
        if (spin_timer != NULL) {
            lv_timer_pause(spin_timer);
        }
        return;
    }

    if (!spin_process.is_running) return;

    uint32_t current_tick = lv_tick_get();
    int step_idx = spin_process.current_step;
    int target_duration = spin_process.step[step_idx].duration_s;
    int current_accel = spin_process.step[step_idx].accel;
    
    // 如果加速度是 0，强行给一个大数值，防止卡死！
    if (current_accel <= 0) {
        current_accel = 2000; // 默认 2000 RPM/S 的加减速度
        printf("Warning: Acceleration is 0, using default 2000 RPM/S\n");
    }

    // 每 100ms 速度变化步长
    float rpm_step = current_accel * 0.1f;
    int remaining_s = 0;
    int target_rpm = 0;

    // ----------------- 1. 时间与阶段目标转速判断 -----------------
    if (!spin_process.is_decelerating) {
        // 正常工艺运行计时中
        uint32_t elapsed_s = (current_tick - spin_process.step_start_tick) / 1000;
        
        if (elapsed_s < target_duration) {
            remaining_s = target_duration - elapsed_s;
            target_rpm = spin_process.step[step_idx].rpm; // 目标为设定转速
        } else {
            // 时间到 进入减速缓冲期
            remaining_s = 0;
            target_rpm = 0; // 目标转为 0，开始平滑降速
            spin_process.is_decelerating = true;
            printf("Time's up! Starting deceleration...\n");
        }
    } else {
        // 处于减速缓冲期：时间保持为 0，目标转速为 0
        remaining_s = 0;
        target_rpm = 0;
    }

    // ----------------- 2. 爬坡与减速算法 (加/减速斜率控制) -----------------
    if (spin_process.current_realtime_rpm < target_rpm) {
        spin_process.current_realtime_rpm += rpm_step;
        if (spin_process.current_realtime_rpm > target_rpm) {
            spin_process.current_realtime_rpm = target_rpm;
        }
    } else if (spin_process.current_realtime_rpm > target_rpm) {
        spin_process.current_realtime_rpm -= rpm_step;
        if (spin_process.current_realtime_rpm < target_rpm) {
            spin_process.current_realtime_rpm = target_rpm;
        }
    }

    int display_rpm = (int)spin_process.current_realtime_rpm;

    // ----------------- 3. 刷新 UI 控件 -----------------
    if (guider_ui.screen_label_13) {
        lv_label_set_text_fmt(guider_ui.screen_label_13, "%d", remaining_s);
    }
    if (guider_ui.screen_label_12) {
        lv_label_set_text_fmt(guider_ui.screen_label_12, "%d", display_rpm);
    }
    if (guider_ui.screen_arc_1) {
        lv_arc_set_value(guider_ui.screen_arc_1, display_rpm);
    }

    // ----------------- 4. 减速完成后的换挡与结束判断 -----------------
    // 必须同时满足：处于减速期，且实时转速已完全降至 0 (加个缓冲区间 <= 5)
    if (spin_process.is_decelerating && display_rpm <= 5) {
        spin_process.current_realtime_rpm = 0.0f; // 彻底清零

        if (step_idx == 0 && spin_process.process_mode == 2) {
            // 多步旋涂：第一段完全刹停！准备切入第二段
            spin_process.current_step = 1;
            spin_process.is_decelerating = false;           // 退出减速期
            spin_process.step_start_tick = current_tick;     // 第二阶段重新起算时间
            printf("Step 1 fully stopped. Ramping up to Step 2!\n");
        } else {
            // 单步完成，或多步第二段完全刹停：工艺全部结束
            printf("Process fully completed!\n");
            stop_spin_process();
        }
    }
}

// 提供一个启动函数的接口
void start_spin_process(void) {
    if (!spin_process.is_running) {
        spin_process.current_step = 0;
        spin_process.is_decelerating = false;
        spin_process.is_running = true;
        spin_process.current_realtime_rpm = 0.0f;
        spin_process.step_start_tick = lv_tick_get();
        
        if (spin_timer == NULL) {
            // 第一次点击：创建定时器
            spin_timer = lv_timer_create(spin_timer_callback, 100, NULL);
        } else {
            // 后续点击：唤醒已经存在的定时器
            lv_timer_resume(spin_timer);
        }
    }
}

void stop_spin_process(void) {
    if (spin_process.is_running) {
        spin_process.is_running = false;
        spin_process.is_decelerating = false;
        spin_process.current_realtime_rpm = 0.0f;
        
        // 暂停定时器
        if (spin_timer != NULL) {
            lv_timer_pause(spin_timer); 
        }

        // 把文字清零
        if (guider_ui.screen_label_13) lv_label_set_text(guider_ui.screen_label_13, "00.00");
        if (guider_ui.screen_label_12) lv_label_set_text(guider_ui.screen_label_12, "0000");

        if (guider_ui.screen_arc_1) lv_arc_set_value(guider_ui.screen_arc_1, 0);
        spin_process.current_realtime_rpm = 0;
        lv_obj_clear_state(guider_ui.screen_btn_3, LV_STATE_CHECKED);
        lv_led_set_color(guider_ui.screen_led_1, lv_color_make(0x00, 0xa1, 0xb5));
    }
}

void save_recipe_to_sd(void) {
    if (current_recipe_file[0] == '\0') {
        printf("Error: No recipe selected!\n");
        return;
    }
    // 打开文件进行写入 (wb: 写入二进制文件)
    // 移植到 ESP32 时，路径改成类似 "/sdcard/%s", current_recipe_file
    FILE *fp = fopen(current_recipe_file, "wb"); 
    if (fp != NULL) {
        // 直接把整个 spin_process 结构体像盖印章一样写进文件！
        fwrite(&spin_process, sizeof(SpinProcess_t), 1, fp);
        fclose(fp);
        printf("Success: Saved to %s\n", current_recipe_file);
    } else {
        printf("Error: Cannot open file for writing!\n");
    }
}

void load_recipe_from_sd(void) {
    if (current_recipe_file[0] == '\0') {
        printf("Error: No recipe selected!\n");
        return;
    }

    // 打开文件进行读取 (rb: 读取二进制文件)
    FILE *fp = fopen(current_recipe_file, "rb");
    if (fp != NULL) {
        // 直接把文件内容覆盖到 spin_process 结构体中
        fread(&spin_process, sizeof(SpinProcess_t), 1, fp);
        fclose(fp);
        printf("Success: Loaded from %s\n", current_recipe_file);
        
        
        spin_process.is_running = false; 
        spin_process.is_decelerating = false;
        spin_process.current_realtime_rpm = 0.0f;
    } else {
        printf("Error: Recipe file %s not found!\n", current_recipe_file);
        
    }
}

void load_preset_recipe(void) {
    // 确保机器处于停止状态，才能加载新配方
    spin_process.is_running = false; 
    spin_process.is_decelerating = false;
    spin_process.current_realtime_rpm = 0.0f;

    // 1. 预设 NiOx 参数 (假设为单步：3000转，30秒)
    if (strcmp(current_recipe_name, "NiOx") == 0) {
        spin_process.process_mode = 1; // 明确指定为单步
        
        spin_process.step[0].rpm = 2500;
        spin_process.step[0].duration_s = 30;
        spin_process.step[0].accel = 1500;
        
        // 清空第二段残留
        spin_process.step[1].rpm = 0;
        spin_process.step[1].duration_s = 0;
        spin_process.step[1].accel = 0;
        printf("Loaded Preset: NiOx\n");
    }
    // 2. 预设 SAM (自组装单分子层) (假设单步：4000转，20秒)
    else if (strcmp(current_recipe_name, "SAM") == 0) {
        spin_process.process_mode = 1;
        spin_process.step[0].rpm = 3000;
        spin_process.step[0].duration_s = 30;
        spin_process.step[0].accel = 1500;
        spin_process.step[1].rpm = 0;
        spin_process.step[1].duration_s = 0;
        spin_process.step[1].accel = 0;
        printf("Loaded Preset: SAM\n");
    }
    // 3. 预设 Perovskite (钙钛矿层) (假设为多步：低速铺胶 + 高速反溶剂萃取)
    else if (strcmp(current_recipe_name, "Perovskite") == 0) {
        spin_process.process_mode = 2; // 明确指定为多步！
        
        // 第一段：低速 1000转，10秒
        spin_process.step[0].rpm = 1000;
        spin_process.step[0].duration_s = 10;
        spin_process.step[0].accel = 1000;
        
        // 第二段：高速 4000转，30秒
        spin_process.step[1].rpm = 4000;
        spin_process.step[1].duration_s = 30;
        spin_process.step[1].accel = 2000;
        printf("Loaded Preset: Perovskite\n");
    }
    // 4. 预设 PCBM (电子传输层)
    else if (strcmp(current_recipe_name, "PCBM") == 0) {
        spin_process.process_mode = 1;
        spin_process.step[0].rpm = 3000;
        spin_process.step[0].duration_s = 30;
        spin_process.step[0].accel = 500;
        spin_process.step[1].rpm = 0;
        spin_process.step[1].duration_s = 0;
        spin_process.step[1].accel = 0;
        printf("Loaded Preset: PCBM\n");
    }
}
/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/

/**
 * Create a demo application
 */
// 定义UI刷新回调函数 
void ui_env_update_timer_cb(lv_timer_t * timer) {
    // 确保当前停留在主界面
    if (lv_disp_get_scr_act(NULL) == guider_ui.screen) {
        
        
        static int last_temp = -999;
        static int last_hum = -999;

        // 1. 温度：只更新数值 label（screen_label_4，原 "25℃"），保持原格式
        if (g_current_temp != last_temp) {
            if (guider_ui.screen_label_4) {
                lv_label_set_text_fmt(guider_ui.screen_label_4, "%d℃", g_current_temp);
            }
            last_temp = g_current_temp; // 更新记忆
        }

        // 2. 湿度：只更新数值 label（screen_label_6，原 "45%"），保持原格式
        if (g_current_hum != last_hum) {
            if (guider_ui.screen_label_6) {
                lv_label_set_text_fmt(guider_ui.screen_label_6, "%d%%", g_current_hum);
            }
            last_hum = g_current_hum; // 更新记忆
        }
    }
}

void custom_init(lv_ui *ui)
{
    /* Add your codes here */
    lv_timer_create(ui_env_update_timer_cb, 1000, NULL);
}

