/*
* Copyright 2026 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"



void setup_scr_screen3(lv_ui *ui)
{
    //Write codes screen3
    ui->screen3 = lv_obj_create(NULL);
    lv_obj_set_size(ui->screen3, 320, 240);
    lv_obj_set_scrollbar_mode(ui->screen3, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen3, lv_color_hex(0x52a7c1), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen3, LV_GRAD_DIR_VER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui->screen3, lv_color_hex(0x6bb197), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_main_stop(ui->screen3, 83, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(ui->screen3, 202, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen3_label_1
    ui->screen3_label_1 = lv_label_create(ui->screen3);
    lv_label_set_text(ui->screen3_label_1, "配方管理");
    lv_label_set_long_mode(ui->screen3_label_1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen3_label_1, 111, 6);
    lv_obj_set_size(ui->screen3_label_1, 100, 19);

    //Write style for screen3_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen3_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen3_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen3_label_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen3_label_1, &lv_font_myfont_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen3_label_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen3_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen3_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen3_label_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen3_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen3_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen3_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen3_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen3_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen3_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen3_cont_1
    ui->screen3_cont_1 = lv_obj_create(ui->screen3);
    lv_obj_set_pos(ui->screen3_cont_1, 9, 25);
    lv_obj_set_size(ui->screen3_cont_1, 297, 172);
    lv_obj_set_scrollbar_mode(ui->screen3_cont_1, LV_SCROLLBAR_MODE_ON);

    //Write style for screen3_cont_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen3_cont_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen3_cont_1, 171, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen3_cont_1, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen3_cont_1, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen3_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen3_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen3_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen3_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen3_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen3_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen3_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen3_btn_6
    ui->screen3_btn_6 = lv_btn_create(ui->screen3_cont_1);
    ui->screen3_btn_6_label = lv_label_create(ui->screen3_btn_6);
    lv_label_set_text(ui->screen3_btn_6_label, "SAM");
    lv_label_set_long_mode(ui->screen3_btn_6_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen3_btn_6_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen3_btn_6, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen3_btn_6_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen3_btn_6, 31, 65);
    lv_obj_set_size(ui->screen3_btn_6, 241, 24);
    lv_obj_add_flag(ui->screen3_btn_6, LV_OBJ_FLAG_CHECKABLE);

    //Write style for screen3_btn_6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen3_btn_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen3_btn_6, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen3_btn_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen3_btn_6, lv_color_hex(0x191b1c), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen3_btn_6, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen3_btn_6, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen3_btn_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen3_btn_6, lv_color_hex(0x201b1b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen3_btn_6, &lv_font_LiberationSans_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen3_btn_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen3_btn_6, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen3_btn_6, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_bg_opa(ui->screen3_btn_6, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_width(ui->screen3_btn_6, 1, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_opa(ui->screen3_btn_6, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_color(ui->screen3_btn_6, lv_color_hex(0x191b1c), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_side(ui->screen3_btn_6, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui->screen3_btn_6, 5, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->screen3_btn_6, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->screen3_btn_6, lv_color_hex(0x1a1717), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->screen3_btn_6, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->screen3_btn_6, 255, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write style for screen3_btn_6, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_bg_opa(ui->screen3_btn_6, 70, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui->screen3_btn_6, lv_color_hex(0x6cc1ca), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_bg_grad_dir(ui->screen3_btn_6, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_border_width(ui->screen3_btn_6, 0, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_radius(ui->screen3_btn_6, 5, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->screen3_btn_6, 2, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_color(ui->screen3_btn_6, lv_color_hex(0x191c1e), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_opa(ui->screen3_btn_6, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_spread(ui->screen3_btn_6, 0, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_ofs_x(ui->screen3_btn_6, 0, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_ofs_y(ui->screen3_btn_6, 1, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->screen3_btn_6, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->screen3_btn_6, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_opa(ui->screen3_btn_6, 255, LV_PART_MAIN|LV_STATE_CHECKED);

    //Write codes screen3_btn_5
    ui->screen3_btn_5 = lv_btn_create(ui->screen3_cont_1);
    ui->screen3_btn_5_label = lv_label_create(ui->screen3_btn_5);
    lv_label_set_text(ui->screen3_btn_5_label, "NiOx");
    lv_label_set_long_mode(ui->screen3_btn_5_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen3_btn_5_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen3_btn_5, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen3_btn_5_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen3_btn_5, 31, 35);
    lv_obj_set_size(ui->screen3_btn_5, 241, 24);
    lv_obj_add_flag(ui->screen3_btn_5, LV_OBJ_FLAG_CHECKABLE);

    //Write style for screen3_btn_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen3_btn_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen3_btn_5, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen3_btn_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen3_btn_5, lv_color_hex(0x191b1c), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen3_btn_5, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen3_btn_5, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen3_btn_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen3_btn_5, lv_color_hex(0x201b1b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen3_btn_5, &lv_font_LiberationSans_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen3_btn_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen3_btn_5, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen3_btn_5, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_bg_opa(ui->screen3_btn_5, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_width(ui->screen3_btn_5, 1, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_opa(ui->screen3_btn_5, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_color(ui->screen3_btn_5, lv_color_hex(0x191b1c), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_side(ui->screen3_btn_5, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui->screen3_btn_5, 5, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->screen3_btn_5, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->screen3_btn_5, lv_color_hex(0x1a1717), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->screen3_btn_5, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->screen3_btn_5, 255, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write style for screen3_btn_5, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_bg_opa(ui->screen3_btn_5, 70, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui->screen3_btn_5, lv_color_hex(0x6cc1ca), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_bg_grad_dir(ui->screen3_btn_5, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_border_width(ui->screen3_btn_5, 0, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_radius(ui->screen3_btn_5, 5, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->screen3_btn_5, 2, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_color(ui->screen3_btn_5, lv_color_hex(0x191c1e), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_opa(ui->screen3_btn_5, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_spread(ui->screen3_btn_5, 0, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_ofs_x(ui->screen3_btn_5, 0, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_ofs_y(ui->screen3_btn_5, 1, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->screen3_btn_5, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->screen3_btn_5, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_opa(ui->screen3_btn_5, 255, LV_PART_MAIN|LV_STATE_CHECKED);

    //Write codes screen3_btn_4
    ui->screen3_btn_4 = lv_btn_create(ui->screen3_cont_1);
    ui->screen3_btn_4_label = lv_label_create(ui->screen3_btn_4);
    lv_label_set_text(ui->screen3_btn_4_label, "当前配方");
    lv_label_set_long_mode(ui->screen3_btn_4_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen3_btn_4_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen3_btn_4, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen3_btn_4_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen3_btn_4, 31, 6);
    lv_obj_set_size(ui->screen3_btn_4, 241, 24);
    lv_obj_add_flag(ui->screen3_btn_4, LV_OBJ_FLAG_CHECKABLE);

    //Write style for screen3_btn_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen3_btn_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen3_btn_4, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen3_btn_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen3_btn_4, lv_color_hex(0x191b1c), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen3_btn_4, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen3_btn_4, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen3_btn_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen3_btn_4, lv_color_hex(0x201b1b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen3_btn_4, &lv_font_myfont_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen3_btn_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen3_btn_4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen3_btn_4, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_bg_opa(ui->screen3_btn_4, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_width(ui->screen3_btn_4, 1, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_opa(ui->screen3_btn_4, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_color(ui->screen3_btn_4, lv_color_hex(0x191b1c), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_side(ui->screen3_btn_4, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui->screen3_btn_4, 5, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->screen3_btn_4, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->screen3_btn_4, lv_color_hex(0x1a1717), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->screen3_btn_4, &lv_font_myfont_16, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->screen3_btn_4, 255, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write style for screen3_btn_4, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_bg_opa(ui->screen3_btn_4, 70, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui->screen3_btn_4, lv_color_hex(0x6cc1ca), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_bg_grad_dir(ui->screen3_btn_4, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_border_width(ui->screen3_btn_4, 0, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_radius(ui->screen3_btn_4, 5, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->screen3_btn_4, 2, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_color(ui->screen3_btn_4, lv_color_hex(0x191c1e), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_opa(ui->screen3_btn_4, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_spread(ui->screen3_btn_4, 0, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_ofs_x(ui->screen3_btn_4, 0, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_ofs_y(ui->screen3_btn_4, 1, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->screen3_btn_4, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->screen3_btn_4, &lv_font_myfont_16, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_opa(ui->screen3_btn_4, 255, LV_PART_MAIN|LV_STATE_CHECKED);

    //Write codes screen3_btn_8
    ui->screen3_btn_8 = lv_btn_create(ui->screen3_cont_1);
    ui->screen3_btn_8_label = lv_label_create(ui->screen3_btn_8);
    lv_label_set_text(ui->screen3_btn_8_label, "PCBM");
    lv_label_set_long_mode(ui->screen3_btn_8_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen3_btn_8_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen3_btn_8, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen3_btn_8_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen3_btn_8, 32, 123);
    lv_obj_set_size(ui->screen3_btn_8, 241, 24);
    lv_obj_add_flag(ui->screen3_btn_8, LV_OBJ_FLAG_CHECKABLE);

    //Write style for screen3_btn_8, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen3_btn_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen3_btn_8, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen3_btn_8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen3_btn_8, lv_color_hex(0x191b1c), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen3_btn_8, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen3_btn_8, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen3_btn_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen3_btn_8, lv_color_hex(0x201b1b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen3_btn_8, &lv_font_LiberationSans_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen3_btn_8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen3_btn_8, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen3_btn_8, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_bg_opa(ui->screen3_btn_8, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_width(ui->screen3_btn_8, 1, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_opa(ui->screen3_btn_8, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_color(ui->screen3_btn_8, lv_color_hex(0x191b1c), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_side(ui->screen3_btn_8, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui->screen3_btn_8, 5, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->screen3_btn_8, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->screen3_btn_8, lv_color_hex(0x1a1717), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->screen3_btn_8, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->screen3_btn_8, 255, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write style for screen3_btn_8, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_bg_opa(ui->screen3_btn_8, 70, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui->screen3_btn_8, lv_color_hex(0x6cc1ca), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_bg_grad_dir(ui->screen3_btn_8, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_border_width(ui->screen3_btn_8, 0, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_radius(ui->screen3_btn_8, 5, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->screen3_btn_8, 2, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_color(ui->screen3_btn_8, lv_color_hex(0x191c1e), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_opa(ui->screen3_btn_8, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_spread(ui->screen3_btn_8, 0, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_ofs_x(ui->screen3_btn_8, 0, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_ofs_y(ui->screen3_btn_8, 1, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->screen3_btn_8, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->screen3_btn_8, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_opa(ui->screen3_btn_8, 255, LV_PART_MAIN|LV_STATE_CHECKED);

    //Write codes screen3_btn_7
    ui->screen3_btn_7 = lv_btn_create(ui->screen3_cont_1);
    ui->screen3_btn_7_label = lv_label_create(ui->screen3_btn_7);
    lv_label_set_text(ui->screen3_btn_7_label, "Perovskite");
    lv_label_set_long_mode(ui->screen3_btn_7_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen3_btn_7_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen3_btn_7, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen3_btn_7_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen3_btn_7, 32, 94);
    lv_obj_set_size(ui->screen3_btn_7, 241, 24);
    lv_obj_add_flag(ui->screen3_btn_7, LV_OBJ_FLAG_CHECKABLE);

    //Write style for screen3_btn_7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen3_btn_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen3_btn_7, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen3_btn_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen3_btn_7, lv_color_hex(0x191b1c), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen3_btn_7, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen3_btn_7, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen3_btn_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen3_btn_7, lv_color_hex(0x201b1b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen3_btn_7, &lv_font_LiberationSans_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen3_btn_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen3_btn_7, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen3_btn_7, Part: LV_PART_MAIN, State: LV_STATE_PRESSED.
    lv_obj_set_style_bg_opa(ui->screen3_btn_7, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_width(ui->screen3_btn_7, 1, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_opa(ui->screen3_btn_7, 255, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_color(ui->screen3_btn_7, lv_color_hex(0x191b1c), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_border_side(ui->screen3_btn_7, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_radius(ui->screen3_btn_7, 5, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_shadow_width(ui->screen3_btn_7, 0, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ui->screen3_btn_7, lv_color_hex(0x1a1717), LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_font(ui->screen3_btn_7, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_PRESSED);
    lv_obj_set_style_text_opa(ui->screen3_btn_7, 255, LV_PART_MAIN|LV_STATE_PRESSED);

    //Write style for screen3_btn_7, Part: LV_PART_MAIN, State: LV_STATE_CHECKED.
    lv_obj_set_style_bg_opa(ui->screen3_btn_7, 70, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui->screen3_btn_7, lv_color_hex(0x6cc1ca), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_bg_grad_dir(ui->screen3_btn_7, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_border_width(ui->screen3_btn_7, 0, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_radius(ui->screen3_btn_7, 5, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_width(ui->screen3_btn_7, 2, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_color(ui->screen3_btn_7, lv_color_hex(0x191c1e), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_opa(ui->screen3_btn_7, 255, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_spread(ui->screen3_btn_7, 0, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_ofs_x(ui->screen3_btn_7, 0, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_shadow_ofs_y(ui->screen3_btn_7, 1, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_color(ui->screen3_btn_7, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_font(ui->screen3_btn_7, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_set_style_text_opa(ui->screen3_btn_7, 255, LV_PART_MAIN|LV_STATE_CHECKED);

    //Write codes screen3_btn_2
    ui->screen3_btn_2 = lv_btn_create(ui->screen3);
    ui->screen3_btn_2_label = lv_label_create(ui->screen3_btn_2);
    lv_label_set_text(ui->screen3_btn_2_label, "保存");
    lv_label_set_long_mode(ui->screen3_btn_2_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen3_btn_2_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen3_btn_2, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen3_btn_2_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen3_btn_2, 180, 201);
    lv_obj_set_size(ui->screen3_btn_2, 56, 32);

    //Write style for screen3_btn_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen3_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen3_btn_2, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen3_btn_2, 146, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen3_btn_2, lv_color_hex(0x393939), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen3_btn_2, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen3_btn_2, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen3_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen3_btn_2, lv_color_hex(0x393939), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen3_btn_2, &lv_font_myfont_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen3_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen3_btn_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen3_btn_1
    ui->screen3_btn_1 = lv_btn_create(ui->screen3);
    ui->screen3_btn_1_label = lv_label_create(ui->screen3_btn_1);
    lv_label_set_text(ui->screen3_btn_1_label, "加载");
    lv_label_set_long_mode(ui->screen3_btn_1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen3_btn_1_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen3_btn_1, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen3_btn_1_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen3_btn_1, 71, 201);
    lv_obj_set_size(ui->screen3_btn_1, 56, 32);

    //Write style for screen3_btn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen3_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen3_btn_1, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen3_btn_1, 146, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen3_btn_1, lv_color_hex(0x393939), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen3_btn_1, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen3_btn_1, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen3_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen3_btn_1, lv_color_hex(0x393939), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen3_btn_1, &lv_font_myfont_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen3_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen3_btn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen3_btn_3
    ui->screen3_btn_3 = lv_btn_create(ui->screen3);
    ui->screen3_btn_3_label = lv_label_create(ui->screen3_btn_3);
    lv_label_set_text(ui->screen3_btn_3_label, "" LV_SYMBOL_HOME " ");
    lv_label_set_long_mode(ui->screen3_btn_3_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen3_btn_3_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen3_btn_3, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen3_btn_3_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen3_btn_3, 278, 201);
    lv_obj_set_size(ui->screen3_btn_3, 34, 31);

    //Write style for screen3_btn_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen3_btn_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen3_btn_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen3_btn_3, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen3_btn_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen3_btn_3, lv_color_hex(0x4d4646), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen3_btn_3, &lv_font_montserratMedium_22, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen3_btn_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen3_btn_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of screen3.


    //Update current screen layout.
    lv_obj_update_layout(ui->screen3);

    //Init events for screen.
    events_init_screen3(ui);
}
