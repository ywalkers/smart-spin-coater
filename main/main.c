/*
 * @Author: ywalkers 2078500453@qq.com
 * @Date: 2026-08-28 17:35:03
 * @LastEditors: ywalkers 2078500453@qq.com
 * @LastEditTime: 2026-10-04 18:29:35
 * @FilePath: \WIFI_STUDY\main\main.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_system.h"
#include "nvs.h"
#include "nvs_flash.h"
#include "esp_ota_ops.h"
#include "my_lcd.h"
#include "lvgl.h"
#include "wifista.h"
#include "gui_guider.h"
#include "custom.h"
#include "events_init.h"
#include "bldc_motor.h"
#include "esp_timer.h"
#include "dht11.h"
#include "myntc.h"
#include "time.h"
#include "my_ota.h"
#include "esp_task_wdt.h"

static const char *TAG = "MAIN";

// ---- OTA 回滚自检相关 ----
#define OTA_NVS_NAMESPACE   "ota_nvs"
#define BOOT_FAIL_COUNT_KEY "boot_fail"
#define BOOT_FAIL_LIMIT     3

char my_ip[20] = "0.0.0.0";
int wifi_update_flag = 0;

int g_current_temp = 25; // 默认温度
int g_current_hum = 45;  // 默认湿度
lv_ui guider_ui;
static const char *reset_reason_str(esp_reset_reason_t reason)
{
    switch (reason) {
        case ESP_RST_POWERON:   return "POWERON";
        case ESP_RST_EXT:       return "EXT";
        case ESP_RST_SW:        return "SW";
        case ESP_RST_PANIC:     return "PANIC";
        case ESP_RST_INT_WDT:   return "INT_WDT";
        case ESP_RST_TASK_WDT:  return "TASK_WDT";
        case ESP_RST_WDT:       return "WDT";
        case ESP_RST_DEEPSLEEP: return "DEEPSLEEP";
        case ESP_RST_BROWNOUT:  return "BROWNOUT";
        case ESP_RST_SDIO:      return "SDIO";
        case ESP_RST_UNKNOWN:
        default:                return "UNKNOWN";
    }
}

// 仅在"待验证(PENDING_VERIFY)"状态下累计失败启动次数；超过阈值则回滚上一版本。
// 已确认有效的稳定固件不会进入计数分支，不受影响。
static void handle_ota_rollback(void)
{
    const esp_partition_t *running = esp_ota_get_running_partition();
    esp_ota_img_states_t ota_state;
    if (esp_ota_get_state_partition(running, &ota_state) != ESP_OK) {
        return;
    }

    ESP_LOGI(TAG, "Running partition: %s, state: %d", running->label, ota_state);
    if (ota_state != ESP_OTA_IMG_PENDING_VERIFY) {
        return;
    }

    uint32_t boot_count = 0;
    nvs_handle_t handle;
    if (nvs_open(OTA_NVS_NAMESPACE, NVS_READWRITE, &handle) == ESP_OK) {
        nvs_get_u32(handle, BOOT_FAIL_COUNT_KEY, &boot_count);
        boot_count++;
        nvs_set_u32(handle, BOOT_FAIL_COUNT_KEY, boot_count);
        nvs_commit(handle);
        nvs_close(handle);
    }

    ESP_LOGW(TAG, "Pending verify, boot fail count: %u/%d", (unsigned)boot_count, BOOT_FAIL_LIMIT);
    if (boot_count >= BOOT_FAIL_LIMIT) {
        ESP_LOGE(TAG, "Too many failed boots, rolling back to previous firmware...");
        esp_ota_mark_app_invalid_rollback_and_reboot();
    }
}

// 初始化成功，清零失败计数
static void clear_boot_fail_count(void)
{
    nvs_handle_t handle;
    if (nvs_open(OTA_NVS_NAMESPACE, NVS_READWRITE, &handle) == ESP_OK) {
        nvs_set_u32(handle, BOOT_FAIL_COUNT_KEY, 0);
        nvs_commit(handle);
        nvs_close(handle);
    }
}

void app_main(void)
{
    ESP_LOGI(TAG, "Reset reason: %s", reset_reason_str(esp_reset_reason()));

    nvs_flash_init(); // 初始化 NVS（回滚计数器依赖它）

    // 待验证固件自检：连续失败启动超过阈值则自动回滚
    handle_ota_rollback();

    // 打印当前运行固件版本
    const esp_partition_t *running = esp_ota_get_running_partition();
    esp_app_desc_t running_app_info;
    if (esp_ota_get_partition_description(running, &running_app_info) == ESP_OK) {
        ESP_LOGI(TAG, "Firmware version: %s", running_app_info.version);
    }

    my_lcd_init();

    wifista_init();  // 必须先开启 Wi-Fi
    myntc_init();    // 然后启动时间同步服务

    // 任务看门狗（TWDT）：电机 PID、DHT11 等关键任务加入后需周期性喂狗，
    // 任一任务卡死超过 5s → 整机自动复位，防止电机飞车/系统挂死。
    esp_task_wdt_config_t twdt_config = {
        .timeout_ms = 5000,
        .idle_core_mask = (1 << portNUM_PROCESSORS) - 1,   // 监测所有核的 idle 任务
        .trigger_panic = true,
    };
    ESP_ERROR_CHECK(esp_task_wdt_init(&twdt_config));

    motor_init();

    dht11_start_task();

    // 调用生成的初始化函数
    setup_ui(&guider_ui);

    // 3.绑定按钮事件
    events_init(&guider_ui);

    // 4.启动自定义初始化（创建温湿度/转速等 UI 定时刷新任务）
    custom_init(&guider_ui);

    // 所有关键初始化都成功后，才确认固件有效并清零失败计数
    esp_ota_mark_app_valid_cancel_rollback();
    clear_boot_fail_count();
    ESP_LOGI(TAG, "Boot OK, firmware marked valid");

    static int last_sec = -1;
    time_t timer;
    struct tm *local_time;

    while (1) {
        timer = time(NULL);
        local_time = localtime(&timer);

        if (local_time != NULL && local_time->tm_sec != last_sec) {
            last_sec = local_time->tm_sec;
            if (lv_disp_get_scr_act(NULL) == guider_ui.screen && guider_ui.screen_label_1) {
                lv_label_set_text_fmt(guider_ui.screen_label_1,
                                      "%02d:%02d:%02d",
                                      local_time->tm_hour,
                                      local_time->tm_min,
                                      local_time->tm_sec);
            }
        }

        lv_timer_handler();
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
