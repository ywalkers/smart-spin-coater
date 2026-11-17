/*
* Copyright 2026 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

typedef struct
{
  
	lv_obj_t *screen;
	bool screen_del;
	lv_obj_t *screen_label_1;
	lv_obj_t *screen_label_2;
	lv_obj_t *screen_label_3;
	lv_obj_t *screen_label_4;
	lv_obj_t *screen_label_5;
	lv_obj_t *screen_label_6;
	lv_obj_t *screen_btn_1;
	lv_obj_t *screen_btn_1_label;
	lv_obj_t *screen_btn_2;
	lv_obj_t *screen_btn_2_label;
	lv_obj_t *screen_arc_1;
	lv_obj_t *screen_label_7;
	lv_obj_t *screen_label_10;
	lv_obj_t *screen_btn_3;
	lv_obj_t *screen_btn_3_label;
	lv_obj_t *screen_led_1;
	lv_obj_t *screen_btn_4;
	lv_obj_t *screen_btn_4_label;
	lv_obj_t *screen_led_2;
	lv_obj_t *screen_btn_5;
	lv_obj_t *screen_btn_5_label;
	lv_obj_t *screen_label_11;
	lv_obj_t *screen_label_12;
	lv_obj_t *screen_label_13;
	lv_obj_t *screen_label_14;
	lv_obj_t *screen1;
	bool screen1_del;
	lv_obj_t *screen1_label_1;
	lv_obj_t *screen1_tabview_1;
	lv_obj_t *screen1_tabview_1_tab_1;
	lv_obj_t *screen1_label_2;
	lv_obj_t *screen1_label_3;
	lv_obj_t *screen1_label_4;
	lv_obj_t *screen1_ta_1;
	lv_obj_t *screen1_ta_2;
	lv_obj_t *screen1_ta_3;
	lv_obj_t *screen1_btn_1;
	lv_obj_t *screen1_btn_1_label;
	lv_obj_t *screen1_btn_2;
	lv_obj_t *screen1_btn_2_label;
	lv_obj_t *screen1_btn_3;
	lv_obj_t *screen1_btn_3_label;
	lv_obj_t *screen2;
	bool screen2_del;
	lv_obj_t *screen2_label_1;
	lv_obj_t *screen2_tabview_1;
	lv_obj_t *screen2_tabview_1_tab_1;
	lv_obj_t *screen2_tabview_1_tab_2;
	lv_obj_t *screen2_label_2;
	lv_obj_t *screen2_label_3;
	lv_obj_t *screen2_label_4;
	lv_obj_t *screen2_ta_1;
	lv_obj_t *screen2_ta_2;
	lv_obj_t *screen2_ta_3;
	lv_obj_t *screen2_label_5;
	lv_obj_t *screen2_label_6;
	lv_obj_t *screen2_label_7;
	lv_obj_t *screen2_ta_5;
	lv_obj_t *screen2_ta_6;
	lv_obj_t *screen2_ta_7;
	lv_obj_t *screen2_btn_1;
	lv_obj_t *screen2_btn_1_label;
	lv_obj_t *screen2_btn_2;
	lv_obj_t *screen2_btn_2_label;
	lv_obj_t *screen2_btn_3;
	lv_obj_t *screen2_btn_3_label;
	lv_obj_t *screen3;
	bool screen3_del;
	lv_obj_t *screen3_label_1;
	lv_obj_t *screen3_cont_1;
	lv_obj_t *screen3_btn_6;
	lv_obj_t *screen3_btn_6_label;
	lv_obj_t *screen3_btn_5;
	lv_obj_t *screen3_btn_5_label;
	lv_obj_t *screen3_btn_4;
	lv_obj_t *screen3_btn_4_label;
	lv_obj_t *screen3_btn_8;
	lv_obj_t *screen3_btn_8_label;
	lv_obj_t *screen3_btn_7;
	lv_obj_t *screen3_btn_7_label;
	lv_obj_t *screen3_btn_2;
	lv_obj_t *screen3_btn_2_label;
	lv_obj_t *screen3_btn_1;
	lv_obj_t *screen3_btn_1_label;
	lv_obj_t *screen3_btn_3;
	lv_obj_t *screen3_btn_3_label;
	lv_obj_t *screen_1;
	bool screen_1_del;
	lv_obj_t *g_kb_top_layer;
}lv_ui;

typedef void (*ui_setup_scr_t)(lv_ui * ui);

void ui_init_style(lv_style_t * style);

void ui_load_scr_animation(lv_ui *ui, lv_obj_t ** new_scr, bool new_scr_del, bool * old_scr_del, ui_setup_scr_t setup_scr,
                           lv_scr_load_anim_t anim_type, uint32_t time, uint32_t delay, bool is_clean, bool auto_del);

void ui_animation(void * var, int32_t duration, int32_t delay, int32_t start_value, int32_t end_value, lv_anim_path_cb_t path_cb,
                       uint16_t repeat_cnt, uint32_t repeat_delay, uint32_t playback_time, uint32_t playback_delay,
                       lv_anim_exec_xcb_t exec_cb, lv_anim_start_cb_t start_cb, lv_anim_ready_cb_t ready_cb, lv_anim_deleted_cb_t deleted_cb);


void init_scr_del_flag(lv_ui *ui);

void setup_ui(lv_ui *ui);

void init_keyboard(lv_ui *ui);

extern lv_ui guider_ui;


void setup_scr_screen(lv_ui *ui);
void setup_scr_screen1(lv_ui *ui);
void setup_scr_screen2(lv_ui *ui);
void setup_scr_screen3(lv_ui *ui);
void setup_scr_screen_1(lv_ui *ui);

LV_FONT_DECLARE(lv_font_montserratMedium_16)
LV_FONT_DECLARE(lv_font_myfont_14)
LV_FONT_DECLARE(lv_font_myfont_16)
LV_FONT_DECLARE(lv_font_montserratMedium_20)
LV_FONT_DECLARE(lv_font_LiberationSans_16)
LV_FONT_DECLARE(lv_font_myfont_20)
LV_FONT_DECLARE(lv_font_LiberationSans_15)
LV_FONT_DECLARE(lv_font_montserratMedium_25)
LV_FONT_DECLARE(lv_font_montserratMedium_22)
LV_FONT_DECLARE(lv_font_myfont_18)


#ifdef __cplusplus
}
#endif
#endif
