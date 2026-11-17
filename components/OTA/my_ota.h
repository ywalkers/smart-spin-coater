#ifndef __MY_OTA_H__
#define __MY_OTA_H__

// OTA 服务器地址：改成你局域网电脑的实际 IP 和固件包名
#define OTA_URL         "http://10.53.22.92:8000/WIFI_STUDY.bin"
// 下载超时（毫秒），避免服务器无响应时卡死
#define OTA_TIMEOUT_MS  15000

// 声明 OTA 启动函数，供外部（比如按键中断或 LVGL 按钮回调）调用
void start_ota_update(void);

#endif