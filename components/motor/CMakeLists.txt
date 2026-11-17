idf_component_register(
    SRCS "bldc_motor.c" 
    INCLUDE_DIRS "."   
    REQUIRES  driver gui_app lvgl esp_timer
)