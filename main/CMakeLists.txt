idf_component_register(SRCS "main.c"
                    INCLUDE_DIRS "."
                    REQUIRES gui_app motor my_lcd_module WIFI_STA Dht11 MY_NTC OTA app_update)