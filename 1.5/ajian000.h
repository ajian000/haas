#include "aos/init.h"
#include "board.h"
#include <aos/errno.h>
#include <aos/kernel.h>
#include <k_api.h>
#include <stdio.h>
#include <stdlib.h>
#include <aos/hal/gpio.h>      
#include <hal_iomux_haas1000.h>
#include <aos/hal/pwm.h>

#define PORT 0

pwm_dev_t buz1;

gpio_dev_t blueLed;
gpio_dev_t redLed;
gpio_dev_t greenLed;

gpio_dev_t key1;
gpio_dev_t key2;
gpio_dev_t key3;
gpio_dev_t key4;

uint32_t val1;
uint32_t val2;
uint32_t val3;
uint32_t val4;

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

/**按键1扫描
 * @return int 按键是否按下
 * @author ajian000
*/
int key1_scan(){
    hal_gpio_input_get(&key1,&val1);

    if(!val1){
        delay(10);
        if(!val1){
            while(!val1){
                hal_gpio_input_get(&key1,&val1);
            }
            //TODO 这里写执行操作
            return 1;
        }
    }
    return 0;
}

/**按键2扫描
 * @return int 按键是否按下
*/
int key2_scan(){
    hal_gpio_input_get(&key2,&val2);

    if(!val2){
        delay(10);
        if(!val2){
            while(!val2){
                hal_gpio_input_get(&key2,&val2);
            }
            //TODO 这里写执行操作
            return 1;        
        }
    }
    return 0;
}

/**按键3扫描
 * @return int 按键是否按下
*/
int key3_scan(){
    hal_gpio_input_get(&key3,&val3);

    if(!val3){
        delay(10);
        if(!val3){
            while(!val3){
                hal_gpio_input_get(&key3,&val3);
            }
            //TODO 这里写执行操作
            return 1;
        }
    }
    return 0;
}

/**按键4扫描
 * @return int 按键是否按下
*/
int key4_scan(){
    hal_gpio_input_get(&key4,&val4);

    if(!val4){
        delay(10);
        if(!val4){
            while(!val4){
                hal_gpio_input_get(&key4,&val4);
            }
            //TODO 这里写执行操作
            return 1;
        }
    }
    return 0;
}

/**@Deprecated  
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

/**蜂鸣器初始化
 * @param f int 蜂鸣器振动频率(Hz)
 * @return void
*/
void buz_init(int f){
    buz1.port= PORT;
    buz1.config.duty_cycle = 0.1;
    buz1.config.freq = f;
    buz1.priv=NULL;

    hal_pwm_init(&buz1);
}

/**全部初始化
 * @param led int LED灯初始状态
 * @param buzF int 蜂鸣器频率
 * @return void
*/
all_init(int led,int buzF){
    led_init(led);
    keys_init();
    buz_init(buzF);
}