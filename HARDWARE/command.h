//******************************************************************************/
//** @author    zyp
//** @version   v1.0
//** @date      2017.12.21
//** @brief     ������λ�Cָ��
//******************************************************************************/
#ifndef __COMMAND_H
#define __COMMAND_H
#include "stm32f10x.h"
#include "public.h"

void CommandResolution(void);
void CommandRxEndUart1(void);
void CommandRxEndUart2(void);
void CommandRxEndUart4(void);
void CommandBufferClear(void);


#endif
