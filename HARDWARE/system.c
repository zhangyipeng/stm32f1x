#include "system.h"

/****************************************************************************
* Function Name :   RCC_Configuration
* Description   :   时钟配置
* Input         :
* Output        :
*****************************************************************************/
void RCC_Configuration(void){
    SystemInit();
    /* [> PCLK2 = HCLK/2 <] */
//  RCC_PCLK2Config(RCC_HCLK_Div2);
/* [> Enable SPI Periph clock <] */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
//    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
}
/* void RCC_Configuration(void){ */
/*     RCC_DeInit();//RCC寄存器重置 */
/*     RCC_HSICmd(ENABLE);//HSI使能 */
/*     while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET){ */
/*     }//等待HSI使能 */
/*     if(1){ */
/*         RCC_HCLKConfig(RCC_SYSCLK_Div1); */
/*         RCC_PCLK1Config(RCC_HCLK_Div2); */
/*         RCC_PCLK2Config(RCC_HCLK_Div1); */
/*         //设置PLL时钟及倍频 */
/*         RCC_PLLConfig(RCC_PLLSource_HSI_Div2,RCC_PLLMul_9); */
/*         RCC_PLLCmd(ENABLE); */
/*         while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET){ */
/*         } */
/*         //设置系统时钟SYSCLK */
/*         RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK); */
/*         while(RCC_GetSYSCLKSource()!= 0x08){//00：HSI作为系统时钟，04：HSE作为系统时钟，08：PLL作为系统时钟 */
/*         } */
/*     } */
/*     RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); */
/*     RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); */
/*     RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); */
/*     RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE); */
/*     RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE); */
/* } */
/****************************************************************************
* Function Name :   sys_rst
* Description   :   系统初始化
* Input         :
* Output        :
*****************************************************************************/
void sys_rst(void){
    int8_t i = 0;
    DAC_I_Default = 0x07FF;
    DAC_Q_Default = 0x17FF;
    for(i=0;i<5;i++){
        DAC_I_Q[0][i]= 0x07FF;
        DAC_I_Q[1][i]= 0x17FF;
    }
/*init PLL */  //6.4G
    SpiTxBuf[0] = 0x8d;
    SpiTxBuf[1] = 0x80;
    SpiTxBuf[2] = 0x83;
    setPLL(SpiTxBuf);
    SpiTxBuf[0] = 0x8d;
    SpiTxBuf[1] = 0x80;
    SpiTxBuf[2] = 0x82;
    setPLL(SpiTxBuf);
    SpiTxBuf[0] = 0x00;
    SpiTxBuf[1] = 0x00;
    SpiTxBuf[2] = 0x10;
    setPLL(SpiTxBuf);
    SpiTxBuf[0] = 0x00;
    SpiTxBuf[1] = 0x28;
    SpiTxBuf[2] = 0x01;
    setPLL(SpiTxBuf);
/*init DAC */
    SpiTxBuf[0] = 0xFF;
    SpiTxBuf[1] = 0x10;
    setDAC(SpiTxBuf);
    SpiTxBuf[0] = 0x07;
    SpiTxBuf[1] = 0xFF;
    setDAC(SpiTxBuf); //DAC CHA1.3V
    SpiTxBuf[0] = 0x17;
    SpiTxBuf[1] = 0xFF;
    setDAC(SpiTxBuf); //DAC CHB1.3V
/*init PGA112 */
    SpiTxBuf[0] = 0x2A;
    SpiTxBuf[1] = 0x00;
    setPGA(SpiTxBuf);
/*init PGA112 */
    setHMC(0x00);

    TxBuffer[0] = 0x24; //'$'
    TxBuffer[1] = 0x30; //'0'
    TxBuffer[2] = 0x31; //'1'
    TxBuffer[3] = 0x32; //'2'
    TxBuffer[4] = 0x33; //'3'
    TxBuffer[5] = 0x34; //'4'
    TxBuffer[6] = 0x35; //'5'
    TxBuffer[7] = 0x36; //'6'
    TxBuffer[8] = 0x37; //'7'
    TxBuffer[9] = 0x0A; //'8'
//    if(WifiOrRs==0){
//        Usart_SendString(USART2,"System Reset");
//        Usart_SendStr_length(USART2,TxBuffer,10);
//    }else{
//        Usart_SendString(USART1,"System Reset");
//        Usart_SendStr_length(USART1,TxBuffer,10);
//    }
}
/****************************************************************************
* Function Name :   NVIC_Configuartion
* Description   :   中断优先级配置,Group可以是0,1,2,3;分别代表抢占优先级有1,2,4,8,16和响应优先级16,8,4,2,1个,数字越小优先级越高
* Input         :
* Output        :
*****************************************************************************/
void NVIC_Configuartion(void){
    NVIC_InitTypeDef NVIC_InitStructure;                                    //中断结构体定义

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);                         //中断优先级分组
/*  USART1    */
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;                       //打开USART1的全局终端,在3.0版本库中IRQChannel缩写为了TRQn
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1 ;                //抢占优先级0
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;                      //响应优先级0
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                         //IRQ通道使能
    NVIC_Init(&NVIC_InitStructure);	                                        //根据指定的参数初始化VIC寄存器
/*  UART4    */
    NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;                        //打开UART4的全局终端
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;                //抢占优先级0
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;                      //响应优先级1
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                         //IRQ通道使能
    NVIC_Init(&NVIC_InitStructure);	                                        //根据指定的参数初始化VIC寄存器
//*  USART2    */
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;                        //打开USART2的全局终端
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;                //抢占优先级0
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;                      //响应优先级1
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                         //IRQ通道使能
    NVIC_Init(&NVIC_InitStructure);	                                        //根据指定的参数初始化VIC寄存器
//*  EXTI7    */
    NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;                        //打开外部中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1 ;                //抢占优先级0
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;                      //响应优先级1
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                         //IRQ通道使能
    NVIC_Init(&NVIC_InitStructure);	                                        //根据指定的参数初始化VIC寄存器
//*  EXTI11   */
    NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;                        //打开外部中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1 ;                //抢占优先级0
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;                      //响应优先级1
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                         //IRQ通道使能
    NVIC_Init(&NVIC_InitStructure);
//*  EXTI1   */
    NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;                        //打开外部中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1 ;                //抢占优先级0
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;                      //响应优先级1
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                         //IRQ通道使能
    NVIC_Init(&NVIC_InitStructure);			//根据指定的参数初始化VIC寄存器
		//*  EXTI1   */
    NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;                        //打开外部中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1 ;                //抢占优先级0
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;                      //响应优先级1
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                         //IRQ通道使能
    NVIC_Init(&NVIC_InitStructure);			//根据指定的参数初始化VIC寄存器
/*  TIM3    */
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;                         //打开TIM3的全局中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;                //抢占优先级0
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;                      //响应优先级2
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                         //IRQ通道使能
    NVIC_Init(&NVIC_InitStructure);	                                        //根据指定的参数初始化VIC寄存器
}

