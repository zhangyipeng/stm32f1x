#include "system_id.h"

extern uint8_t  System_ID[12];
extern uint8_t  SystemCheck;

void ReadSystemID(void) {
    static int i;
    for(i=0;i<12;i++){                                                  //read stm32 ID
        System_ID[i]=*((u8 *)(ID_ADR+i));
    }
}

void CheckSystemID(void) {
    if((System_ID[8]==0x13&&System_ID[9]==0x56&&System_ID[10]==0x09&&System_ID[11]==0x43)
            ||(System_ID[8]==0x07&&System_ID[9]==0x60&&System_ID[10]==0x25&&System_ID[11]==0x43)
            ||(System_ID[8]==0x07&&System_ID[9]==0x77&&System_ID[10]==0x25&&System_ID[11]==0x43)
            ||(System_ID[8]==0x06&&System_ID[9]==0x67&&System_ID[10]==0x25&&System_ID[11]==0x43)
      ){
        SystemCheck = 1;
//        Usart_SendString(USART1,"$System Start\r\n");
    }else{
        Usart_SendString(USART1,"$System Failed\r\n");
        SystemCheck = 0;
    }
}

