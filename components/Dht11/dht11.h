/*
 * @Author: ywalkers 2078500453@qq.com
 * @Date: 2026-09-20 22:24:06
 * @LastEditors: ywalkers 2078500453@qq.com
 * @LastEditTime: 2026-09-21 16:38:37
 * @FilePath: \WIFI_STUDY\components\Dht11\dht11.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef DHT11_H
#define DHT11_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "driver/gpio.h"

// 
#define DHT11_PIN  GPIO_NUM_5

// 声明外部函数
uint8_t DHT11_Init(void);
uint8_t DHT11_Read_Data(uint8_t *temp, uint8_t *humi);
uint8_t DHT11_Read_Byte(void);
uint8_t DHT11_Read_Bit(void);
uint8_t DHT11_Check(void);
void DHT11_Rst(void);
void dht11_start_task(void);
uint8_t dht11_is_error(void);   // 查询 DHT11 是否异常(连续多次读取失败返回 1)

#ifdef __cplusplus
}
#endif

#endif