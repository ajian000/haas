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

int application_start(int argc, char *argv[])
{
    int loop = 1;
    int red = 0,green = 0,blue = 0;

    led_init(0);
    keys_init();
    buz_init(500);
    while (1) {
        if(key1_scan()){
            red++;
        }
        if(key2_scan()){
            green++;
        }
        if(key3_scan()){
            blue++;
        }

        if(red%2 != 0){
            hal_gpio_output_toggle(&redLed);
        }else{
            hal_gpio_output_low(&redLed);
        }
        
        if(green%2 != 0){
            hal_gpio_output_toggle(&greenLed);
        }else{
            hal_gpio_output_low(&greenLed);
        }

        if(blue%2 != 0){
            hal_gpio_output_toggle(&blueLed);
        }else{
            hal_gpio_output_low(&blueLed);
        }
        delay(200);

        if(key4_scan()){
            red = 0;
            green = 0;
            blue = 0;
            hal_gpio_output_low(&redLed);
            hal_gpio_output_low(&greenLed);
            hal_gpio_output_low(&blueLed);
        }
    }
}