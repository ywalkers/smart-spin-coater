/*
 * @Author: ywalkers 2078500453@qq.com
 * @Date: 2026-08-28 17:41:28
 * @LastEditors: ywalkers 2078500453@qq.com
 * @LastEditTime: 2026-08-28 18:04:31
 * @FilePath: \WIFI_STUDY\components\my_lcd_module\include\my_lcd.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef __MY_LCD_H
#define __MY_LCD_H

#include "lvgl.h"
//初始化硬件、SPI总线、和LVGL   

extern lv_obj_t * g_sys_log_label;

void my_lcd_init(void);

#endif