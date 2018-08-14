//******************************************************************************/
//** @author 	ECUST_AASP_LAB
//** @version 	V1.0
//** @date    	20/04/2016
//** @brief   	SPI driver
//******************************************************************************/
#ifndef _spi_H
#define _spi_H
#include "stm32f10x.h"
  

//RX SPI, SPI2 				  	    													  
void    SPI2_Config(void);
uint8_t SPI2_WriteReadData(uint8_t dat);
		 
#endif

