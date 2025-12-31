#include "key.h"

uint8_t key;
uint32_t key1_time,key2_time,key3_time,key4_time;
uint8_t key1_0 = 1,key1_1 = 1;
uint8_t key2_0 = 1,key2_1 = 1;
uint8_t key3_0 = 1,key3_1 = 1;
uint8_t key4_0 = 1,key4_1 = 1;

uint8_t KEY_Scan(uint32_t ms)
{
    uint8_t key = 0;
    
    key1_1 = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0);
    key2_1 = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1);
    key3_1 = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2);
    key4_1 = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);

    if(key1_0 == 1 && key1_1 == 0)    key1_time = ms;
    if(key1_0 == 0 && key1_1 == 1 && ms - key1_time <= 1000) key = 1; 
    if(key1_0 == 0 && key1_1 == 1 && ms - key1_time >= 1000) key = 10;

    if(key2_0 == 1 && key2_1 == 0)    key2_time = ms;
    if(key2_0 == 0 && key2_1 == 1 && ms - key2_time <= 1000) key = 2;
    if(key2_0 == 0 && key2_1 == 1 && ms - key2_time >= 1000) key = 20;

    if(key3_0 == 1 && key3_1 == 0)    key3_time = ms;
    if(key3_0 == 0 && key3_1 == 1 && ms - key3_time <= 1000) key = 3;
    if(key3_0 == 0 && key3_1 == 1 && ms - key3_time >= 1000) key = 30;

    if(key4_0 == 1 && key4_1 == 0)    key4_time = ms;
    if(key4_0 == 0 && key4_1 == 1 && ms - key4_time <= 1000) key = 4;
    if(key4_0 == 0 && key4_1 == 1 && ms - key4_time >= 1000) key = 40;

    key1_0 = key1_1;
    key2_0 = key2_1;
    key3_0 = key3_1;
    key4_0 = key4_1;

    return key;
}
