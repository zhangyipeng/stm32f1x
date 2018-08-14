#ifndef _encoder_H
#define _encoder_H
#include "stm32f10x.h"
#define OutA GPIO_Pin_1   //OUTA PC1
#define OutB GPIO_Pin_2     //OUTB PC2
#define OutZ GPIO_Pin_3    //OUTZ PC3

void encoder_init(void);       //旋转编码器控制器初始化

#endif
