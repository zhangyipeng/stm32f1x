//******************************************************************************/
//** @author 		ECUST_AASP_LAB
//** @version 	V1.0
//** @date    	20/04/2016
//** @brief   	SPI driver
//******************************************************************************/
#include "spi.h"
/****************************************************************************
*Function Name  :  SPI2_Config
*Description    :   初始化SPI2
*
*
*****************************************************************************/
void    SPI2_Config(void){
    SPI_InitTypeDef  SPI_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
                            //*结构体定义*

    RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB,ENABLE );
    RCC_APB1PeriphClockCmd( RCC_APB1Periph_SPI2, ENABLE );                  //

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;  //
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;                         //
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

 	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;      //
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		                    //:
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		                //:
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;		                        //:
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;	                        //
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		                        //:
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;	//
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	                    //
	SPI_InitStructure.SPI_CRCPolynomial = 3;	                            //

	SPI_Init(SPI2, &SPI_InitStructure);                                     //
	SPI_Cmd(SPI2, ENABLE);                                                  //
}

/****************************************************************************
*Function Name  :   SPI2_WriteReadData(unit8_t dat)
*Description    :   使用SPI写入一个字节数据同时读取一个字节数据
*Input          ：   dat：写入的8bit数据
*Output         ：   None
*Return         ：   读取到的8bit数据
*****************************************************************************/
uint8_t SPI2_WriteReadData(uint8_t dat){
    while(SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_TXE)==RESET);
    SPI_I2S_SendData(SPI2,dat);
    while(SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_RXNE )==RESET);
    return SPI_I2S_ReceiveData(SPI2);
}
