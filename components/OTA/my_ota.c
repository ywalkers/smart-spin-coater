/*
 * @Author: ywalkers 2078500453@qq.com
 * @Date: 2026-09-22 21:34:58
 * @LastEditors: ywalkers 2078500453@qq.com
 * @LastEditTime: 2026-09-22 22:16:08
 * @FilePath: \WIFI_STUDY\components\OTA\my_ota.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "esp_http_client.h"
#include "esp_https_ota.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "my_ota.h"
static const char *TAG = "OTA_UPDATE";

void ota_task(void *pvParameter)
{
    ESP_LOGI(TAG, "Starting OTA update...");

    esp_http_client_config_t config = {
        .url = OTA_URL,
        .cert_pem = NULL,
        .skip_cert_common_name_check = true,
        .keep_alive_enable = true,
        .timeout_ms = OTA_TIMEOUT_MS,
    };

    esp_err_t ret = esp_https_ota(&config);
    if (ret == ESP_OK) {
        ESP_LOGI(TAG, "OTA Update success! Rebooting...");
        vTaskDelay(pdMS_TO_TICKS(1000));
        esp_restart(); // 下载完成，强制重启进入新版本（新固件以 PENDING_VERIFY 启动，由 main 自检）
    } else {
        // 升级失败：当前固件仍健康，继续运行即可，不回滚、不重启
        ESP_LOGE(TAG, "OTA Update failed! (Error: %s), keep running current firmware", esp_err_to_name(ret));
    }
    vTaskDelete(NULL);
}

// 当你在屏幕上点击“升级”按钮，或者接收到服务器指令时，调用此函数启动任务
void start_ota_update(void)
{
    xTaskCreate(&ota_task, "ota_task", 8192, NULL, 5, NULL);
}