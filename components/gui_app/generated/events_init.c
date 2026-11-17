/*
* Copyright 2026 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "events_init.h"
#include <stdio.h>
#include "lvgl.h"

#if LV_USE_GUIDER_SIMULATOR && LV_USE_FREEMASTER
#include "freemaster_client.h"
#endif

#include "custom.h"
#include "custom.h"
#include "custom.h"
#include <string.h>
#include "custom.h"
#include <string.h>
#include "custom.h"
#include <string.h>
#include "custom.h"
#include <string.h>
#include "custom.h"
#include <string.h>
#include "custom.h"
#include <string.h>
#include "custom.h"
#include <string.h>
#include "custom.h"

static void screen_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED:
    {
        if (strlen(current_recipe_name) > 0) {
            // 如果已经加载了具体的配方，直接显示配方名！
            lv_label_set_text_fmt(guider_ui.screen_label_2, "当前工艺: %s", current_recipe_name);
        } else {
            if (spin_process.process_mode == 2) {
                lv_label_set_text(guider_ui.screen_label_2, "当前工艺: 多步旋涂");
            } else if (spin_process.process_mode == 1) {
                lv_label_set_text(guider_ui.screen_label_2, "当前工艺: 单步旋涂");
            } else {
                lv_label_set_text(guider_ui.screen_label_2, "当前工艺: 未设置");
            }
        }
        // 刷新剩余时间 Label (格式化为 00.00)
        lv_label_set_text_fmt(guider_ui.screen_label_13, "%02d.00", spin_process.step[0].duration_s);

        // 初始化转速圆环和数字
        lv_arc_set_value(guider_ui.screen_arc_1, 0);
        lv_label_set_text(guider_ui.screen_label_12, "0000");
        // 假设你的两个灯分别叫 screen_led_start 和 screen_led_vacuum
        lv_led_set_color(guider_ui.screen_led_1, lv_color_make(0x00, 0xa1, 0xb5));
        lv_led_set_color(guider_ui.screen_led_2, lv_color_make(0x00, 0xa1, 0xb5));

        // 如果希望初始状态是亮着的青蓝色：
        lv_led_on(guider_ui.screen_led_1);
        lv_led_on(guider_ui.screen_led_1);
        break;
    }
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch(dir) {
        case LV_DIR_LEFT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.screen1, guider_ui.screen1_del, &guider_ui.screen_del, setup_scr_screen1, LV_SCR_LOAD_ANIM_MOVE_LEFT, 200, 0, false, true);
            break;
        }
        case LV_DIR_RIGHT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.screen3, guider_ui.screen3_del, &guider_ui.screen_del, setup_scr_screen3, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 200, 0, false, true);
            break;
        }
        default:
            break;
        }
        break;
    }
    default:
        break;
    }
}

static void screen_btn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen2, guider_ui.screen2_del, &guider_ui.screen_del, setup_scr_screen2, LV_SCR_LOAD_ANIM_NONE, 200, 0, false, true);
        break;
    }
    default:
        break;
    }
}

static void screen_btn_2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_LONG_PRESSED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_1, guider_ui.screen_1_del, &guider_ui.screen_del, setup_scr_screen_1, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, false, true);
        break;
    }
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_1, guider_ui.screen_1_del, &guider_ui.screen_del, setup_scr_screen_1, LV_SCR_LOAD_ANIM_NONE, 200, 0, false, true);
        break;
    }
    default:
        break;
    }
}

static void screen_btn_3_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED:
    {

        extern void start_spin_process(void);

        //核心逻辑判断
        if(lv_obj_has_state(guider_ui.screen_btn_3, LV_STATE_CHECKED)) {
            // 如果真空按钮也是按下的状态（允许启动）
            if(lv_obj_has_state(guider_ui.screen_btn_4, LV_STATE_CHECKED)) {

                // 亮红灯
                lv_led_set_color(guider_ui.screen_led_1, lv_color_make(0xff, 0x00, 0x00));

                // 直接调用启动函数
                start_spin_process();

            } else {
                // 真空没开，禁止启动
                static const char * btns[] = {"确定", ""};
                lv_obj_t * mbox = lv_msgbox_create(guider_ui.screen, "警告", "请先开启真空！", btns, true);
                lv_obj_center(mbox);

                // 强制替换中文字体
                lv_obj_set_style_text_font(mbox, &lv_font_myfont_16, 0);
                lv_obj_set_style_text_font(lv_msgbox_get_title(mbox), &lv_font_myfont_16, 0);
                lv_obj_set_style_text_font(lv_msgbox_get_text(mbox), &lv_font_myfont_16, 0);
                lv_obj_set_style_text_font(lv_msgbox_get_btns(mbox), &lv_font_myfont_16, 0);

                // 把开始按钮强行弹起来
                lv_obj_clear_state(guider_ui.screen_btn_3, LV_STATE_CHECKED);
            }

        } else {
            // 再次点击开始按钮（试图停止），恢复指示灯默认颜色
            lv_led_set_color(guider_ui.screen_led_1, lv_color_make(0x00, 0xa1, 0xb5));
            stop_spin_process();
           
        }
        break;
    }
    default:
        break;
    }
}

static void screen_btn_4_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_VALUE_CHANGED:
    {
        // 判断按钮是否处于凹陷（打开）状态
        if(lv_obj_has_state(guider_ui.screen_btn_4, LV_STATE_CHECKED)) {
            // 1. 设置LED为红色
            lv_led_set_color(guider_ui.screen_led_2, lv_color_make(0xff, 0x00, 0x00));
            // 2. 强制点亮它
            lv_led_on(guider_ui.screen_led_2);
        } else {
            // 1. 设置LED
            lv_led_set_color(guider_ui.screen_led_2, lv_color_make(0x00, 0xa1, 0xb5));
            // 2. 强制点亮它
            lv_led_on(guider_ui.screen_led_2);
        }
        break;
    }
    default:
        break;
    }
}

static void screen_btn_5_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen3, guider_ui.screen3_del, &guider_ui.screen_del, setup_scr_screen3, LV_SCR_LOAD_ANIM_NONE, 200, 200, true, true);
        break;
    }
    default:
        break;
    }
}

void events_init_screen (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen, screen_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_btn_1, screen_btn_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_btn_2, screen_btn_2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_btn_3, screen_btn_3_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_btn_4, screen_btn_4_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen_btn_5, screen_btn_5_event_handler, LV_EVENT_ALL, ui);
}

static void screen1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch(dir) {
        case LV_DIR_LEFT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.screen2, guider_ui.screen2_del, &guider_ui.screen1_del, setup_scr_screen2, LV_SCR_LOAD_ANIM_MOVE_LEFT, 200, 0, false, true);
            break;
        }
        case LV_DIR_RIGHT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.screen, guider_ui.screen_del, &guider_ui.screen1_del, setup_scr_screen, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 200, 0, false, true);
            break;
        }
        default:
            break;
        }
        break;
    }
    default:
        break;
    }
}

static void screen1_btn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        // 1. 读取单步界面的 3 个文本框
        spin_process.step[0].rpm = atoi(lv_textarea_get_text(guider_ui.screen1_ta_1));
        spin_process.step[0].duration_s = atoi(lv_textarea_get_text(guider_ui.screen1_ta_2));
        spin_process.step[0].accel = atoi(lv_textarea_get_text(guider_ui.screen1_ta_3));

        // 2. 清空多步残留的脏数据
        spin_process.step[1].rpm = 0;
        spin_process.step[1].duration_s = 0;
        spin_process.step[1].accel = 0;

        // 3. 明确模式
        spin_process.process_mode = 1;
        ui_load_scr_animation(&guider_ui, &guider_ui.screen, guider_ui.screen_del, &guider_ui.screen1_del, setup_scr_screen, LV_SCR_LOAD_ANIM_MOVE_LEFT, 200, 0, false, true);
        break;
    }
    default:
        break;
    }
}

static void screen1_btn_2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen, guider_ui.screen_del, &guider_ui.screen1_del, setup_scr_screen, LV_SCR_LOAD_ANIM_MOVE_LEFT, 200, 0, false, true);
        break;
    }
    default:
        break;
    }
}

static void screen1_btn_3_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen3, guider_ui.screen3_del, &guider_ui.screen1_del, setup_scr_screen3, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 200, 0, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_screen1 (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen1, screen1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen1_btn_1, screen1_btn_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen1_btn_2, screen1_btn_2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen1_btn_3, screen1_btn_3_event_handler, LV_EVENT_ALL, ui);
}

static void screen2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch(dir) {
        case LV_DIR_LEFT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.screen3, guider_ui.screen3_del, &guider_ui.screen2_del, setup_scr_screen3, LV_SCR_LOAD_ANIM_MOVE_LEFT, 200, 0, false, true);
            break;
        }
        case LV_DIR_RIGHT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.screen1, guider_ui.screen1_del, &guider_ui.screen2_del, setup_scr_screen1, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 200, 0, false, true);
            break;
        }
        default:
            break;
        }
        break;
    }
    default:
        break;
    }
}

static void screen2_btn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        spin_process.step[0].rpm = atoi(lv_textarea_get_text(guider_ui.screen2_ta_1));
        spin_process.step[0].duration_s = atoi(lv_textarea_get_text(guider_ui.screen2_ta_2));
        spin_process.step[0].accel = atoi(lv_textarea_get_text(guider_ui.screen2_ta_3));
        spin_process.step[1].rpm = atoi(lv_textarea_get_text(guider_ui.screen2_ta_7));
        spin_process.step[1].duration_s = atoi(lv_textarea_get_text(guider_ui.screen2_ta_5));
        spin_process.process_mode = 2;
        printf("Params saved!\n");
        ui_load_scr_animation(&guider_ui, &guider_ui.screen, guider_ui.screen_del, &guider_ui.screen2_del, setup_scr_screen, LV_SCR_LOAD_ANIM_NONE, 200, 0, false, true);
        break;
    }
    default:
        break;
    }
}

static void screen2_btn_2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen, guider_ui.screen_del, &guider_ui.screen2_del, setup_scr_screen, LV_SCR_LOAD_ANIM_MOVE_LEFT, 200, 0, false, true);
        break;
    }
    default:
        break;
    }
}

static void screen2_btn_3_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen3, guider_ui.screen3_del, &guider_ui.screen2_del, setup_scr_screen3, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 200, 0, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_screen2 (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen2, screen2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen2_btn_1, screen2_btn_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen2_btn_2, screen2_btn_2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen2_btn_3, screen2_btn_3_event_handler, LV_EVENT_ALL, ui);
}

static void screen3_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch(dir) {
        case LV_DIR_LEFT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.screen, guider_ui.screen_del, &guider_ui.screen3_del, setup_scr_screen, LV_SCR_LOAD_ANIM_NONE, 200, 0, false, true);
            break;
        }
        case LV_DIR_RIGHT:
        {
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.screen2, guider_ui.screen2_del, &guider_ui.screen3_del, setup_scr_screen2, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 200, 0, false, true);
            break;
        }
        default:
            break;
        }
        break;
    }
    default:
        break;
    }
}

static void screen3_btn_6_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        strcpy(current_recipe_file, "SAM.dat");
        strcpy(current_recipe_name, "SAM");
        printf("Selected Recipe: SAM\n");
        break;
    }
    default:
        break;
    }
}

static void screen3_btn_5_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        strcpy(current_recipe_file, "NiOx.dat");
        strcpy(current_recipe_name, "NiOx");
        printf("Selected Recipe: NiOx\n");
        break;
    }
    default:
        break;
    }
}

static void screen3_btn_8_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        strcpy(current_recipe_file, "PCBM.dat");
        strcpy(current_recipe_name, "PCBM");
        printf("Selected Recipe: PCBM\n");
        break;
    }
    default:
        break;
    }
}

static void screen3_btn_7_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        strcpy(current_recipe_file, "Perovskite.dat");
        strcpy(current_recipe_name, "Perovskite");
        printf("Selected Recipe:Perovskite\n");
        break;
    }
    default:
        break;
    }
}

static void screen3_btn_2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        save_recipe_to_sd();
        break;
    }
    default:
        break;
    }
}

static void screen3_btn_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        load_recipe_from_sd();
        load_preset_recipe();
        ui_load_scr_animation(&guider_ui, &guider_ui.screen, guider_ui.screen_del, &guider_ui.screen3_del, setup_scr_screen, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 200, 0, false, true);
        break;
    }
    default:
        break;
    }
}

static void screen3_btn_3_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen, guider_ui.screen_del, &guider_ui.screen3_del, setup_scr_screen, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_screen3 (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen3, screen3_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen3_btn_6, screen3_btn_6_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen3_btn_5, screen3_btn_5_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen3_btn_8, screen3_btn_8_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen3_btn_7, screen3_btn_7_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen3_btn_2, screen3_btn_2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen3_btn_1, screen3_btn_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->screen3_btn_3, screen3_btn_3_event_handler, LV_EVENT_ALL, ui);
}

static void screen_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen, guider_ui.screen_del, &guider_ui.screen_1_del, setup_scr_screen, LV_SCR_LOAD_ANIM_NONE, 200, 0, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_screen_1 (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen_1, screen_1_event_handler, LV_EVENT_ALL, ui);
}


void events_init(lv_ui *ui)
{

}
