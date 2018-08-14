#include "calibration.h"
/****************************************************************************
* Function Name :  calibration
* Description   :   5频点AD数据上传
* Input         :   电机位置（行，列）
* Output        :   二进制数TxBuffer：行，列，I通道数据，Q通道数据，频率
*****************************************************************************/
void calibration(void){
    int8_t p = 0;
    static uint8_t  FirstLatch[2][5];
    static uint8_t  SecendLatch[2][5];
    static uint8_t  i;
    for(i=0; i<5; i++){
        DAC_I_Q[0][i] = 0x0000;
        DAC_I_Q[1][i] = 0x1000;
        FirstLatch[0][i] = 0;
        FirstLatch[1][i] = 0;
        SecendLatch[0][i] = 0;
        SecendLatch[1][i] = 0;
    }
    delay_us(5);
    for(p=0; p<5; p++){//5
        if(p==0){//6.4G
            SpiTxBuf[0] = 0x00;
            SpiTxBuf[1] = 0x28;
            SpiTxBuf[2] = 0x01;
            setPLL(SpiTxBuf);
        }else if (p==1){//6.5G
            SpiTxBuf[0] = 0x00;
            SpiTxBuf[1] = 0x28;
            SpiTxBuf[2] = 0x51;
            setPLL(SpiTxBuf);
        }else if (p==2){//6.6G
            SpiTxBuf[0] = 0x00;
            SpiTxBuf[1] = 0x29;
            SpiTxBuf[2] = 0x21;
            setPLL(SpiTxBuf);
        }else if (p==3){//6.7G
            SpiTxBuf[0] = 0x00;
            SpiTxBuf[1] = 0x29;
            SpiTxBuf[2] = 0x71;
            setPLL(SpiTxBuf);
        }else if (p==4){//6.8G
            SpiTxBuf[0] = 0x00;
            SpiTxBuf[1] = 0x2A;
            SpiTxBuf[2] = 0x41;
            setPLL(SpiTxBuf);
        }else{
            SpiTxBuf[0] = 0x00;
            SpiTxBuf[1] = 0x28;
            SpiTxBuf[2] = 0x01;
            setPLL(SpiTxBuf);
        }
        delay_us(5);
        SpiTxBuf[0] = (DAC_I_Q[0][p] & 0xFF00) >> 8;
        SpiTxBuf[1] = (DAC_I_Q[0][p] & 0x00FF);
        setDAC(SpiTxBuf);//I通道初始化
        delay_us(5);
        SpiTxBuf[0] = (DAC_I_Q[1][p] & 0xFF00) >> 8;
        SpiTxBuf[1] = (DAC_I_Q[1][p] & 0x00FF);
        setDAC(SpiTxBuf);
        delay_us(5);//Q通道初始化
/*****************************I通道采样10个数平均*************************************/
        SpiTxBuf[0] = 0x2A;
        SpiTxBuf[1] = tst_amp*16+1;
        setPGA(SpiTxBuf);//切换为I通道
        delay_us(5);
        AdcDataIAV = meanAD(meantimes);
        while((AdcDataIAV<=32768)&&(DAC_I_Q[0][p]<0x0FFF)&&(FirstLatch[0][p]==0)){
            DAC_I_Q[0][p] = DAC_I_Q[0][p] + 0x0100;
            SpiTxBuf[0] = (DAC_I_Q[0][p] & 0xFF00) >> 8;
            SpiTxBuf[1] = (DAC_I_Q[0][p] & 0x00FF);
            setDAC(SpiTxBuf);//I通道初始化
            AdcDataIAV = meanAD(meantimes);
            if(AdcDataIAV >32768){
               FirstLatch[0][p] = 1;
            }
        }
        while((AdcDataIAV>=32768)&&(DAC_I_Q[0][p]<0x0FFF)&&(SecendLatch[0][p]==0)){
            DAC_I_Q[0][p] = DAC_I_Q[0][p] - 0x0010;
            SpiTxBuf[0] = (DAC_I_Q[0][p] & 0xFF00) >> 8;
            SpiTxBuf[1] = (DAC_I_Q[0][p] & 0x00FF);
            setDAC(SpiTxBuf);//I通道初始化
            AdcDataIAV = meanAD(meantimes);
            if(AdcDataIAV <32768){
                SecendLatch[0][p] = 1;
            }
        }
        if(p>=0){
            TxBuffer[p*7+0]= 0xFF;
            TxBuffer[p*7+1]= 0xFF;
            TxBuffer[p*7+2] = ((AdcDataIAV & 0xFF00) >> 8);
            TxBuffer[p*7+3] = (AdcDataIAV & 0x00FF);
        }
/*****************************Q通道采样10个数平均*************************************/
        SpiTxBuf[0] = 0x2A;
        SpiTxBuf[1] = tst_amp*16+0;
        setPGA(SpiTxBuf);//切换为I通道
        delay_us(5);
        AdcDataQAV = meanAD(meantimes);
        while((AdcDataQAV<=32768)&&(DAC_I_Q[1][p]<0x1FFF)&&(FirstLatch[1][p]==0)){
            DAC_I_Q[1][p] = DAC_I_Q[1][p] + 0x0100;
            SpiTxBuf[0] = (DAC_I_Q[1][p] & 0xFF00) >> 8;
            SpiTxBuf[1] = (DAC_I_Q[1][p] & 0x00FF);
            setDAC(SpiTxBuf);//Q通道初始化
            AdcDataQAV = meanAD(meantimes);
            if(AdcDataQAV >32768){
               FirstLatch[1][p] = 1;
            }
        }
        while((AdcDataQAV>=32768)&&(DAC_I_Q[1][p]<0x1FFF)&&(SecendLatch[1][p]==0)){
            DAC_I_Q[1][p] = DAC_I_Q[1][p] - 0x0010;
            SpiTxBuf[0] = (DAC_I_Q[1][p] & 0xFF00) >> 8;
            SpiTxBuf[1] = (DAC_I_Q[1][p] & 0x00FF);
            setDAC(SpiTxBuf);//I通道初始化
            AdcDataQAV = meanAD(meantimes);
            if(AdcDataQAV <32768){
                SecendLatch[1][p] = 1;
            }
        }
        if(p>=0){
            TxBuffer[p*7+4] = ((AdcDataQAV & 0xFF00) >>8);
            TxBuffer[p*7+5] = (AdcDataQAV & 0x00FF);
            TxBuffer[p*7+6] = p+0xF0;
        }
    }
    Usart_SendStr_length(USART2,TxBuffer,35);
}
