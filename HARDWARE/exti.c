#include "exti.h"
/***************************************************************************
File		: exti_init
Author		: ZhangYiPeng
Date		: 2018-03-09 14:12:46
Description : 外部中断7的初始化程序
    -
****************************************************************************/

void exti_init(){
    GPIO_InitTypeDef GPIO_InitStructure;

	EXTI_InitTypeDef EXTI_InitStructure;

	/* 开启GPIO时钟 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

	GPIO_InitStructure.GPIO_Pin=key_in;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource11);//选择GPIO管脚用作外部中断线路
	//此处一定要记住给端口管脚加上中断外部线路
	/* 设置外部中断的模式 */
	EXTI_InitStructure.EXTI_Line=EXTI_Line11;
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;//EXTI_Trigger_Rising,EXTI_Trigger_Rising_Falling
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
    /*  */
	/* [> 设置NVIC参数 <] */
	/* NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1); */
	/* NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn; 	//打开EXTI2的全局中断 */
	/* NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //抢占优先级为0 */
	/* NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		  //响应优先级为0 */
	/* NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 		  //使能 */
	/* NVIC_Init(&NVIC_InitStructure); */
}
