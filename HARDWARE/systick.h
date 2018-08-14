#ifndef _systick_H
#define _systick_H

#include "stm32f10x.h"
#include   "public.h"

void    delay_us(u32 i);
void    delay_ms(u16 i);
void    delay_ns(__IO uint32_t i);

#endif
