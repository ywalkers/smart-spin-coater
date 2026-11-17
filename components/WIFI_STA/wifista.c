/*
 * @Author: ywalkers 2078500453@qq.com
 * @Date: 2026-08-29 15:42:08
 * @LastEditors: ywalkers 2078500453@qq.com
 * @LastEditTime: 2026-08-31 09:56:58
 * @FilePath: \WIFI_STUDY\components\WIFI_STA\wifista.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "wifista.h"
#include "esp_wifi.h"
#include "my_lcd.h"
#include "esp_netif.h"
#include "esp_event.h"
#include "lvgl.h"
#include "stdio.h"

extern char my_ip[32];
extern int wifi_update_flag;
static const char *TAG = "WIFI_STA";

void wifista_event_handler(void* event_handler_arg,esp_event_base_t event_base,int32_t event_id,void* event_data)//最后一个参数存储着事件返回的全部信息
{
    if(event_base == WIFI_EVENT)
    {
        if(event_id == WIFI_EVENT_STA_START)
        {
            esp_wifi_connect();
        }
        else if(event_id == WIFI_EVENT_STA_CONNECTED)
        {
            if (g_sys_log_label != NULL) {
                lv_label_set_text(g_sys_log_label, "WIFI Connected!");
            }
        }
        else if(event_id == WIFI_EVENT_STA_DISCONNECTED)
        {
            if (g_sys_log_label != NULL) {
                lv_label_set_text(g_sys_log_label, "WIFI Disonnected!");
                esp_wifi_stop();
            }
        }
    }
    else if(event_base == IP_EVENT)
    {
         if(event_id == IP_EVENT_STA_GOT_IP)
        {
            //获取包含IP信息的结构体
            ip_event_got_ip_t *event = (ip_event_got_ip_t *)event_data;//监听到IP事件后，将全部信息存储到结构体指针中
            // IPSTR 和 IP2STR 是官方宏，会自动把数字转成 "192.168.x.x" 的格式
            sprintf(my_ip, IPSTR, IP2STR(&event->ip_info.ip));
            wifi_update_flag = 1;

        }
        
    }
}



void wifista_init(void)
{
   esp_netif_init();  //初始化LWIP协议栈
   esp_event_loop_create_default(); //创建默认事件循环
   //向循环事件组中注册要监听的事件组以及编号，并创建事件函数
   //监听wifi事件、监听所有事件、监听到事件，触发这个事件函数
   esp_event_handler_register(WIFI_EVENT,ESP_EVENT_ANY_ID,&wifista_event_handler,NULL);
   esp_event_handler_register(IP_EVENT,IP_EVENT_STA_GOT_IP,&wifista_event_handler,NULL);//监听获取IP事件

   esp_netif_create_default_wifi_sta();  //将STA/SA模块与lwip协议栈连接
   //初始化与WIFI相关底层硬件
   wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();//初始化配置结构体，默认宏定义
   esp_wifi_init(&cfg);
   //工作模式设置为STA模式
   esp_wifi_set_mode(WIFI_MODE_STA);
   //配置SAT模式具体参数
   wifi_config_t wifista_config ={
        .sta={
            .ssid=DEFAULT_SSID,
            .password=DEFAULT_PWD,
        }

   };
   esp_wifi_set_config(WIFI_IF_STA, &wifista_config);

   esp_wifi_start();

}

