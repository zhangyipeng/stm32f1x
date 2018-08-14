#include "spi_flash.h"
/****************************************************************************
*Function Name  :  SPIx_FLASH_Init
*Description    :   初始化软件模拟SPIx
*
*
*****************************************************************************/
void SPIx_FLASH_Init(void){
    GPIO_InitTypeDef    GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB |
                            RCC_APB2Periph_GPIOD,ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;//CLK
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;//MISO
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//要用模拟输入
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//修改为RST_n
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;//MOSI
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD,&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//CS
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_InitStructure);
}
/****************************************************************************
*Function Name  :  SPI1_FLASH_Init
*Description    :   初始化软件模拟SPI1
*在4183V1.01版本中因为接口连接错误，MOSI连接至MISO接口，在1.18版本进行端口互换
*
*****************************************************************************/
void SPI1_FLASH_Init(void){
    GPIO_InitTypeDef    GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |
                            RCC_APB2Periph_GPIOC,ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;//CS CLK
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;//MISO
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//要用模拟输入
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//修改为RST_n
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;//MOSI
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
}
/****************************************************************************
*Function Name  :  SPI2_FLASH_Init
*Description    :   初始化软件模拟SPI2
*
*
*****************************************************************************/
void SPI2_FLASH_Init(void){
    GPIO_InitTypeDef    GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB |
                            RCC_APB2Periph_GPIOC,ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;// CLK
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;//MISO
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//要用模拟输入
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//修改为RST_n
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;//MOSI
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_InitStructure);
}
/****************************************************************************
*Function Name  :  SPIx_FLASH_SendByte
*Description    :  软件模拟SPIx发送数据
*
*
*****************************************************************************/
u8 SPIx_FLASH_SendByte(uint8_t byte){
    uint8_t i;
    u8 Temp=0x00;
    unsigned char SDI;
    for(i=0;i<8;i++){
        GPIO_ResetBits(GPIOB,GPIO_Pin_4);//sclk=0;
        if(byte&0x80){//首位字符判定
            GPIO_SetBits(GPIOD,GPIO_Pin_2);//Out=1
        }else{
            GPIO_ResetBits(GPIOD,GPIO_Pin_2);//out=0
        }
        byte<<=1;
        GPIO_SetBits(GPIOB,GPIO_Pin_4);//sclk=1;
        SDI=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5);//in是否有输入
        Temp<<=1;
        if(SDI){
            Temp++;
        }
        GPIO_ResetBits(GPIOB,GPIO_Pin_4);//sclk=0
    }
    return Temp;//in输入值ֵ
}
/****************************************************************************
*Function Name  :  SPI1_FLASH_SendByte
*Description    :  软件模拟SPI1发送数据
*
*
*****************************************************************************/
u8 SPI1_FLASH_SendByte(uint8_t byte){
    uint8_t i;
    u8 Temp=0x00;
    unsigned char SDI;
    for(i=0;i<8;i++){
        GPIO_ResetBits(GPIOA,GPIO_Pin_5);//sclk=0;
        if(byte&0x80){//首位字符判定
            GPIO_SetBits(GPIOA,GPIO_Pin_6);//Out=1
        }else{
            GPIO_ResetBits(GPIOA,GPIO_Pin_6);//out=0
        }
        byte<<=1;
        GPIO_SetBits(GPIOA,GPIO_Pin_5);//sclk=1;
        SDI=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7);//in是否有输入
        Temp<<=1;
        if(SDI){
            Temp++;
        }
        GPIO_ResetBits(GPIOA,GPIO_Pin_5);//sclk=0
    }
    return Temp;//in输入值
}
/****************************************************************************
*Function Name  :  SPI2_FLASH_SendByte
*Description    :  软件模拟SPI2发送数据
*
*
*****************************************************************************/
u8 SPI2_FLASH_SendByte(uint8_t byte){
    uint8_t i;
    u8 Temp=0x00;
    unsigned char SDI;
    for(i=0;i<8;i++){
        GPIO_ResetBits(GPIOB,GPIO_Pin_13);//sclk=0;
        if(byte&0x80){//首位字符判定
            GPIO_SetBits(GPIOB,GPIO_Pin_15);//Out=1
        }else{
            GPIO_ResetBits(GPIOB,GPIO_Pin_15);//out=0
        }
        byte<<=1;
        GPIO_SetBits(GPIOB,GPIO_Pin_13);//sclk=1;
        SDI=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14);//in是否有输入
        Temp<<=1;
        if(SDI){
            Temp++;
        }
        GPIO_ResetBits(GPIOB,GPIO_Pin_13);//sclk=0
    }
    return Temp;//in输入值
}
