#ifndef	_radio_H
#define	_radio_H
/****************************************************************************
* Function Name :   radio.h
* Description   :   …‰∆µ∞Â≤Œ ˝…Ë÷√PLL°¢PGA°¢AD°¢DA
* Input         £∫
* Output        £∫
*****************************************************************************/
#include "stm32f10x.h"
#include  "public.h"

void setPGA(uint8_t *buf);
void setPLL(uint8_t *buf);
void setDAC(uint8_t *buf);
void readADC(void);
int meanAD(uint8_t meantimes);
void setHMC(uint8_t *buf);

#endif
