#ifndef _itr_H
#define _itr_H
#include "stm32f10x.h"
#define WheelIn GPIO_Pin_8   //wheel PC8
#define WheelIn_1 GPIO_Pin_11   //wheel_1 PA11

void itr_init(void);       //光电开关初始化

#endif
