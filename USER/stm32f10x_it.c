/******************************************************************************
* Function Name :   中断函数设置
* Description   :   2017.09.13
* Input         :
* Output        :
******************************************************************************/
/* Includes -----------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "stm32f10x_tim.h"
#include <math.h>
#include "stm32f10x.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "public.h"
#include "systick.h"
/* Private variables -------------------------------------------------------*/
extern  uint8_t     ad_flag;

extern  uint8_t     CmdRxStartUart1;
extern  uint8_t     CmdRxTempUart1;
extern  uint8_t     CmdRxStartUart2;
extern  uint8_t     CmdRxTempUart2;
extern  uint8_t     CmdRxStartUart4;
extern  uint8_t     CmdRxTempUart4;

extern  uint8_t     MoveLength;
extern  uint8_t     MoveFrePoint;
extern  uint8_t     CalibrationEnd;                                           //校准结束指令 2018-03-16

extern  uint8_t     EncoderNum;//编码器位置计数器2018-07-23

uint8_t     KeyFallFlag;//按键按下标志2018-03-21
uint8_t     KeyHoldMs;//按键持续时间2018-03-21
uint8_t     KeyShortFlag;//短按标志2018-03-21
extern  uint8_t     KeyLongFlag;//长按标志 2018-03-21
uint8_t     KeyUpCnt;//按键计数 2018-03-21
uint8_t     KeyUpFlag;//按键抬起标志 2018-03-21
uint8_t     KeyDoubleFlag;//双击标志 2018-03-21
uint8_t     KeyDownFlag;//KEYDOWN命令发送完成标志
uint8_t     WheelMoveFlag;//短按后进行的光电编码轮移动标志
extern  uint8_t     WheelMoveNum;//光电开关移动位置

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/
void NMI_Handler(void){
}
void TIM2_IRQHandler(void){
}
void TIM3_IRQHandler(void){
    static int i;
    if(TIM_GetITStatus(TIM3,TIM_IT_Update)!=RESET){//检查TIM3更新中断是否发生
        if(KeyShortFlag==1){//当短按时刻，进行点亮或单次操作
            WheelMoveFlag=1;
            /* if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_1)==Bit_RESET){ */
            /*     GPIO_SetBits(GPIOA,GPIO_Pin_1);//熄灭 */
            /* }else{ */
            /*     GPIO_ResetBits(GPIOA,GPIO_Pin_1);//点亮 */
            /* } */
        }
        if(KeyLongFlag==1){//当长按时刻，进行闪烁操作
            i++;
            if(WifiOrRs==0&&KeyDownFlag==0){//当按键按下，上传指令，开始进行校准
                Usart_SendString(USART2,"$KDWN\r\n");
                KeyDownFlag=1;
            }else if(WifiOrRs==1&&KeyDownFlag==0){
                Usart_SendString(USART1,"$KDWN\r\n");
                KeyDownFlag=1;
            }
            if(i==5){
                i=0;
                if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_1)==Bit_RESET){
                    GPIO_SetBits(GPIOA,GPIO_Pin_1);//熄灭
                }else{
                    GPIO_ResetBits(GPIOA,GPIO_Pin_1);//点亮
                }
            }
        }
        if(KeyFallFlag==1){//发生按键按下事件
            if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)==Bit_RESET){//按键持续按下
                if(KeyHoldMs<=200){
                    KeyHoldMs++;
                }else{//按键持续2s后，判定长按成立，生成长按标志
                    KeyHoldMs = 0;
                    KeyShortFlag =0;
                    KeyLongFlag = 1;//长按标志
                    KeyDownFlag = 0;
                    KeyFallFlag = 0;
                }
            }else{//按键抬起后
                if(KeyHoldMs>5){//按下时间超过50ms，认为是单击事件
                    KeyHoldMs=0;
                    KeyShortFlag=1;//单击标志
                    KeyLongFlag=0;
                    KeyFallFlag = 0;
                    if(KeyUpCnt>10&&KeyUpCnt<50){//当在500ms内连续发生单击，认为是连击
                        /* KeyDoubleFlag = 1; *///取消双击的反映，2018-04-02
                        /* KeyShortFlag = 0; */
                    }
                    KeyUpFlag = 1;//单击抬起后，生成抬起标志
                }else{//按键持续时间小于50ms，忽略
                    KeyHoldMs = 0;
                    KeyShortFlag = 0;
                    KeyLongFlag = 0;
                    KeyFallFlag = 0;
                }
            }
        }
        if(KeyUpFlag==1){//单击抬起后开始计数
            KeyUpCnt++;
        }
        if(KeyUpCnt>50){//超过500ms后开始循环
            KeyUpCnt = 0;
            KeyUpFlag = 0;
        }
    }
    TIM_ClearITPendingBit(TIM3,TIM_IT_Update);//清除TIM3更新中断标志
}
/******************
*  旋转编码器使用中断1触发  *
******************/

void EXTI1_IRQHandler(void){
	static int i;
    if(EXTI_GetITStatus(EXTI_Line1)==SET){//当A的下降沿触发的时刻
   		EXTI_ClearITPendingBit(EXTI_Line1);//清除EXTI线路挂起位
			delay_us(50);
			if(i>=3){//进行4倍抽取
				i=0;
				EncoderNum++;
//				TxBuffer[0] = EncoderNum; 
//				Usart_SendString(USART2,"$Size++\r\n");
//				Usart_SendStr_length(USART2,TxBuffer,1);
				transdata_point_p2(MoveFrePoint,WheelMoveNum,EncoderNum);
			}else{
				i++;
			}
    }
}
void  EXTI3_IRQHandler(void){
    if(EXTI_GetITStatus(EXTI_Line3)==SET){//当A的下降沿触发的时刻
   		EXTI_ClearITPendingBit(EXTI_Line3);//清除EXTI线路挂起位
			delay_us(50);
			EncoderNum=0;
//			Usart_SendString(USART2,"$Size0\r\n");
    }
}

void EXTI9_5_IRQHandler(void){
    if(EXTI_GetITStatus(EXTI_Line8)==SET){//当光电开关被阻挡的时刻开始生效
    /* if(WheelMoveFlag){//修改为双边沿触发，只要中断已经触发，且校准指令生效 */
   		EXTI_ClearITPendingBit(EXTI_Line8);//清除EXTI线路挂起位
		delay_ms(10);//消抖处理
        if(WheelMoveNum<MoveLength){
            WheelMoveNum++;
        }
        /* if(WheelMoveNum<MoveLength){ */
        /*     if((WheelMoveFlag==1)){	   //wheel按键按下且同时校准已经完成 */
		/*         delay_ms(10);//消抖处理 */
        /*         [> transdata(0xFF,WheelMoveNum);//执行采集指令 <] */
        /*         WheelMoveNum++; */
		/*         if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_1)==Bit_RESET){//led灯熄灭 */
        /*             GPIO_SetBits(GPIOA,GPIO_Pin_1); */
		/*         } */
		/*         else{ */
        /*             GPIO_ResetBits(GPIOA,GPIO_Pin_1);//led灯发光 */
		/*         } */
        /*     } */
		/*     while(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_8)==0); */
		/* }else{//扫描一行后，可以进行重新校准，重新按键，重新扫描 */
        /*     WheelMoveFlag = 0; */
        /*     KeyShortFlag = 0; */
        /*     CalibrationEnd = 0;//当扫描结束时刻置零，需要重新启动扫描 */
		/*     GPIO_SetBits(GPIOA,GPIO_Pin_1);//led灯熄灭 */
        /* } */
    }
}
void EXTI15_10_IRQHandler(void){
    if(EXTI_GetITStatus(EXTI_Line11)==SET)
	{
   		EXTI_ClearITPendingBit(EXTI_Line11);//清除EXTI线路挂起位
		delay_ms(10);//消抖处理
		if((GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)==Bit_RESET))   //k_left按键按下
		{
			delay_ms(10);//消抖处理
            WheelMoveNum = 0;
            KeyFallFlag = 1;//KEY按下标志位
		}
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)==0);
	}
}
void USART1_IRQHandler(void){                                               //RS232中断函数
    USART_ClearFlag(USART1,USART_FLAG_TC);
    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET){
        CmdRxStartUart1=1;
        CmdRxTempUart1 = USART_ReceiveData(USART1);
    }
}
void USART2_IRQHandler(void){                                               //WIFI中断函数
    USART_ClearFlag(USART2,USART_FLAG_TC);
    if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET){
        CmdRxStartUart2=1;
        CmdRxTempUart2 = USART_ReceiveData(USART2);
    }
}


void UART4_IRQHandler(void){
    USART_ClearFlag(UART4,USART_FLAG_TC);
    if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET){
        CmdRxStartUart4=1;
        CmdRxTempUart4 = USART_ReceiveData(UART4);
    }
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{}

/**
  * @brief  This function handles PendSV_Handler exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{}

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
