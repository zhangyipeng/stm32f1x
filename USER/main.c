/******************************************************************************
* Function Name :   全息雷达二期主函数
* Description   :   2017.09.13
* Input         :
* Output        :
******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "public.h"
#include "system.h"                                                         //系统时钟配置，复位函数及中断嵌套函数
#include "radio.h"                                                          //射频元件控制函数
#include "calculate.h"                                                      //数据转化函数
#include "translate.h"                                                      //接收机控制及数据上传函数
#include "move.h"                                                           //电机控制函数
#include "command.h"
#include "encoder.h"
#include "calibration.h"
/* #include "stm32f10x_flash.h" */
//中断使用定义
/*-------------------USART1-------------------------------------------------*/
uint8_t     TxBuffer[40];                                          //RS232的发送缓存数组，数组大小16Byte
/*-------------------解析状态控制字----------------------------------------*/
uint8_t     WifiOrRs=0;
uint8_t     SystemReset;                                                    //复位使能
uint8_t     PLLBuf[3];                                                      //PLL控制字寄存器
uint8_t     DACBuf[2];                                                      //DAC控制字寄存器
uint8_t     PGABuf[2];                                                      //PGA控制字寄存器
uint8_t     HMCBuf[1];                                                      //HMC控制字寄存器
uint8_t     SignalModeEn;                                                   //单频点工作模式使能：1：单次5频点控制，2：单频点工作
uint8_t     SignalPoint;                                                    //工作频点
uint8_t     TestModeEn;                                                     //校准模式使能
int16_t     DAC_I_Q[2][5];                                                  //5频点IQ校准数据寄存器
uint8_t     tst_amp=1;                                                        //PGA放大倍数
uint8_t     meantimes=10;                                                      //AD平均次数
uint8_t     MoveLength=100;                                                      //设备移动距离 2018-03-16
uint8_t     MoveFlag;                                                       //电机运动使能
uint8_t     MoveFrePoint=1;                                                    //2mm工作频点
uint32_t    delay=5390;                                                          //电机运动延迟
uint8_t     DelayModeEn;                                                     //电机分步操作
uint8_t     MoveInitialEn;                                                  //电机复位命令
uint8_t     CalibrationEnd=0;                                           //校准结束指令 2018-03-16
// SPI
uint8_t     SpiTxBuf[4];                                                    //SPI发送寄存器
uint8_t     SpiRxBuf[0x3003];                                               //SPI接收寄存器
uint16_t    SpiRxIdx;                                                       //SPI数据下标
// DAC initial value
int16_t     DAC_I_Default=0x07FF;                                          //DACI默认值
int16_t     DAC_Q_Default=0x17FF;                                          //DACQ默认值
// ADC parameters
uint32_t    AdcDataISum;                                                    //I通道均值累加
uint32_t    AdcDataQSum;                                                    //Q通道均值累加
uint16_t    AdcDataIAV;                                                     //I通道均值
uint16_t    AdcDataQAV;                                                     //Q通道均值
uint16_t    AdcDataAV;                                                      //ADC均值

uint8_t     ad_flag=0;
uint16_t    ad[2];

uint8_t     System_ID[12];
uint8_t     SystemCheck;

uint8_t     CmdRxStartUart1;
uint8_t     CmdRxTempUart1;
char        CmdLFUart1;
char        CmdRecvOKUart1;
char        CmdRxEndUart1;
uint16_t    CmdRxCntUart1=0;
char        CmdRxBufferUart1[BufferSize1];
uint8_t     CmdRxStartUart2;
uint8_t     CmdRxTempUart2;
char        CmdLFUart2;
char        CmdRecvOKUart2;
char        CmdRxEndUart2;
uint16_t    CmdRxCntUart2=0;
char        CmdRxBufferUart2[BufferSize1];
uint8_t     CmdRxStartUart4;
uint8_t     CmdRxTempUart4;
char        CmdLFUart4;
char        CmdRecvOKUart4;
char        CmdRxEndUart4;
uint16_t    CmdRxCntUart4=0;
char        CmdRxBufferUart4[BufferSize1];

uint8_t     KeyLongFlag;//长按标志 2018-03-21
uint8_t     EncoderNum=0;//编码器位置计数器 2018-07-23
uint8_t     WheelMoveNum=0;//光电开关计数


int main(void){
/* System Initialization ------------------------------------------------------------*/
/* System clocks configuration */
    RCC_Configuration();
    delay_ms(3000);
    NVIC_Configuartion();
/* GPIO configuration */
    LED_Init();
    usart_init();
    wifi_init(256000);
    /* rs485_init(); */
    adc_init();
    /* exti_init(); */
    itr_init();
    /* time_init(); */
    SPIx_FLASH_Init();
    SPI1_FLASH_Init();
    encoder_init();
//    SPI2_FLASH_Init();
    SPI2_Config();
    sys_rst();
    /* GPIO_ResetBits(GPIOC,GPIO_Pin_12);                                      //RS485收发控制使能，高发低收 */
    /* ReadSystemID(); */
    /* CheckSystemID(); */
    /* if(FLASH_GetReadOutProtectionStatus()!=SET){//设置flash读保护 */
    /*     [> 会擦出FLASH <] */
    /*     FLASH_Unlock();//写保护时可以不用 */
    /*     FLASH_ReadOutProtection(ENABLE); */
    /* } */
    while (1){
        /* GPIO_ResetBits(GPIOC,GPIO_Pin_12); */
        CommandRxEndUart1();
        CommandRxEndUart2();
        CommandRxEndUart4();
        CommandResolution();
        if(SystemReset==1){
            sys_rst();
            SystemReset=0;
        }
        if(SignalModeEn==1){
            transdata(0xFF,0xFF);
            SignalModeEn=0;
        }
        else if(SignalModeEn==2){
            transdata_point(SignalPoint);
            SignalModeEn=0;
        }
        if(MoveFlag==2){
            move_2mm(MoveFrePoint);
            MoveFlag=0;
        }else if(MoveFlag==5){
            move_5mm();
            MoveFlag=0;
        }
        if(ad_flag==1){//#BATTERY
            ad[0] = Get_Adc(ADC_Channel_10);
            TxBuffer[7]=ad[0]*3.3/4096*10;
            TxBuffer[0]='$';
            TxBuffer[1]='B';
            TxBuffer[2]='=';
            TxBuffer[3]=TxBuffer[7]/10+0x30;
            TxBuffer[4]=TxBuffer[7]%10+0x30;
            TxBuffer[5]='\r';
            TxBuffer[6]='\n';
            if(WifiOrRs==0){
                Usart_SendStr_length(USART2,TxBuffer,7);
            }else{
                Usart_SendStr_length(USART1,TxBuffer,7);
            }
            delay_ms(100);
            ad_flag=0;
        }
    }
}


/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
