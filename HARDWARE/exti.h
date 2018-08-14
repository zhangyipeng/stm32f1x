#ifndef _exti_H
#define _exti_H
#include "stm32f10x.h"
#define key_in GPIO_Pin_11   //key PC7->PB11

void exti_init(void);       //外部中断初始化

#endif
