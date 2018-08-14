#ifndef	_rs485_H
#define	_rs485_H
#include	"stm32f10x.h"

void	rs485_init(void);
// void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch );
void Usart_SendString( USART_TypeDef * pUSARTx, char *str);
void Usart_SendStr_length( USART_TypeDef * pUSARTx, uint8_t *str,uint32_t strlen );

#endif
