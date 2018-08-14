#include "translate.h"
/****************************************************************************
* Function Name :   transdata
* Description   :   5频点AD数据上传
* Input         :   电机位置（行，列）
* Output        :   二进制数TxBuffer：行，列，I通道数据，Q通道数据，频率
*****************************************************************************/
void transdata(uint8_t row,uint8_t col){
    int8_t p = 0;
    delay_us(5);
    for(p=0; p<5; p++){//5
        if(p==0){//6.4G
            SpiTxBuf[0] = 0x00;
            SpiTxBuf[1] = 0x28;
            SpiTxBuf[2] = 0x01;
            setPLL(SpiTxBuf);
            delay_us(5);
            SpiTxBuf[0] = (DAC_I_Q[0][p] & 0xFF00) >> 8;
            SpiTxBuf[1] = (DAC_I_Q[0][p] & 0x00FF);
            setDAC(SpiTxBuf);
            delay_us(5);
            SpiTxBuf[0] = (DAC_I_Q[1][p] & 0xFF00) >> 8;
            SpiTxBuf[1] = (DAC_I_Q[1][p] & 0x00FF);
            setDAC(SpiTxBuf);
            delay_us(5);
        }else if (p==1){//6.5G
            SpiTxBuf[0] = 0x00;
            SpiTxBuf[1] = 0x28;
            SpiTxBuf[2] = 0x51;
            setPLL(SpiTxBuf);
            delay_us(5);
            SpiTxBuf[0] = (DAC_I_Q[0][p] & 0xFF00) >> 8;
            SpiTxBuf[1] = (DAC_I_Q[0][p] & 0x00FF);
            setDAC(SpiTxBuf);
            delay_us(5);
            SpiTxBuf[0] = (DAC_I_Q[1][p] & 0xFF00) >> 8;
            SpiTxBuf[1] = (DAC_I_Q[1][p] & 0x00FF);
            setDAC(SpiTxBuf);
            delay_us(5);
        }else if (p==2){//6.6G
            SpiTxBuf[0] = 0x00;
            SpiTxBuf[1] = 0x29;
            SpiTxBuf[2] = 0x21;
            setPLL(SpiTxBuf);
            delay_us(5);
            SpiTxBuf[0] = (DAC_I_Q[0][p] & 0xFF00) >> 8;
            SpiTxBuf[1] = (DAC_I_Q[0][p] & 0x00FF);
            setDAC(SpiTxBuf);
            delay_us(5);
            SpiTxBuf[0] = (DAC_I_Q[1][p] & 0xFF00) >> 8;
            SpiTxBuf[1] = (DAC_I_Q[1][p] & 0x00FF);
            setDAC(SpiTxBuf);
            delay_us(5);
        }else if (p==3){//6.7G
            SpiTxBuf[0] = 0x00;
            SpiTxBuf[1] = 0x29;
            SpiTxBuf[2] = 0x71;
            setPLL(SpiTxBuf);
            delay_us(5);
            SpiTxBuf[0] = (DAC_I_Q[0][p] & 0xFF00) >> 8;
            SpiTxBuf[1] = (DAC_I_Q[0][p] & 0x00FF);
            setDAC(SpiTxBuf);
            delay_us(5);
            SpiTxBuf[0] = (DAC_I_Q[1][p] & 0xFF00) >> 8;
            SpiTxBuf[1] = (DAC_I_Q[1][p] & 0x00FF);
            setDAC(SpiTxBuf);
            delay_us(5);
        }else if (p==4){//6.8G
            SpiTxBuf[0] = 0x00;
            SpiTxBuf[1] = 0x2A;
            SpiTxBuf[2] = 0x41;
            setPLL(SpiTxBuf);
            delay_us(5);
            SpiTxBuf[0] = (DAC_I_Q[0][p] & 0xFF00) >> 8;
            SpiTxBuf[1] = (DAC_I_Q[0][p] & 0x00FF);
            setDAC(SpiTxBuf);
            delay_us(5);
            SpiTxBuf[0] = (DAC_I_Q[1][p] & 0xFF00) >> 8;
            SpiTxBuf[1] = (DAC_I_Q[1][p] & 0x00FF);
            setDAC(SpiTxBuf);
            delay_us(5);
        }else{
            SpiTxBuf[0] = 0x00;
            SpiTxBuf[1] = 0x28;
            SpiTxBuf[2] = 0x01;
            setPLL(SpiTxBuf);
            delay_us(5);
            SpiTxBuf[0] = (DAC_I_Q[0][0] & 0xFF00) >> 8;
            SpiTxBuf[1] = (DAC_I_Q[0][0] & 0x00FF);
            setDAC(SpiTxBuf);
            delay_us(5);
            SpiTxBuf[0] = (DAC_I_Q[1][0] & 0xFF00) >> 8;
            SpiTxBuf[1] = (DAC_I_Q[1][0] & 0x00FF);
            setDAC(SpiTxBuf);
            delay_us(5);
        }
/*****************************I通道采样10个数平均*************************************/
        SpiTxBuf[0] = 0x2A;
        SpiTxBuf[1] = tst_amp*16+1;
        setPGA(SpiTxBuf);
        delay_us(5);
        AdcDataIAV = meanAD(meantimes);
        if(p>=0){
            TxBuffer[p*7+0]= row;
            TxBuffer[p*7+1]= col;
            TxBuffer[p*7+2] = ((AdcDataIAV & 0xFF00) >> 8);
            TxBuffer[p*7+3] = (AdcDataIAV & 0x00FF);
        }
/*****************************Q通道采样10个数平均*************************************/
        SpiTxBuf[0] = 0x2A;
        SpiTxBuf[1] = tst_amp*16+0;
        setPGA(SpiTxBuf);
        delay_us(5);
        AdcDataQAV = meanAD(meantimes);
        if(p>=0){
            TxBuffer[p*7+4] = ((AdcDataQAV & 0xFF00) >>8);
            TxBuffer[p*7+5] = (AdcDataQAV & 0x00FF);
            TxBuffer[p*7+6] = p+0xF0;
        }
    }
    if(WifiOrRs==0){
        Usart_SendStr_length(USART2,TxBuffer,35);
    }else{
        Usart_SendStr_length(USART1,TxBuffer,35);
    }
}
/****************************************************************************
* Function Name :   transdata_point
* Description   :   单频点AD数据上传
* Input         :   工作频点
* Output        :   二进制数TxBuffer：255，255，I通道数据，Q通道数据，频率
*****************************************************************************/
void transdata_point(uint8_t p){
    delay_us(20);
        if(p==0){//6.4G
            SpiTxBuf[0] = 0x00;
            SpiTxBuf[1] = 0x28;
            SpiTxBuf[2] = 0x01;
            setPLL(SpiTxBuf);
            delay_us(5);
            SpiTxBuf[0] = (DAC_I_Q[0][p] & 0xFF00) >> 8;
            SpiTxBuf[1] = (DAC_I_Q[0][p] & 0x00FF);
            setDAC(SpiTxBuf);
            delay_us(5);
            SpiTxBuf[0] = (DAC_I_Q[1][p] & 0xFF00) >> 8;
            SpiTxBuf[1] = (DAC_I_Q[1][p] & 0x00FF);
            setDAC(SpiTxBuf);
            delay_us(5);
        }else if (p==1){//6.5G
            SpiTxBuf[0] = 0x00;
            SpiTxBuf[1] = 0x28;
            SpiTxBuf[2] = 0x51;
            setPLL(SpiTxBuf);
            delay_us(5);
            SpiTxBuf[0] = (DAC_I_Q[0][p] & 0xFF00) >> 8;
            SpiTxBuf[1] = (DAC_I_Q[0][p] & 0x00FF);
            setDAC(SpiTxBuf);
            delay_us(5);
            SpiTxBuf[0] = (DAC_I_Q[1][p] & 0xFF00) >> 8;
            SpiTxBuf[1] = (DAC_I_Q[1][p] & 0x00FF);
            setDAC(SpiTxBuf);
            delay_us(5);
        }else if (p==2){//6.6G
            SpiTxBuf[0] = 0x00;
            SpiTxBuf[1] = 0x29;
            SpiTxBuf[2] = 0x21;
            setPLL(SpiTxBuf);
            delay_us(50);
            SpiTxBuf[0] = (DAC_I_Q[0][p] & 0xFF00) >> 8;
            SpiTxBuf[1] = (DAC_I_Q[0][p] & 0x00FF);
            setDAC(SpiTxBuf);
            delay_us(20);
            SpiTxBuf[0] = (DAC_I_Q[1][p] & 0xFF00) >> 8;
            SpiTxBuf[1] = (DAC_I_Q[1][p] & 0x00FF);
            setDAC(SpiTxBuf);
            delay_us(20);
        }else if (p==3){ //6.7G
            SpiTxBuf[0] = 0x00;
            SpiTxBuf[1] = 0x29;
            SpiTxBuf[2] = 0x71;
            setPLL(SpiTxBuf);
            delay_us(50);
            SpiTxBuf[0] = (DAC_I_Q[0][p] & 0xFF00) >> 8;
            SpiTxBuf[1] = (DAC_I_Q[0][p] & 0x00FF);
            setDAC(SpiTxBuf);
            delay_us(20);
            SpiTxBuf[0] = (DAC_I_Q[1][p] & 0xFF00) >> 8;
            SpiTxBuf[1] = (DAC_I_Q[1][p] & 0x00FF);
            setDAC(SpiTxBuf);
            delay_us(20);
        }else if (p==4){//6.8G
            SpiTxBuf[0] = 0x00;
            SpiTxBuf[1] = 0x2A;
            SpiTxBuf[2] = 0x41;
            setPLL(SpiTxBuf);
            delay_us(50);
            SpiTxBuf[0] = (DAC_I_Q[0][p] & 0xFF00) >> 8;
            SpiTxBuf[1] = (DAC_I_Q[0][p] & 0x00FF);
            setDAC(SpiTxBuf);
            delay_us(20);
            SpiTxBuf[0] = (DAC_I_Q[1][p] & 0xFF00) >> 8;
            SpiTxBuf[1] = (DAC_I_Q[1][p] & 0x00FF);
            setDAC(SpiTxBuf);
            delay_us(20);
        }else{
            SpiTxBuf[0] = 0x00;
            SpiTxBuf[1] = 0x28;
            SpiTxBuf[2] = 0x01;
            setPLL(SpiTxBuf);
            delay_us(50);
            SpiTxBuf[0] = (DAC_I_Q[0][0] & 0xFF00) >> 8;
            SpiTxBuf[1] = (DAC_I_Q[0][0] & 0x00FF);
            setDAC(SpiTxBuf);
            delay_us(20);
            SpiTxBuf[0] = (DAC_I_Q[1][0] & 0xFF00) >> 8;
            SpiTxBuf[1] = (DAC_I_Q[1][0] & 0x00FF);
            setDAC(SpiTxBuf);
            delay_us(20);
        }
/*****************************I通道采样10个数平均*************************************/
        SpiTxBuf[0] = 0x2A;
        SpiTxBuf[1] = tst_amp*16+1;
        setPGA(SpiTxBuf);
        delay_us(20);
        AdcDataIAV = meanAD(meantimes);
        delay_us(20);
        TxBuffer[p*7]=0xFF;  //
        TxBuffer[p*7+1]=0xFF;  //
        TxBuffer[p*7+2] = ((AdcDataIAV & 0xFF00) >> 8) ;
        TxBuffer[p*7+3] = (AdcDataIAV & 0x00FF);
/*****************************Q通道采样10个数平均*************************************/
        SpiTxBuf[0] = 0x2A;
        SpiTxBuf[1] = tst_amp*16+0;
        setPGA(SpiTxBuf);
        delay_us(20);
        AdcDataQAV = meanAD(meantimes);
        delay_us(20);
        TxBuffer[p*7+4] = ((AdcDataQAV & 0xFF00) >>8) ;
        TxBuffer[p*7+5] = (AdcDataQAV & 0x00FF) ;
        TxBuffer[p*7+6]=p;
        if(WifiOrRs==0){
            Usart_SendStr_length(USART2,TxBuffer,35);
        }else{
            Usart_SendStr_length(USART1,TxBuffer,35);
        }
}
/****************************************************************************
* Function Name :   transdata_reverse
* Description   :   5频点AD数据上传,反向扫描频点
* Input         :   电机位置（行，列）
* Output        :   二进制数TxBuffer：行，列，I通道数据，Q通道数据，频率
*****************************************************************************/
void transdata_reverse(uint8_t row,uint8_t col){
    int8_t p = 0;
//    delay_us(1);
    for(p=0; p<3; p++){//5
        if(p==0){//6.8G
            SpiTxBuf[0] = 0x00;
            SpiTxBuf[1] = 0x2A;
            SpiTxBuf[2] = 0x41;
            setPLL(SpiTxBuf);
//            delay_us(1);
            SpiTxBuf[0] = (DAC_I_Q[0][4-p] & 0xFF00) >> 8;
            SpiTxBuf[1] = (DAC_I_Q[0][4-p] & 0x00FF);
            setDAC(SpiTxBuf);
            delay_us(1);
            SpiTxBuf[0] = (DAC_I_Q[1][4-p] & 0xFF00) >> 8;
            SpiTxBuf[1] = (DAC_I_Q[1][4-p] & 0x00FF);
            setDAC(SpiTxBuf);
//            delay_us(1);
        }else if (p==1){//6.7G
            SpiTxBuf[0] = 0x00;
            SpiTxBuf[1] = 0x29;
            SpiTxBuf[2] = 0x71;
            setPLL(SpiTxBuf);
//            delay_us(1);
            SpiTxBuf[0] = (DAC_I_Q[0][4-p] & 0xFF00) >> 8;
            SpiTxBuf[1] = (DAC_I_Q[0][4-p] & 0x00FF);
            setDAC(SpiTxBuf);
//            delay_us(1);
            SpiTxBuf[0] = (DAC_I_Q[1][4-p] & 0xFF00) >> 8;
            SpiTxBuf[1] = (DAC_I_Q[1][4-p] & 0x00FF);
            setDAC(SpiTxBuf);
//            delay_us(1);
        }else if (p==2){//6.6G
            SpiTxBuf[0] = 0x00;
            SpiTxBuf[1] = 0x29;
            SpiTxBuf[2] = 0x21;
            setPLL(SpiTxBuf);
 //           delay_us(1);
            SpiTxBuf[0] = (DAC_I_Q[0][4-p] & 0xFF00) >> 8;
            SpiTxBuf[1] = (DAC_I_Q[0][4-p] & 0x00FF);
            setDAC(SpiTxBuf);
//            delay_us(1);
            SpiTxBuf[0] = (DAC_I_Q[1][4-p] & 0xFF00) >> 8;
            SpiTxBuf[1] = (DAC_I_Q[1][4-p] & 0x00FF);
            setDAC(SpiTxBuf);
//            delay_us(1);
        }else if (p==3){//6.5G
            SpiTxBuf[0] = 0x00;
            SpiTxBuf[1] = 0x28;
            SpiTxBuf[2] = 0x51;
            setPLL(SpiTxBuf);
//            delay_us(1);
            SpiTxBuf[0] = (DAC_I_Q[0][4-p] & 0xFF00) >> 8;
            SpiTxBuf[1] = (DAC_I_Q[0][4-p] & 0x00FF);
            setDAC(SpiTxBuf);
//            delay_us(1);
            SpiTxBuf[0] = (DAC_I_Q[1][4-p] & 0xFF00) >> 8;
            SpiTxBuf[1] = (DAC_I_Q[1][4-p] & 0x00FF);
            setDAC(SpiTxBuf);
//            delay_us(1);
        }else if (p==4){//6.4G
            SpiTxBuf[0] = 0x00;
            SpiTxBuf[1] = 0x28;
            SpiTxBuf[2] = 0x01;
            setPLL(SpiTxBuf);
//            delay_us(1);
            SpiTxBuf[0] = (DAC_I_Q[0][4-p] & 0xFF00) >> 8;
            SpiTxBuf[1] = (DAC_I_Q[0][4-p] & 0x00FF);
            setDAC(SpiTxBuf);
//            delay_us(1);
            SpiTxBuf[0] = (DAC_I_Q[1][4-p] & 0xFF00) >> 8;
            SpiTxBuf[1] = (DAC_I_Q[1][4-p] & 0x00FF);
            setDAC(SpiTxBuf);
//            delay_us(1);
        }else{
            SpiTxBuf[0] = 0x00;
            SpiTxBuf[1] = 0x2A;
            SpiTxBuf[2] = 0x41;
            setPLL(SpiTxBuf);
//            delay_us(1);
            SpiTxBuf[0] = (DAC_I_Q[0][4] & 0xFF00) >> 8;
            SpiTxBuf[1] = (DAC_I_Q[0][4] & 0x00FF);
            setDAC(SpiTxBuf);
//            delay_us(1);
            SpiTxBuf[0] = (DAC_I_Q[1][4] & 0xFF00) >> 8;
            SpiTxBuf[1] = (DAC_I_Q[1][4] & 0x00FF);
            setDAC(SpiTxBuf);
//            delay_us(1);
        }
/*****************************I通道采样10个数平均*************************************/
        SpiTxBuf[0] = 0x2A;
        SpiTxBuf[1] = tst_amp*16+1;
        setPGA(SpiTxBuf);
//        delay_us(1);
        AdcDataIAV = meanAD(meantimes);
        if(p>=0){
            TxBuffer[(2-p)*7+0]= row;
            TxBuffer[(2-p)*7+1]= col;
            TxBuffer[(2-p)*7+2] = ((AdcDataIAV & 0xFF00) >> 8);
            TxBuffer[(2-p)*7+3] = (AdcDataIAV & 0x00FF);
        }
/*****************************Q通道采样10个数平均*************************************/
        SpiTxBuf[0] = 0x2A;
        SpiTxBuf[1] = tst_amp*16+0;
        setPGA(SpiTxBuf);
//        delay_us(1);
        AdcDataQAV = meanAD(meantimes);
        if(p>=0){
            TxBuffer[(2-p)*7+4] = ((AdcDataQAV & 0xFF00) >>8);
            TxBuffer[(2-p)*7+5] = (AdcDataQAV & 0x00FF);
            TxBuffer[(2-p)*7+6] = (2-p)+0xF0;
        }
    }
    if(WifiOrRs==0){
        Usart_SendStr_length(USART2,TxBuffer,21);
    }else{
        Usart_SendStr_length(USART1,TxBuffer,21);
    }
}
/****************************************************************************
* Function Name :   transdata
* Description   :   5频点AD数据上传
* Input         :   电机位置（行，列）
* Output        :   二进制数TxBuffer：行，列，I通道数据，Q通道数据，频率
*****************************************************************************/
void transdata_t(uint8_t row,uint8_t col){
    int8_t p = 0;
    delay_us(5);
    for(p=0; p<5; p++){//5
        if(p==0){//6.4G
            SpiTxBuf[0] = 0x00;
            SpiTxBuf[1] = 0x28;
            SpiTxBuf[2] = 0x01;
            setPLL(SpiTxBuf);
            delay_us(5);
            SpiTxBuf[0] = (DAC_I_Q[0][p] & 0xFF00) >> 8;
            SpiTxBuf[1] = (DAC_I_Q[0][p] & 0x00FF);
            setDAC(SpiTxBuf);
            delay_us(5);
            SpiTxBuf[0] = (DAC_I_Q[1][p] & 0xFF00) >> 8;
            SpiTxBuf[1] = (DAC_I_Q[1][p] & 0x00FF);
            setDAC(SpiTxBuf);
            delay_us(5);
        }else if (p==1){//6.5G
            SpiTxBuf[0] = 0x00;
            SpiTxBuf[1] = 0x28;
            SpiTxBuf[2] = 0x51;
            setPLL(SpiTxBuf);
            delay_us(5);
            SpiTxBuf[0] = (DAC_I_Q[0][p] & 0xFF00) >> 8;
            SpiTxBuf[1] = (DAC_I_Q[0][p] & 0x00FF);
            setDAC(SpiTxBuf);
            delay_us(5);
            SpiTxBuf[0] = (DAC_I_Q[1][p] & 0xFF00) >> 8;
            SpiTxBuf[1] = (DAC_I_Q[1][p] & 0x00FF);
            setDAC(SpiTxBuf);
            delay_us(5);
        }else if (p==2){//6.6G
            SpiTxBuf[0] = 0x00;
            SpiTxBuf[1] = 0x29;
            SpiTxBuf[2] = 0x21;
            setPLL(SpiTxBuf);
            delay_us(5);
            SpiTxBuf[0] = (DAC_I_Q[0][p] & 0xFF00) >> 8;
            SpiTxBuf[1] = (DAC_I_Q[0][p] & 0x00FF);
            setDAC(SpiTxBuf);
            delay_us(5);
            SpiTxBuf[0] = (DAC_I_Q[1][p] & 0xFF00) >> 8;
            SpiTxBuf[1] = (DAC_I_Q[1][p] & 0x00FF);
            setDAC(SpiTxBuf);
            delay_us(5);
        }else if (p==3){//6.7G
            SpiTxBuf[0] = 0x00;
            SpiTxBuf[1] = 0x29;
            SpiTxBuf[2] = 0x71;
            setPLL(SpiTxBuf);
            delay_us(5);
            SpiTxBuf[0] = (DAC_I_Q[0][p] & 0xFF00) >> 8;
            SpiTxBuf[1] = (DAC_I_Q[0][p] & 0x00FF);
            setDAC(SpiTxBuf);
            delay_us(5);
            SpiTxBuf[0] = (DAC_I_Q[1][p] & 0xFF00) >> 8;
            SpiTxBuf[1] = (DAC_I_Q[1][p] & 0x00FF);
            setDAC(SpiTxBuf);
            delay_us(5);
        }else if (p==4){//6.8G
            SpiTxBuf[0] = 0x00;
            SpiTxBuf[1] = 0x2A;
            SpiTxBuf[2] = 0x41;
            setPLL(SpiTxBuf);
            delay_us(5);
            SpiTxBuf[0] = (DAC_I_Q[0][p] & 0xFF00) >> 8;
            SpiTxBuf[1] = (DAC_I_Q[0][p] & 0x00FF);
            setDAC(SpiTxBuf);
            delay_us(5);
            SpiTxBuf[0] = (DAC_I_Q[1][p] & 0xFF00) >> 8;
            SpiTxBuf[1] = (DAC_I_Q[1][p] & 0x00FF);
            setDAC(SpiTxBuf);
            delay_us(5);
        }else{
            SpiTxBuf[0] = 0x00;
            SpiTxBuf[1] = 0x28;
            SpiTxBuf[2] = 0x01;
            setPLL(SpiTxBuf);
            delay_us(5);
            SpiTxBuf[0] = (DAC_I_Q[0][0] & 0xFF00) >> 8;
            SpiTxBuf[1] = (DAC_I_Q[0][0] & 0x00FF);
            setDAC(SpiTxBuf);
            delay_us(5);
            SpiTxBuf[0] = (DAC_I_Q[1][0] & 0xFF00) >> 8;
            SpiTxBuf[1] = (DAC_I_Q[1][0] & 0x00FF);
            setDAC(SpiTxBuf);
            delay_us(5);
        }
/*****************************I通道采样10个数平均*************************************/
        SpiTxBuf[0] = 0x2A;
        SpiTxBuf[1] = tst_amp*16+1;
        setPGA(SpiTxBuf);
        delay_us(5);
        AdcDataIAV = meanAD(meantimes);
        if(p>=0){
            TxBuffer[p*7+0]= row;
            TxBuffer[p*7+1]= col;
            TxBuffer[p*7+2] = ((AdcDataIAV & 0xFF00) >> 8);
            TxBuffer[p*7+3] = (AdcDataIAV & 0x00FF);
        }
/*****************************Q通道采样10个数平均*************************************/
        SpiTxBuf[0] = 0x2A;
        SpiTxBuf[1] = tst_amp*16+0;
        setPGA(SpiTxBuf);
        delay_us(5);
        AdcDataQAV = meanAD(meantimes);
        if(p>=0){
            TxBuffer[p*7+4] = ((AdcDataQAV & 0xFF00) >>8);
            TxBuffer[p*7+5] = (AdcDataQAV & 0x00FF);
            TxBuffer[p*7+6] = p+0xF0;
        }
    }
    if(WifiOrRs==0){
        Usart_SendStr_length(USART2,TxBuffer,7);
    }else{
        Usart_SendStr_length(USART1,TxBuffer,7);
    }
}
/****************************************************************************
* Function Name :   transdata_point_t
* Description   :   单频点AD数据上传
* Input         :   工作频点
* Output        :   二进制数TxBuffer：255，255，I通道数据，Q通道数据，频率
*****************************************************************************/
void transdata_point_t(uint8_t p,uint8_t row,uint8_t col){
    delay_us(20);
        if(p==0){//6.4G
            SpiTxBuf[0] = 0x00;
            SpiTxBuf[1] = 0x28;
            SpiTxBuf[2] = 0x01;
            setPLL(SpiTxBuf);
            delay_us(5);
            SpiTxBuf[0] = (DAC_I_Q[0][p] & 0xFF00) >> 8;
            SpiTxBuf[1] = (DAC_I_Q[0][p] & 0x00FF);
            setDAC(SpiTxBuf);
            delay_us(5);
            SpiTxBuf[0] = (DAC_I_Q[1][p] & 0xFF00) >> 8;
            SpiTxBuf[1] = (DAC_I_Q[1][p] & 0x00FF);
            setDAC(SpiTxBuf);
            delay_us(5);
        }else if (p==1){//6.5G
            SpiTxBuf[0] = 0x00;
            SpiTxBuf[1] = 0x28;
            SpiTxBuf[2] = 0x51;
            setPLL(SpiTxBuf);
            delay_us(5);
            SpiTxBuf[0] = (DAC_I_Q[0][p] & 0xFF00) >> 8;
            SpiTxBuf[1] = (DAC_I_Q[0][p] & 0x00FF);
            setDAC(SpiTxBuf);
            delay_us(5);
            SpiTxBuf[0] = (DAC_I_Q[1][p] & 0xFF00) >> 8;
            SpiTxBuf[1] = (DAC_I_Q[1][p] & 0x00FF);
            setDAC(SpiTxBuf);
            delay_us(5);
        }else if (p==2){//6.6G
            SpiTxBuf[0] = 0x00;
            SpiTxBuf[1] = 0x29;
            SpiTxBuf[2] = 0x21;
            setPLL(SpiTxBuf);
            delay_us(50);
            SpiTxBuf[0] = (DAC_I_Q[0][p] & 0xFF00) >> 8;
            SpiTxBuf[1] = (DAC_I_Q[0][p] & 0x00FF);
            setDAC(SpiTxBuf);
            delay_us(20);
            SpiTxBuf[0] = (DAC_I_Q[1][p] & 0xFF00) >> 8;
            SpiTxBuf[1] = (DAC_I_Q[1][p] & 0x00FF);
            setDAC(SpiTxBuf);
            delay_us(20);
        }else if (p==3){ //6.7G
            SpiTxBuf[0] = 0x00;
            SpiTxBuf[1] = 0x29;
            SpiTxBuf[2] = 0x71;
            setPLL(SpiTxBuf);
            delay_us(50);
            SpiTxBuf[0] = (DAC_I_Q[0][p] & 0xFF00) >> 8;
            SpiTxBuf[1] = (DAC_I_Q[0][p] & 0x00FF);
            setDAC(SpiTxBuf);
            delay_us(20);
            SpiTxBuf[0] = (DAC_I_Q[1][p] & 0xFF00) >> 8;
            SpiTxBuf[1] = (DAC_I_Q[1][p] & 0x00FF);
            setDAC(SpiTxBuf);
            delay_us(20);
        }else if (p==4){//6.8G
            SpiTxBuf[0] = 0x00;
            SpiTxBuf[1] = 0x2A;
            SpiTxBuf[2] = 0x41;
            setPLL(SpiTxBuf);
            delay_us(50);
            SpiTxBuf[0] = (DAC_I_Q[0][p] & 0xFF00) >> 8;
            SpiTxBuf[1] = (DAC_I_Q[0][p] & 0x00FF);
            setDAC(SpiTxBuf);
            delay_us(20);
            SpiTxBuf[0] = (DAC_I_Q[1][p] & 0xFF00) >> 8;
            SpiTxBuf[1] = (DAC_I_Q[1][p] & 0x00FF);
            setDAC(SpiTxBuf);
            delay_us(20);
        }else{
            SpiTxBuf[0] = 0x00;
            SpiTxBuf[1] = 0x28;
            SpiTxBuf[2] = 0x01;
            setPLL(SpiTxBuf);
            delay_us(50);
            SpiTxBuf[0] = (DAC_I_Q[0][0] & 0xFF00) >> 8;
            SpiTxBuf[1] = (DAC_I_Q[0][0] & 0x00FF);
            setDAC(SpiTxBuf);
            delay_us(20);
            SpiTxBuf[0] = (DAC_I_Q[1][0] & 0xFF00) >> 8;
            SpiTxBuf[1] = (DAC_I_Q[1][0] & 0x00FF);
            setDAC(SpiTxBuf);
            delay_us(20);
        }
/*****************************I通道采样10个数平均*************************************/
        SpiTxBuf[0] = 0x2A;
        SpiTxBuf[1] = tst_amp*16+1;
        setPGA(SpiTxBuf);
        delay_us(20);
        AdcDataIAV = meanAD(meantimes);
        delay_us(20);
        TxBuffer[0]=0xFF;  //
        TxBuffer[1]=row;  //方位向移动
        TxBuffer[2] = ((AdcDataIAV & 0xFF00) >> 8) ;
        TxBuffer[3] = (AdcDataIAV & 0x00FF);
/*****************************Q通道采样10个数平均*************************************/
        SpiTxBuf[0] = 0x2A;
        SpiTxBuf[1] = tst_amp*16+0;
        setPGA(SpiTxBuf);
        delay_us(20);
        AdcDataQAV = meanAD(meantimes);
        delay_us(20);
        TxBuffer[4] = ((AdcDataQAV & 0xFF00) >>8) ;
        TxBuffer[5] = (AdcDataQAV & 0x00FF) ;
        TxBuffer[6]=p;//频点
		TxBuffer[7]=col;//角度
        if(WifiOrRs==0){
            Usart_SendStr_length(USART2,TxBuffer,8);
        }else{
            Usart_SendStr_length(USART1,TxBuffer,8);
        }
}
