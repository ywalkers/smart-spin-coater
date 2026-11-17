idf_component_register(
    SRCS "my_lcd.c"
    INCLUDE_DIRS "include"
    # 声明本模块需要用到 esp_lcd 和 lvgl 等底层库
    REQUIRES esp_lcd driver lvgl esp_timer esp_lcd_ili9341 esp_lcd_touch_ft5x06
)