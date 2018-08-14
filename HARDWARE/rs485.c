#include "rs485.h"
/****************************************************************************
* Function  Name    : rs485_init
* Description       : UART4初始化，RS485
* Input             :
* Output            :
*****************************************************************************/
void rs485_init(){
    GPIO_InitTypeDef    GPIO_InitStructure;                                 //声明一个结构体变量，用来初始化GPIO
    USART_InitTypeDef   USART_InitStructure;                                //串口结构体定义

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC |
                            RCC_APB2Periph_AFIO, ENABLE);                   //使能USART4，GPIOC,AFIO时钟
/******配置GPIO的模式和IO口******/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;                              //PC.12输出EN_485
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;                        //推挽输出
    GPIO_Init(GPIOC, &GPIO_InitStructure);                                  //初始化GPIOC.12
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;                              //PC.10输出TX_485
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	                        //复用推挽输出
    GPIO_Init(GPIOC, &GPIO_InitStructure);                                  //初始化GPIOC.10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;                              //PC11输入RX_485
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;                   //浮空输入
    GPIO_Init(GPIOC, &GPIO_InitStructure);                                  //初始化GPIOC.11

    USART_InitStructure.USART_BaudRate = 115200;                            //串口波特率
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;             //字长为8位数据格式
    USART_InitStructure.USART_StopBits = USART_StopBits_1;                  //一个停止位
    USART_InitStructure.USART_Parity = USART_Parity_No;                     //无奇偶校验位
    USART_InitStructure.USART_HardwareFlowControl =
                                             USART_HardwareFlowControl_None;//无硬件数据流控制
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	        //收发模式
    USART_Init(UART4, &USART_InitStructure);                                //开启串口接受中断
    USART_Cmd(UART4, ENABLE);                                               //使能串口1
    USART_ClearFlag(UART4,USART_FLAG_TC);                                   //清除USARTx的待处理标志位
    USART_ITConfig(UART4,USART_IT_RXNE,ENABLE);
}

static void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch )
{
	/* 发送一个字节数据到USART1 */
	USART_SendData(pUSARTx,ch);

	/* 等待发送完毕 */
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
}

void Usart_SendString( USART_TypeDef * pUSARTx, char *str)
{
	unsigned int k=0;
    do
    {
        Usart_SendByte( pUSARTx, *(str + k) );
        k++;
    } while(*(str + k)!='\0');
}

/*****************  指定长度的发送字符串 **********************/
void Usart_SendStr_length( USART_TypeDef * pUSARTx, uint8_t *str,uint32_t strlen )
{
	unsigned int k=0;
    do
    {
        Usart_SendByte( pUSARTx, *(str + k) );
        k++;
    } while(k < strlen);
}
