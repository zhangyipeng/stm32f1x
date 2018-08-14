#ifndef	_calculate_H
#define	_calculate_H
/****************************************************************************
* Function Name :   calculate.h
* Description   :   进制转化及2^n计算
* Input         ：
* Output        ：
*****************************************************************************/
#include "stm32f10x.h"
#include "public.h"

int char2hex(const char *s,uint8_t qq,uint8_t number);
int pow2(int);

#endif
