/*
 * Copyright (C) 2015-2020 Alibaba Group Holding Limited
 */

#include "aos/init.h"
#include "board.h"
#include <aos/errno.h>
#include <aos/kernel.h>
#include <k_api.h>
#include <stdio.h>
#include <stdlib.h>
//引入gpio以及引脚相关头文件
#include <aos/hal/gpio.h>           //gpio相关的头文件
#include <hal_iomux_haas1000.h>     //引脚所在的头文件3
#include "ajian000.h"

uint32_t val1;
uint32_t val2;
uint32_t val3;
uint32_t val4;

void key1_scan(){
    hal_gpio_input_get(&key1,&val1);

    if(!val1){
        delay(10);
        if(!val1){
            while(!val1){
                hal_gpio_input_get(&key1,&val1);
            }
            //TODO 这里写执行操作
            hal_gpio_output_toggle(&redLed);
        }
    }
}
void key2_scan(){
    hal_gpio_input_get(&key2,&val2);

    if(!val2){
        delay(10);
        if(!val2){
            while(!val2){
                hal_gpio_input_get(&key2,&val2);
            }
            //TODO 这里写执行操作
            hal_gpio_output_toggle(&greenLed);
        }
    }
}
void key3_scan(){
    hal_gpio_input_get(&key3,&val3);

    if(!val3){
        delay(10);
        if(!val3){
            while(!val3){
                hal_gpio_input_get(&key3,&val3);
            }
            //TODO 这里写执行操作
            hal_gpio_output_toggle(&blueLed);
        }
    }
}
void key4_scan(){
    hal_gpio_input_get(&key4,&val4);

    if(!val4){
        delay(10);
        if(!val4){
            while(!val4){
                hal_gpio_input_get(&key4,&val4);
            }
            //TODO 这里写执行操作
            hal_gpio_output_toggle(&blueLed);
            hal_gpio_output_toggle(&redLed);
            hal_gpio_output_toggle(&greenLed);
        }
    }
}

int application_start(int argc, char *argv[])
{
    led_init(0);
    keys_init();
    while (1) {
        key1_scan();
        key2_scan();
        key3_scan();
        key4_scan();
    }
}