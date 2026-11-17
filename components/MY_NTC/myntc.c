#include "myntc.h"
#include "esp_sntp.h" 
#include "time.h"
#include "lvgl.h"
#include "my_lcd.h"


void myntc_init(void)
{
    esp_sntp_setoperatingmode(ESP_SNTP_OPMODE_POLL);//主动向服务器请求时间
    esp_sntp_setservername(0, "pool.ntp.org");//设置服务器地址
    esp_sntp_setservername(1, "cn.pool.ntp.org");//设置服务器地址
    esp_sntp_setservername(2, "ntp1.aliyun.com");//设置服务器地址,首先访问第一个，访问失败访问第二个
    esp_sntp_init();//初始化sntp
    setenv("TZ","CST-8",1);//时区参数、时区、已设置时区则覆盖
    tzset();

}