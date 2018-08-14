/***************************************************************************
File		: led.c
Author		: ZhangYiPeng
Date		: 2018-03-01 09:50:13
Description : 配置GPIO口
    -
****************************************************************************/

#include "led.h"

void LED_Init(void){
    GPIO_InitTypeDef  GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB
                     | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD, ENABLE);//打开PA、PB、PC PD端口时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);//重映射使能
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//关闭JTAG重映射，因为使用了PB3 PB4端口
      GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;                             //LED-->PA.1 端口配置
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;                       //推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                       //IO口速度为50MHz
    GPIO_Init(GPIOA, &GPIO_InitStructure);                                  //根据设定参数初始化GPIOA.1
    GPIO_SetBits(GPIOA,GPIO_Pin_1);                                         //PA.1 输出高

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;                               //ATT-Rst-->PB.5 端口配置, 推挽输出
    GPIO_Init(GPIOB, &GPIO_InitStructure);                                  //推挽输出 ，IO口速度为50MHz
    GPIO_SetBits(GPIOB,GPIO_Pin_5);                                         //输出高

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;                               //ADC_CS-->PC.4 端口配置, 推挽输出
    GPIO_Init(GPIOC, &GPIO_InitStructure);                                  //推挽输出 ，IO口速度为50MHz
    GPIO_SetBits(GPIOC,GPIO_Pin_4);                                         //输出高

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;                               //PGA_CS-->PC.5 端口配置, 推挽输出
    GPIO_Init(GPIOC, &GPIO_InitStructure);                                  //推挽输出 ，IO口速度为50MHz
    GPIO_SetBits(GPIOC,GPIO_Pin_5);                                         //输出高

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;                               //DAC_CS-->PB.0 端口配置, 推挽输出
    GPIO_Init(GPIOB, &GPIO_InitStructure);                                  //推挽输出 ，IO口速度为50MHz
    GPIO_SetBits(GPIOB,GPIO_Pin_0);                                         //输出高

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;                               //PLL_CS-->PB.8 端口配置, 推挽输出
    GPIO_Init(GPIOB, &GPIO_InitStructure);                                  //推挽输出 ，IO口速度为50MHz
    GPIO_SetBits(GPIOB,GPIO_Pin_8);                                         //输出高


    /* GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;                               //WIFI_RST-->PC.2 端口配置, 推挽输出 */
    /* GPIO_Init(GPIOC, &GPIO_InitStructure);                                  //推挽输出 ，IO口速度为50MHz */
    /* GPIO_SetBits(GPIOC,GPIO_Pin_2);                                         //PC.2 输出高 */
    /*  */
    /* GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;                               //WIFI_Reload-->PC.3 端口配置, 推挽输出 */
    /* GPIO_Init(GPIOC, &GPIO_InitStructure);                                  //推挽输出 ，IO口速度为50MHz */
    /* GPIO_SetBits(GPIOC,GPIO_Pin_3);                                         //PC.3 输出高 */
}

