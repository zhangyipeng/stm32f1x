#include "move.h"
#include "translate.h"
/****************************************************************************
* Function Name :   move_2mm
* Description   :   使用485接口控制电机运行，控制uart4
 * Input         :   1:0x31 F:0x46 L:0x4C M:0x4D E:0x45 <CR>:0x0D -：0x2D V:0x56  P:0x50
* Output        :   2号电机为横轴快速运动抽，1号电机为慢轴  VE5时刻延迟0500
*****************************************************************************/
extern uint8_t MoveFlag;
void move_2mm(uint8_t p) {
    static uint8_t m=0,k=0;
    GPIO_SetBits(GPIOC,GPIO_Pin_12);
    delay_ms(1);
    Usart_SendString(UART4, "2VE10\r");
    delay_ms(1);
    GPIO_ResetBits(GPIOC,GPIO_Pin_12);
    delay_ms(20);
    if(p==0){//6.8G
        SpiTxBuf[0] = 0x00;
        SpiTxBuf[1] = 0x2A;
        SpiTxBuf[2] = 0x41;
        setPLL(SpiTxBuf);
        SpiTxBuf[0] = (DAC_I_Q[0][4-p] & 0xFF00) >> 8;
        SpiTxBuf[1] = (DAC_I_Q[0][4-p] & 0x00FF);
        setDAC(SpiTxBuf);
        delay_us(1);
        SpiTxBuf[0] = (DAC_I_Q[1][4-p] & 0xFF00) >> 8;
        SpiTxBuf[1] = (DAC_I_Q[1][4-p] & 0x00FF);
        setDAC(SpiTxBuf);
    }else if (p==1){//6.7G
        SpiTxBuf[0] = 0x00;
        SpiTxBuf[1] = 0x29;
        SpiTxBuf[2] = 0x71;
        setPLL(SpiTxBuf);
        SpiTxBuf[0] = (DAC_I_Q[0][4-p] & 0xFF00) >> 8;
        SpiTxBuf[1] = (DAC_I_Q[0][4-p] & 0x00FF);
        setDAC(SpiTxBuf);
        SpiTxBuf[0] = (DAC_I_Q[1][4-p] & 0xFF00) >> 8;
        SpiTxBuf[1] = (DAC_I_Q[1][4-p] & 0x00FF);
        setDAC(SpiTxBuf);
    }else if (p==2){//6.6G
        SpiTxBuf[0] = 0x00;
        SpiTxBuf[1] = 0x29;
        SpiTxBuf[2] = 0x21;
        setPLL(SpiTxBuf);
        SpiTxBuf[0] = (DAC_I_Q[0][4-p] & 0xFF00) >> 8;
        SpiTxBuf[1] = (DAC_I_Q[0][4-p] & 0x00FF);
        setDAC(SpiTxBuf);
        SpiTxBuf[0] = (DAC_I_Q[1][4-p] & 0xFF00) >> 8;
        SpiTxBuf[1] = (DAC_I_Q[1][4-p] & 0x00FF);
        setDAC(SpiTxBuf);
    }else if (p==3){//6.5G
        SpiTxBuf[0] = 0x00;
        SpiTxBuf[1] = 0x28;
        SpiTxBuf[2] = 0x51;
        setPLL(SpiTxBuf);
        SpiTxBuf[0] = (DAC_I_Q[0][4-p] & 0xFF00) >> 8;
        SpiTxBuf[1] = (DAC_I_Q[0][4-p] & 0x00FF);
        setDAC(SpiTxBuf);
        SpiTxBuf[0] = (DAC_I_Q[1][4-p] & 0xFF00) >> 8;
        SpiTxBuf[1] = (DAC_I_Q[1][4-p] & 0x00FF);
        setDAC(SpiTxBuf);
    }else if (p==4){//6.4G
        SpiTxBuf[0] = 0x00;
        SpiTxBuf[1] = 0x28;
        SpiTxBuf[2] = 0x01;
        setPLL(SpiTxBuf);
        SpiTxBuf[0] = (DAC_I_Q[0][4-p] & 0xFF00) >> 8;
        SpiTxBuf[1] = (DAC_I_Q[0][4-p] & 0x00FF);
        setDAC(SpiTxBuf);
        SpiTxBuf[0] = (DAC_I_Q[1][4-p] & 0xFF00) >> 8;
        SpiTxBuf[1] = (DAC_I_Q[1][4-p] & 0x00FF);
        setDAC(SpiTxBuf);
    }else{
        SpiTxBuf[0] = 0x00;
        SpiTxBuf[1] = 0x2A;
        SpiTxBuf[2] = 0x41;
        setPLL(SpiTxBuf);
        SpiTxBuf[0] = (DAC_I_Q[0][4] & 0xFF00) >> 8;
        SpiTxBuf[1] = (DAC_I_Q[0][4] & 0x00FF);
        setDAC(SpiTxBuf);
        SpiTxBuf[0] = (DAC_I_Q[1][4] & 0xFF00) >> 8;
        SpiTxBuf[1] = (DAC_I_Q[1][4] & 0x00FF);
        setDAC(SpiTxBuf);
        }
    for(m = 0; m < 100; m++){
        GPIO_SetBits(GPIOC,GPIO_Pin_12);
        delay_ms(1);
        Usart_SendString(UART4, "2FP56000\r");
        delay_ms(1);
        GPIO_ResetBits(GPIOC,GPIO_Pin_12);
        for(k=0;k<100;k++){//进行40点的数据采集
            delay_us(delay);
            /*****************************I通道采样10个数平均*************************************/
            SpiTxBuf[0] = 0x2A;
            SpiTxBuf[1] = tst_amp*16+1;
            setPGA(SpiTxBuf);
            AdcDataIAV = meanAD(meantimes);
            TxBuffer[0]= 0xFF;
            TxBuffer[1]= k;
            TxBuffer[2] = ((AdcDataIAV & 0xFF00) >> 8);
            TxBuffer[3] = (AdcDataIAV & 0x00FF);
            /*****************************Q通道采样10个数平均*************************************/
            SpiTxBuf[0] = 0x2A;
            SpiTxBuf[1] = tst_amp*16+0;
            setPGA(SpiTxBuf);
            AdcDataQAV = meanAD(meantimes);
            TxBuffer[4] = ((AdcDataQAV & 0xFF00) >>8);
            TxBuffer[5] = (AdcDataQAV & 0x00FF);
            TxBuffer[6] = 0xF0+(4-p);
            if(WifiOrRs==0){
                Usart_SendStr_length(USART2,TxBuffer,7);
            }else{
                Usart_SendStr_length(USART1,TxBuffer,7);
            }
        }
        delay_ms(20);
        GPIO_SetBits(GPIOC,GPIO_Pin_12);
        delay_ms(1);
        Usart_SendString(UART4, "2FP0\r");
        delay_ms(1);
        GPIO_ResetBits(GPIOC,GPIO_Pin_12);
        delay_ms(20);
        GPIO_SetBits(GPIOC,GPIO_Pin_12);
        delay_ms(1);
        Usart_SendString(UART4, "1FL560\r");
        delay_ms(1);
        GPIO_ResetBits(GPIOC,GPIO_Pin_12);
        delay_ms(800);//等待电机到位
    }
    delay_ms(20);
    GPIO_SetBits(GPIOC,GPIO_Pin_12);
    delay_ms(1);
    Usart_SendString(UART4, "1VE5\r");
    delay_ms(1);
    GPIO_ResetBits(GPIOC,GPIO_Pin_12);
    delay_ms(20);
    GPIO_SetBits(GPIOC,GPIO_Pin_12);
    delay_ms(1);
    Usart_SendString(UART4, "1FP0\r");
    delay_ms(1);
    GPIO_ResetBits(GPIOC,GPIO_Pin_12);
    delay_ms(20);
    GPIO_SetBits(GPIOC,GPIO_Pin_12);
    delay_ms(1);
    Usart_SendString(UART4, "2FP0\r");
    delay_ms(1);
    GPIO_ResetBits(GPIOC,GPIO_Pin_12);
    MoveFlag = 0;
    m = 0;
    k = 0;
}
 
/****************************************************************************
* Function Name :   move_5mm
* Description   :   使用485接口控制电机运行，控制uart4
 * Input         :   1:0x31 F:0x46 L:0x4C M:0x4D E:0x45 <CR>:0x0D -：0x2D V:0x56  P:0x50
* Output        :   2号电机为横轴快速运动抽，1号电机为慢轴
*****************************************************************************/
void move_5mm(void) {
    static uint8_t m=0,k=0;
    GPIO_SetBits(GPIOC,GPIO_Pin_12);
    delay_ms(1);
    Usart_SendString(UART4, "2VE10\r");
    delay_ms(1);
    GPIO_ResetBits(GPIOC,GPIO_Pin_12);
    delay_ms(20);
    for(m = 0; m < 40; m++){
        GPIO_SetBits(GPIOC,GPIO_Pin_12);
        delay_ms(1);
        Usart_SendString(UART4, "2FP56000\r");
        delay_ms(1);
        GPIO_ResetBits(GPIOC,GPIO_Pin_12);
        for(k=0;k<40;k++){//进行40点的数据采集
            delay_us(delay);
            transdata(0xFF,k);
        }
        delay_ms(20);
        GPIO_SetBits(GPIOC,GPIO_Pin_12);
        delay_ms(1);
        Usart_SendString(UART4, "2FP0\r");
        delay_ms(1);
        GPIO_ResetBits(GPIOC,GPIO_Pin_12);
        delay_ms(20);
        GPIO_SetBits(GPIOC,GPIO_Pin_12);
        delay_ms(1);
        Usart_SendString(UART4, "1FL1400\r");
        delay_ms(1);
        GPIO_ResetBits(GPIOC,GPIO_Pin_12);
        delay_ms(600);//等待电机到位
    }
    delay_ms(20);
    GPIO_SetBits(GPIOC,GPIO_Pin_12);
    delay_ms(1);
    Usart_SendString(UART4, "1VE5\r");
    delay_ms(1);
    GPIO_ResetBits(GPIOC,GPIO_Pin_12);
    delay_ms(20);
    GPIO_SetBits(GPIOC,GPIO_Pin_12);
    delay_ms(1);
    Usart_SendString(UART4, "1FP0\r");
    delay_ms(1);
    GPIO_ResetBits(GPIOC,GPIO_Pin_12);
    delay_ms(20);
    GPIO_SetBits(GPIOC,GPIO_Pin_12);
    delay_ms(1);
    Usart_SendString(UART4, "2FP0\r");
    delay_ms(1);
    GPIO_ResetBits(GPIOC,GPIO_Pin_12);
    MoveFlag = 0;
    m = 0;
    k = 0;
}



