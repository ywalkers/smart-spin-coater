#include "dht11.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "rom/ets_sys.h"
#include "driver/gpio.h"
#include "esp_attr.h"
#include "esp_task_wdt.h"
#include <stdio.h>

// 温湿度全局变量（在 main.c 中定义）
extern int g_current_temp;
extern int g_current_hum;

// DHT11 异常标志：连续多次读取失败置 1，供 UI 查询
static uint8_t dht11_error = 0;

// 定义自旋锁，供临界区使用
portMUX_TYPE dht11_mux = portMUX_INITIALIZER_UNLOCKED;

// 开漏模式下，不需要再切换 IN 和 OUT 方向了！
#define DHT11_DQ_OUT(x) gpio_set_level(DHT11_PIN, x)
#define DHT11_DQ_IN     gpio_get_level(DHT11_PIN)

// 复位 DHT11（发送起始信号）
void DHT11_Rst(void)
{
    DHT11_DQ_OUT(0);              // 拉低数据线
    vTaskDelay(pdMS_TO_TICKS(20));// 这里不在临界区内，可以安全使用系统延时
    DHT11_DQ_OUT(1);              // 释放数据线，由上拉电阻拉高
    ets_delay_us(30);             // 主机拉高 20~40us
}

// 等待 DHT11 的回应（微秒级时序，放 IRAM 防止 WiFi 禁 flash cache 时被卡）
IRAM_ATTR uint8_t DHT11_Check(void)
{
    uint8_t retry = 0;
    while (DHT11_DQ_IN && retry < 100) // 等待变低
    {
        retry++;
        ets_delay_us(1);
    }
    if(retry >= 100)
    {
        return 1; // 传感器没有拉低（注意：本函数在临界区/IRAM 中运行，禁止 printf）
    }
    else retry = 0;

    while (!DHT11_DQ_IN && retry < 100) // 等待变高
    {
        retry++;
        ets_delay_us(1);
    }
    if(retry >= 100)
    {
        return 1; // 传感器拉低了，但没有恢复高电平
    }
    return 0;
}

// 从 DHT11 读取一个位
IRAM_ATTR uint8_t DHT11_Read_Bit(void)
{
    uint8_t retry = 0;
    while(DHT11_DQ_IN && retry < 100) // 等待高电平结束（位开始）
    {
        retry++;
        ets_delay_us(1);
    }
    retry = 0;
    while(!DHT11_DQ_IN && retry < 100) // 等待低电平结束（50us）
    {
        retry++;
        ets_delay_us(1);
    }
    ets_delay_us(40); // 关键判断时间
    if(DHT11_DQ_IN) return 1;
    else return 0;
}

// 从 DHT11 读取一个字节
IRAM_ATTR uint8_t DHT11_Read_Byte(void)
{
    uint8_t i, dat = 0;
    for (i = 0; i < 8; i++)
    {
        dat <<= 1;
        dat |= DHT11_Read_Bit();
    }
    return dat;
}

// 从 DHT11 读取一次数据
uint8_t DHT11_Read_Data(uint8_t *temp, uint8_t *humi)
{
    uint8_t buf[5];
    uint8_t i;

    DHT11_Rst(); // 先发送开始信号（包含毫秒延时，不加锁）

    // 【核心】仅对微秒级读取过程加锁！
    taskENTER_CRITICAL(&dht11_mux);
    if(DHT11_Check() == 0)
    {
        for(i = 0; i < 5; i++)
        {
            buf[i] = DHT11_Read_Byte();
        }
        taskEXIT_CRITICAL(&dht11_mux); // 读完马上解锁

        if((buf[0] + buf[1] + buf[2] + buf[3]) == buf[4]) // 校验和
        {
            *humi = buf[0];
            *temp = buf[2];
            return 0; // 成功
        }
    }
    else {
        taskEXIT_CRITICAL(&dht11_mux); // Check失败也要记得解锁
    }
    return 1; // 失败
}

// 初始化
uint8_t DHT11_Init(void)
{
    gpio_config_t io_conf = {
        .intr_type = GPIO_INTR_DISABLE,
        // 【关键】使用开漏输入输出模式 (Open-Drain)
        .mode = GPIO_MODE_INPUT_OUTPUT_OD,
        .pin_bit_mask = (1ULL << DHT11_PIN),
        .pull_down_en = 0,
        .pull_up_en = 1 // 开启内部上拉
    };
    gpio_config(&io_conf);
    DHT11_DQ_OUT(1); // 默认输出高电平（释放总线）

    DHT11_Rst();
    return DHT11_Check();
}

static void dht11_task(void *pvParameter)
{
    uint8_t temp = 0;
    uint8_t humi = 0;
    uint8_t init_retry = 0;
    uint8_t fail_cnt = 0;   // 连续读取失败计数
    vTaskDelay(pdMS_TO_TICKS(2000));

    while(DHT11_Init() != 0) {
        if ((++init_retry & 0x0F) == 1) {
            printf("DHT11 初始化中，重试 %u 次...\n", init_retry);
        }
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
    printf("DHT11 Init Success!\n");

    // 加入任务看门狗：进入采集循环后需周期喂狗，传感器读卡死则复位
    esp_task_wdt_add(NULL);

    while (1) {
        esp_task_wdt_reset();   // 每周期喂狗
        if (DHT11_Read_Data(&temp, &humi) == 0) {
            g_current_temp = temp;
            g_current_hum = humi;
            fail_cnt = 0;       // 成功则清零失败计数
            dht11_error = 0;
            printf("温湿度: %dC  %d%%\n", temp, humi);
        } else {
            // 读取失败：保留上次有效值(不更新 g_current_temp/humi)，避免显示脏数据
            fail_cnt++;
            if (fail_cnt >= 5) {
                dht11_error = 1;   // 连续 5 次(10s)失败，标记传感器异常
            }
            if (fail_cnt == 1 || fail_cnt % 10 == 0) {
                printf("DHT11 读取失败 %u 次，保留上次有效值\n", fail_cnt);
            }
        }
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

void dht11_start_task(void)
{
    xTaskCreatePinnedToCore(dht11_task, "dht11_task", 4096, NULL, 5, NULL, 1);
}

// 查询 DHT11 是否异常（连续多次读取失败返回 1）
uint8_t dht11_is_error(void) {
    return dht11_error;
}
