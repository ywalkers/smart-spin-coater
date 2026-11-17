/*
* Copyright 2023 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#ifndef __CUSTOM_H_
#define __CUSTOM_H_

#include "lvgl.h"

#ifdef __cplusplus
extern "C" {
#endif
extern void stop_spin_process(void);
// 声明我们要写的两个文件读写函数
void save_recipe_to_sd(void);
void load_recipe_from_sd(void);
// 记录当前选中的配方文件名
extern char current_recipe_file[32];
extern char current_recipe_name[32];

// 用于存储最新读取到的温湿度
extern int g_current_temp;
extern int g_current_hum;

// 声明定时器回调函数
void spin_animation_timer_cb(lv_timer_t * timer);
#include "gui_guider.h"

void custom_init(lv_ui *ui);

/* 1. 定义单步旋涂的参数结构 */
typedef struct {
    int rpm;          // 目标转速
    int duration_s;   // 持续时间 (秒)
    int accel;
} SpinStep_t;

/* 2. 定义整个工艺流程和状态 */
typedef struct {
    SpinStep_t step[2];       // 两步工艺 (下标0是第一段，1是第二段)
    int current_step;         // 当前正在执行哪一步 (0 或 1)
    bool is_running;          // 机器是否在转
    uint32_t step_start_tick; // 记录当前步开始的系统时间
    float current_realtime_rpm;      
    bool is_decelerating;      //标记当前阶段时间已到，正在降速缓冲至0        
    int process_mode;           // 0 = 未设置, 1 = 单步模式, 2 = 多步模式
} SpinProcess_t;

extern SpinProcess_t spin_process;
extern lv_timer_t * spin_timer;
void stop_spin_process(void);
void start_spin_process(void);
void spin_timer_callback(lv_timer_t * timer);

void save_recipe_to_sd(void);
void load_preset_recipe(void);
#ifdef __cplusplus
}
#endif
#endif /* EVENT_CB_H_ */
