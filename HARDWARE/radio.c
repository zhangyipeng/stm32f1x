#include "radio.h"
/****************************************************************************
* Function Name :   setPLL
* Description   :   PLL(ADRF4107)设置
* Input         :
* Output        :
*****************************************************************************/
void setPLL(uint8_t *buf){
    GPIO_ResetBits(GPIOB,GPIO_Pin_8);
    SPI1_FLASH_SendByte(buf[0]);
    SPI1_FLASH_SendByte(buf[1]);
    SPI1_FLASH_SendByte(buf[2]);
    GPIO_SetBits(GPIOB,GPIO_Pin_8);
    GPIO_ResetBits(GPIOB,GPIO_Pin_8);
    GPIO_SetBits(GPIOB,GPIO_Pin_8);
}
/****************************************************************************
* Function Name :   setDAC
* Description   :   DAC(MAX5722)设置,补偿IQ两路基带放大器控制字为高4bitC3C2C1C0+12bitdata,0000为OUTA,0001为OUTB
* Input         :   outA为Q通道,outB为I通道
* Output        :
*****************************************************************************/
void setDAC(uint8_t *buf){
    GPIO_ResetBits(GPIOC,GPIO_Pin_4);
    SPI2_WriteReadData(buf[0]);
    SPI2_WriteReadData(buf[1]);
    GPIO_SetBits(GPIOC,GPIO_Pin_4);
}
/****************************************************************************
* Function Name :   setPGA
* Description   :   PGA(PGA112)设置,可编程增益放大器,控制字00101010G3G2G1G0Ch3Ch2ch1ch0
* Input         :   ch0为Q通道,ch1为I通道0000ch0,0001cha1
* Output        :
*****************************************************************************/
void setPGA(uint8_t *buf){
    GPIO_ResetBits(GPIOC,GPIO_Pin_5);
    SPI2_WriteReadData(buf[0]);
    SPI2_WriteReadData(buf[1]);
    GPIO_SetBits(GPIOC,GPIO_Pin_5);
}
/****************************************************************************
* Function Name :   readADC
* Description   :   ADC(AD7680)设置16bit精度,100k采样
* Input         :
* Output        :
*****************************************************************************/
void readADC(void){
    GPIO_ResetBits(GPIOB,GPIO_Pin_0);
    SpiRxBuf[0] = SPI2_WriteReadData(0xFF);
    SpiRxBuf[1] = SPI2_WriteReadData(0xFF);
    SpiRxBuf[2] = SPI2_WriteReadData(0xFF);
    GPIO_SetBits(GPIOB,GPIO_Pin_0);
}
/****************************************************************************
* Function Name :   meanAD
* Description   :   对AD采样后的信号进行平均处理
* Input         :
* Output        :
*****************************************************************************/
int meanAD(uint8_t meantimes){
    uint8_t j;
    uint32_t AdcDataSum = 0;
    AdcDataAV = 0;
    for(j = 0; j < meantimes; j++){
        SpiRxIdx=0;
        delay_us(10);                                                       ////20us-10us, ADC50KHz（20us）
        readADC();
        AdcDataSum = AdcDataSum + (SpiRxBuf[0]*4096 + SpiRxBuf[1]*16 + SpiRxBuf[2]/16);
    }
    AdcDataAV = AdcDataSum /meantimes;
return AdcDataAV;
}
/****************************************************************************
* Function Name :   setHMC
* Description   :   HMC(hmc305s)设置
* Input         : 1F:0   0F:0.5     17:1    1B:2    1D:4    1E:8    00:15.5
* Output        :
*****************************************************************************/
void setHMC(uint8_t *buf){
    GPIO_SetBits(GPIOB,GPIO_Pin_5);
    GPIO_ResetBits(GPIOB,GPIO_Pin_5);
    GPIO_SetBits(GPIOB,GPIO_Pin_5);                                         ////先进行rst拉低复位,清空寄存器
    SPIx_FLASH_SendByte(buf[0]);
    GPIO_ResetBits(GPIOB,GPIO_Pin_3);
    GPIO_SetBits(GPIOB,GPIO_Pin_3);
    GPIO_ResetBits(GPIOB,GPIO_Pin_3);
}
