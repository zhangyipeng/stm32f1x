#include "time.h"
/****************************************************************************
* Function Name :   time_init
* Description   :   定时器3的端口初始化
* Input         :
* Output        :   因主要时钟降低至36MHz，Period修改为10
*****************************************************************************/
void    time_init(){
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;                          //声明结构体
    /* TIM_OCInitTypeDef       TIM_OCInitStructure;                            //初始化外设TIMx */

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);                    //开始定时器2时钟
/* TIM3 configuration */
    TIM_ClearITPendingBit(TIM3,TIM_IT_Update);//清除TIM中断源
    TIM_TimeBaseStructure.TIM_Period = 20;                                  //20*0.5=10ms设置自动装载寄存器周期的值
    TIM_TimeBaseStructure.TIM_Prescaler = 0x8CA0;                           //0.5ms  36000，用来作为TIMx时钟频率预分频值
    TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;                          //设置时钟分割：TDTS = Tck——tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;             //向上计数模式
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x0000;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
    TIM_Cmd(TIM3,ENABLE);//使能TIM3

/*     TIM_OCStructInit(&TIM_OCInitStructure); */
/* [> Output Compare Timing Mode configuration: Channel1 <] */
/*     TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing; */
/*     TIM_OCInitStructure.TIM_Pulse = 0x0; */
/*     TIM_OC1Init(TIM2, &TIM_OCInitStructure); */

/* Immediate load of TIM2 Precaler value */
    /* TIM_PrescalerConfig(TIM2, 0xEA5F, TIM_PSCReloadMode_Immediate); */
/* Clear TIM2 update pending flag */
    /* TIM_ClearFlag(TIM3, TIM_FLAG_Update); */
/* Enable TIM2 Update interrupt */
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);                              //使能指定的TIM中断
    /* 设置中断参数*/
//    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
//    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);
}



