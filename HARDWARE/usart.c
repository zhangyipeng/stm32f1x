#include "usart.h"
/****************************************************************************
* Function  Name    : usart_init
* Description       : USART1初始化配置，RS232
* Input             :
* Output            :
*****************************************************************************/
void usart_init(){
    GPIO_InitTypeDef    GPIO_InitStructure;                                 //声明一个结构体变量，用来初始化GPIO
    USART_InitTypeDef   USART_InitStructure;                                //串口结构体定义

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 |
                            RCC_APB2Periph_GPIOA |
                            RCC_APB2Periph_AFIO, ENABLE);                   //使能USART1，GPIOA,AFIO时钟
/****配置GPIO的模式和IO口****/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;                               //PA.9输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	                        //复用推挽输出
    GPIO_Init(GPIOA, &GPIO_InitStructure);                                  //初始化GPIOA.9
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;                              //PA10输入
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;                   //浮空输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);                                  //初始化GPIOA.10

    USART_InitStructure.USART_BaudRate = 115200;                            //串口波特率
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;             //字长为8位数据格式
    USART_InitStructure.USART_StopBits = USART_StopBits_1;                  //一个停止位
    USART_InitStructure.USART_Parity = USART_Parity_No;                     //无奇偶校验位
    USART_InitStructure.USART_HardwareFlowControl =
                                             USART_HardwareFlowControl_None;//无硬件数据流控制
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	        //收发模式
    USART_Init(USART1, &USART_InitStructure);                               //初始化串口1
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);                          //开启串口接受中断
    USART_Cmd(USART1, ENABLE);                                              //使能串口1
    USART_ClearFlag(USART1,USART_FLAG_TC);                                  //清除USARTx的待处理标志位
}
