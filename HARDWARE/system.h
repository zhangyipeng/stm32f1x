#ifndef	_system_H
#define	_system_H
/****************************************************************************
* Function Name :   system.h
* Description   :   ϵͳʱ�����ã��������ʼ��
* Input         ��
* Output        ��
*****************************************************************************/
#include	"stm32f10x.h"
#include   "public.h"
void RCC_Configuration(void);
void sys_rst(void);
void NVIC_Configuartion(void);

#endif
