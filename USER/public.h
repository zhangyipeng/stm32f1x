#ifndef _public_H
#define _public_H

#include "stm32f10x.h"
#include "led.h"
#include "usart.h"
#include "wifi.h"
#include "rs485.h"
#include "systick.h"
#include "time.h"
#include "radio.h"
#include "calculate.h"
#include "system.h"
#include "spi_flash.h"
#include "spi.h"
//#include "pwm.h"
#include "translate.h"
#include "move.h"
#include "adc.h"
#include "command.h"
#include "system_id.h"
#include "exti.h"
#include "itr.h"
#include "time.h"
#include "calibration.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <misc.h>

/* Private define ------------------------------------------------------------*/
#define ID_ADR          0x1ffff7e8
#define BufferSize1     20
#define BufferSize2     16
#define _FLASH_PROG
// SPI
extern  uint8_t     SpiTxBuf[4];                                            //SPI发送寄存器
extern  uint8_t     SpiRxBuf[0x3003];	                                    //SPI接收寄存器
extern  uint16_t    SpiRxIdx;                                               //SPI数据下标
// DAC initial value
extern  int16_t     DAC_I_Default;                                          //DACI默认值
extern  int16_t     DAC_Q_Default;                                          //DACQ默认值

//中断用全局变量
/*-------------------USART1-------------------------------------------------*/
extern  uint8_t     TxBuffer[40];                                  //RS232的发送缓存数组，数组大小16Byte

/*-------------------解析状态控制字----------------------------------------*/
extern  uint8_t     WifiOrRs;
extern  uint8_t     SystemReset;                                            //复位使能
extern  uint8_t     PLLBuf[3];                                              //PLL控制字寄存器
extern  uint8_t     DACBuf[2];                                              //DAC控制字寄存器
extern  uint8_t     PGABuf[2];                                              //PGA控制字寄存器
extern  uint8_t     HMCBuf[1];                                              //HMC控制字寄存器
extern  uint8_t     SignalModeEn;                                           //单频点工作模式使能：1：单次5频点控制，2：单频点工作
extern  uint8_t     SignalPoint;                                            //工作频点
extern  uint8_t     TestModeEn;                                             //校准模式使能
extern  int16_t     DAC_I_Q[2][5];                                          //5频点IQ校准数据寄存器
extern  uint8_t     tst_amp;                                                //PGA放大倍数
extern  uint8_t     meantimes;                                              //AD平均次数
extern  uint8_t     MoveLength;                                              //设备移动距离 2018-03-16
extern  uint8_t     MOV_FLAG;                                               //电机运动使能
extern  uint8_t     MovFrePoint;                                            //2mm工作频点
extern  uint32_t    delay;                                                  //电机运动延迟
extern  uint8_t     wrk_num;                                                //电机工作采集点数
extern  uint8_t     DelayModeEn;                                             //电机分步操作
extern  uint8_t     MoveInitialEn;                                          //电机复位命令
extern  uint8_t     CalibrationEnd;                                           //校准结束指令 2018-03-16
// ADC parameters
extern  uint32_t    AdcDataISum;                                            //I通道均值累加
extern  uint32_t    AdcDataQSum;                                            //Q通道均值累加
extern  uint16_t    AdcDataIAV;                                             //I通道均值
extern  uint16_t    AdcDataQAV;                                             //Q通道均值
extern  uint16_t    AdcDataAV;                                              //ADC均值

extern  uint8_t     Rx_Flag;
extern  uint8_t     RxTemp;
extern  char        LF_Flag;
extern  char        Recv_OK;
extern  char        Rxend_Flag;
extern  char        send_num;
extern  char        Tx_Flag;

extern  uint8_t     ad_flag;


extern  uint8_t     CmdRxStartUart1;
extern  uint8_t     CmdRxTempUart1;
extern  char        CmdLFUart1;
extern  char        CmdRecvOKUart1;
extern  char        CmdRxEndUart1;
extern  uint16_t    CmdRxCntUart1;
extern  char        CmdRxBufferUart1[BufferSize1];
extern  uint8_t     CmdRxStartUart2;
extern  uint8_t     CmdRxTempUart2;
extern  char        CmdLFUart2;
extern  char        CmdRecvOKUart2;
extern  char        CmdRxEndUart2;
extern  uint16_t    CmdRxCntUart2;
extern  char        CmdRxBufferUart2[BufferSize1];
extern  uint8_t     CmdRxStartUart4;
extern  uint8_t     CmdRxTempUart4;
extern  char        CmdLFUart4;
extern  char        CmdRecvOKUart4;
extern  char        CmdRxEndUart4;
extern  uint16_t    CmdRxCntUart4;
extern  char        CmdRxBufferUart4[BufferSize1];


#endif
