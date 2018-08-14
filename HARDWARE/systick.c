#include "systick.h"
/****************************************************************************
* Function Name :   delay_us
* Description   :   延迟us
* Input         :   i
* Output        :
*****************************************************************************/
void    delay_us(u32 i){
    u32 temp;
    SysTick->LOAD=9*i;                                                      //设置重装数值，72MHz时
    SysTick->CTRL=0x01;                                                     //使能，减到零是无动作，采用外部时钟源
    SysTick->VAL=0;                                                         //清零计数器
    do{
        temp=SysTick->CTRL;                                                 //读取当前倒计数值ֵ
    }
    while((temp&0x01)&&(!(temp&(1<<16))));                                  //等待时间到达
    SysTick->CTRL=0;                                                        //关闭计数器
    SysTick->VAL=0;                                                         //清空计数器
}
/****************************************************************************
* Function Name :   delay_ms
* Description   :   延迟ms
* Input         :   i
* Output        :
*****************************************************************************/
void    delay_ms(u16 i){
    u32 temp;
    SysTick->LOAD=9000*i;                                                   //设置重装数值，72MHz时
    SysTick->CTRL=0x01;                                                     //使能，减到零是无动作，采用外部时钟源
    SysTick->VAL=0;                                                         //清零计数器
    do{
        temp=SysTick->CTRL;                                                 //读取当前倒计数值
    }
    while((temp&0x01)&&(!(temp&(1<<16))));                                  //等待时间到达
    SysTick->CTRL=0;                                                        //关闭计数器
    SysTick->VAL=0;                                                         //清空计数器
}

/****************************************************************************
* Function Name :   delay_ns
* Description   :   延迟13.8ns
* Input         :   i
* Output        :
*****************************************************************************/
void delay_ns(__IO uint32_t i)
{
    for(; i != 0; i--);
}
