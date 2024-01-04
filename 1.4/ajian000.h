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

gpio_dev_t blueLed;
gpio_dev_t redLed;
gpio_dev_t greenLed;

gpio_dev_t key1;
gpio_dev_t key2;
gpio_dev_t key3;
gpio_dev_t key4;

/**Led灯初始化
 * @param output int  LED灯初始状态
 * @return void
*/
void led_init(int output){
    //为结构体变量进行赋初值
    blueLed.port = HAL_GPIO_PIN_P4_2;
    redLed.port = HAL_GPIO_PIN_P4_4;
    greenLed.port = HAL_GPIO_PIN_P4_3;
    
    //配置信息：推挽输出
    blueLed.config = OUTPUT_PUSH_PULL;
    redLed.config = OUTPUT_PUSH_PULL;
    greenLed.config = OUTPUT_PUSH_PULL;

    //无私有数据
    blueLed.priv = NULL;
    greenLed.priv = NULL;
    redLed.priv = NULL;

    //保存gpio的初始化
    hal_gpio_init(&blueLed);
    hal_gpio_init(&greenLed);
    hal_gpio_init(&redLed);
    if(output){
        hal_gpio_output_high(&blueLed);
        hal_gpio_output_high(&redLed);
        hal_gpio_output_high(&greenLed);
    }else{
        //蓝灯的初始化的状态:熄灭状态
        hal_gpio_output_low(&blueLed);
        hal_gpio_output_low(&greenLed);
        hal_gpio_output_low(&redLed);
    }
    
}

/**延时方法
 * @param time int 延时时间,单位:毫秒
 * @return void
*/
void delay(int time){
    aos_msleep(time);
}

/**按键初始化
 * @return void
*/
void keys_init(){
    key1.port = HAL_GPIO_PIN_P2_7;
    key2.port = HAL_GPIO_PIN_P2_4;
    key3.port = HAL_GPIO_PIN_P2_5;
    key4.port = HAL_GPIO_PIN_P3_2;

    key1.config = INPUT_PULL_UP;
    key2.config = INPUT_PULL_UP;
    key3.config = INPUT_PULL_UP;
    key4.config = INPUT_PULL_UP;

    key1.priv = NULL;
    key2.priv = NULL;
    key3.priv = NULL;
    key4.priv = NULL;

    hal_gpio_init(&key1);
    hal_gpio_init(&key2);
    hal_gpio_init(&key3);
    hal_gpio_init(&key4);
}
//7452

/*  
void key1_scan(){
    hal_gpio_input_get(&key1,&val1);

    if(!val1){
        delay(10);
        if(!val1){
            while(!val1){
                hal_gpio_input_get(&key1,&val1);
            }
            //TODO 这里写执行操作
        }
    }
}
*/