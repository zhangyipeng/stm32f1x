#ifndef _spi_flash_H
#define _spi_flash_H
#include "stm32f10x.h"

void SPIx_FLASH_Init(void);
u8 SPIx_FLASH_SendByte(uint8_t byte);
void SPI1_FLASH_Init(void);
u8 SPI1_FLASH_SendByte(uint8_t byte);
void SPI2_FLASH_Init(void);
u8 SPI2_FLASH_SendByte(uint8_t byte);

#endif
