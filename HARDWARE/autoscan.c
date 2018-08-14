#include "autoscan.h"
#include "public.h"
/**********************************************************************
*                              行列机械扫描模式                              *
**********************************************************************/
extern uint8_t MoveFlag;
void normal_mode(void){
    static uint8_t m=0,k=0;
    if(MoveFlag ==5){
        Usart_SendString(UART4,"1ME\r\n");
        delay_ms(200);
        Usart_SendString(UART4,"1VE6\r\n");
        delay_ms(200);
        Usart_SendString(UART4,"2ME\r\n");
        delay_ms(200);
        Usart_SendString(UART4,"2VE6\r\n");
        delay_ms(200);
        /* 二维扫描方式 */
        transdata(0xFF,0xFF);
        for(m=0;m<40;m++){
            Usart_SendString(UART4,"2FP1950\r\n");
            for(k=0;k<40-1;k++){
                delay_us(delay);
                transdata(0xFF,0xFF);
            }
            Usart_SendString(UART4,"2FP0\r\n");
            if(m<40-1){
                Usart_SendString(UART4,"1FP20\r\n");
                delay_ms(200);
                transdata(0xFF,0xFF);
            }
        }
        /* 返回原点 */
        delay_ms(600);
        Usart_SendString(UART4,"1FP0\r\n");
        MoveFlag = 0;
    }
}
