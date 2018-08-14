/****************************************************************************
* Function Name :
* Description   :
* Input         :
* Output        :
*****************************************************************************/
#include "command.h"
#include "public.h"

extern uint8_t  System_ID[12];
extern  uint8_t     KeyLongFlag;//长按标志 2018-03-21
extern uint8_t  MoveLength;
extern uint8_t  MoveFlag;
extern uint32_t delay;
extern uint8_t  MoveFrePoint;
extern uint8_t  WheelMoveNum;

void CommandResolution(void){
    static char CmdRxBuffer[20];
    static char CmdRxEnd;
//    static int  i;
    /* static uint8_t TempBuf[8]; */
    if(CmdRxEndUart1==1){
        strcpy(CmdRxBuffer,CmdRxBufferUart1);
        CmdRxEnd    = CmdRxEndUart1;
        CmdRecvOKUart2 = 0;
        CmdRecvOKUart4 = 0;
        CommandBufferClear();
    }else if(CmdRxEndUart2==1){
        strcpy(CmdRxBuffer,CmdRxBufferUart2);
        CmdRxEnd    = CmdRxEndUart2;
        CmdRecvOKUart1 = 0;
        CmdRecvOKUart4 = 0;
        CommandBufferClear();
    }else if(CmdRxEndUart4==1){
        strcpy(CmdRxBuffer,CmdRxBufferUart4);
        CmdRxEnd    = CmdRxEndUart4;
        CmdRecvOKUart1 = 0;
        CmdRecvOKUart2 = 0;
        CommandBufferClear();
    }else{
        strcpy(CmdRxBuffer,CmdRxBufferUart2);
        CmdRxEnd    = CmdRxEndUart2;
        CmdRecvOKUart1 = 0;
        CmdRecvOKUart4 = 0;
    }
    if((strncmp(CmdRxBuffer,"#CHANNEL=",9)==0)&&(CmdRxEnd==1)){               //#CHANNEL=WIFI\r\n
//        strncpy(CmdTemp,CmdRxBuffer+9,5);
        if(strncmp(CmdRxBuffer+9,"WIFI",4)==0){
            Usart_SendString(USART2,"$W+OK\r\n");
            WifiOrRs=0;
            ReadSystemID();
            CheckSystemID();
        }else if(strncmp(CmdRxBuffer+9,"UART",4)==0){
            Usart_SendString(USART1,"$U+OK\r\n");
            WifiOrRs=1;
            ReadSystemID();
            CheckSystemID();
        }else{
            Usart_SendString(USART1,"$+ERR\r\n");
            Usart_SendString(USART2,"$+ERR\r\n");
            ReadSystemID();
            CheckSystemID();
        }
    }else if((strncmp(CmdRxBuffer,"#VERSION",8)==0)&&(CmdRxEnd==1)){              //版本查询命令#version
            if(WifiOrRs==0){
                Usart_SendString(USART2,"$1.151CETC50\r\n");
            }else{
                Usart_SendString(USART1,"$1.151CETC50\r\n");
            }
            SystemReset = 1;
    }else if((strncmp(CmdRxBuffer,"#SYSTEMID",9)==0)&&(CmdRxEnd==1)){              //版本查询命令#systemid
            ReadSystemID();
            Usart_SendStr_length(USART1,System_ID,12);
    }else if((strncmp(CmdRxBuffer,"#RESET",6)==0)&&(CmdRxEnd==1)){              //复位命令#RESET
            if(WifiOrRs==0){
                Usart_SendString(USART2,"$R+OK\r\n");
            }else{
                Usart_SendString(USART1,"$R+OK\r\n");
            }
            SystemReset = 1;
    }else if((strncmp(CmdRxBuffer,"#SETDAC=",8)==0)&&(CmdRxEnd==1)){                 //DAC控制
        static int channel,f;
        channel= char2hex(CmdRxBuffer,9,1);//IQ切换
        f= char2hex(CmdRxBuffer,8,1);//频点切换
        DACBuf[0] = char2hex(CmdRxBuffer,9,2);
        DACBuf[1] = char2hex(CmdRxBuffer,11,2);
        DAC_I_Q[channel][f]=char2hex(CmdRxBuffer,9,4); //5频点IQ控制命令寄存器
        setDAC(DACBuf);
    }else if((strncmp(CmdRxBuffer,"#SETPGA=",8)==0)&&(CmdRxEnd==1)){         //PGA控制
        if(WifiOrRs==0){
            Usart_SendString(USART2,"$P+OK\r\n");
        }else{
            Usart_SendString(USART1,"$P+OK\r\n");
        }
        tst_amp     = CmdRxBuffer[8]-0x30;
        PGABuf[0]   = 0x2A;
        PGABuf[1]   = tst_amp*16+1;
        setPGA(PGABuf);
    }else if((strncmp(CmdRxBuffer,"#SETHMC=",7)==0)&&(CmdRxEnd==1)){        //HMC控制#SIG:HMC:
        delay_ms(10);
        if(WifiOrRs==0){
            Usart_SendString(USART2,"$H+OK\r\n");
        }else{
            Usart_SendString(USART1,"$H+OK\r\n");
        }
        HMCBuf[0] = char2hex(CmdRxBuffer,8,2);
        setHMC(HMCBuf);
    }else if((strncmp(CmdRxBuffer,"#CALIBRATION",12)==0)&&(CmdRxEnd==1)){         //单次校准
        if(strncmp(CmdRxBuffer+12,"=",1)==0){
            SignalModeEn    = 2;
            SignalPoint     = char2hex(CmdRxBuffer,13,1);
            if(strncmp(CmdRxBuffer+13,"OK",2)==0){
                CalibrationEnd = 1;
                KeyLongFlag = 0;//当校准结束后关闭长按指令
            }
        }else if(strncmp(CmdRxBuffer+12,"\r\n",2)==0){
            SignalModeEn    = 1;
        }else{
        }
    }else if((strncmp(CmdRxBuffer,"#MEANTIMES=",11)==0)&&(CmdRxEnd==1)){        //平均次数
        delay_ms(10);
        if(WifiOrRs==0){
            Usart_SendString(USART2,"$M+OK\r\n");
        }else{
            Usart_SendString(USART1,"$M+OK\r\n");
        }
        meantimes   = CmdRxBuffer[11]-0x30;
    }else if((strncmp(CmdRxBuffer,"#LENGTH=",8)==0)&&(CmdRxEnd==1)){        //设备移动距离
        delay_ms(10);
        if(WifiOrRs==0){
            Usart_SendString(USART2,"$L+OK\r\n");
        }else{
            Usart_SendString(USART1,"$L+OK\r\n");
        }
        MoveLength  = char2hex(CmdRxBuffer,8,3);
    }else if((strncmp(CmdRxBuffer,"#MOTORDELAY=",11)==0)&&(CmdRxEnd==1)){        //电机工作校准延迟
        if(WifiOrRs==0){
            Usart_SendString(USART2,"$#M+OK\r\n");
        }else{
            Usart_SendString(USART1,"$#M+OK\r\n");
        }
        delay=char2hex(CmdRxBuffer,12,4);//us
    }else if((strncmp(CmdRxBuffer,"#BATTERY",8)==0)&&(CmdRxEnd==1)){        //电压测试开始
        ad_flag=1;
    }else if((strncmp(CmdRxBuffer,"#MOTOR=",7)==0)&&(CmdRxEnd==1)){        //电机控制命令#MTR:
        if(WifiOrRs==0){
            Usart_SendString(USART2,"$M+OK\r\n");
        }else{
            Usart_SendString(USART1,"$M+OK\r\n");
        }
        TxBuffer[0] = CmdRxBuffer[7];
        TxBuffer[1] = CmdRxBuffer[8];
        TxBuffer[2] = CmdRxBuffer[9];
        TxBuffer[3] = CmdRxBuffer[10];
        TxBuffer[4] = CmdRxBuffer[11];
        TxBuffer[5] = CmdRxBuffer[12];
        TxBuffer[6] = CmdRxBuffer[13];
        TxBuffer[7] = CmdRxBuffer[14];
        TxBuffer[8] = CmdRxBuffer[15];
        TxBuffer[9] = CmdRxBuffer[16];
        Usart_SendStr_length(UART4,TxBuffer,10);
    }else if((strncmp(CmdRxBuffer,"#MOTORSTART=",12)==0)&&(CmdRxEnd==1)){        //电机工作开始
        if(strncmp(CmdRxBuffer+12,"2",1)==0){
            if(WifiOrRs==0){
                Usart_SendString(USART2,"$M+OK\r\n");
            }else{
                Usart_SendString(USART1,"$M+OK\r\n");
            }
            delay_ms(10);
            MoveFlag = char2hex(CmdRxBuffer,12,1);
            MoveFrePoint = char2hex(CmdRxBuffer,13,1);
        }else if(strncmp(CmdRxBuffer+12,"5",1)==0){
            if(WifiOrRs==0){
                Usart_SendString(USART2,"$M+OK\r\n");
            }else{
                Usart_SendString(USART1,"$M+OK\r\n");
            }
            delay_ms(10);
            MoveFlag = char2hex(CmdRxBuffer,12,1);
        }else{
            if(WifiOrRs==0){
                Usart_SendString(USART2,"$+ERR\r\n");
            }else{
                Usart_SendString(USART1,"$+ERR\r\n");
            }
        }
    }else if((strncmp(CmdRxBuffer,"#CIRCLESTART=",13)==0)&&(CmdRxEnd==1)){        //电机工作开始
        if(WifiOrRs==0){
            Usart_SendString(USART2,"$M+OK\r\n");
        }else{
            Usart_SendString(USART1,"$M+OK\r\n");
        }
        delay_ms(10);
        MoveFrePoint = char2hex(CmdRxBuffer,13,1);
        WheelMoveNum = 0;//开始扫描时刻计数器清零:
        transdata_point_p1(MoveFrePoint);
    }else if((strncmp(CmdRxBuffer,"#CALI",5)==0)&&(CmdRxEnd==1)){        //自动开始校准工作
        delay_ms(10);
        calibration();
    }
/****************END********************************/
    CmdRxEndUart1 = 0;
    CmdLFUart1 = 0;
    CmdRxEndUart2 = 0;
    CmdLFUart2 = 0;
    CmdRxEndUart4 = 0;
    CmdLFUart4 = 0;
}

void CommandRxEndUart1(void){
    if(CmdRxStartUart1){
        if(CmdRxCntUart1 < sizeof(CmdRxBufferUart1)){
            CmdRxBufferUart1[CmdRxCntUart1++] = CmdRxTempUart1;
        }else{
            CmdRxCntUart1 = 0;
        }
        if(CmdRxBufferUart1[0]!= '#'){
            CmdRxCntUart1 = 0;
        }
        if(CmdRxTempUart1 == 0x0A){//換行符0x0D 0x0A
            if(CmdLFUart1==0){//command lind feed flag
                CmdLFUart1 = 1;
            /* }else{ */
                CmdRecvOKUart1 = 1;
            }
            CmdRxCntUart1 = 0;
            CmdRxEndUart1 = 1;
        }
        CmdRxStartUart1 = 0;//接收完成後，起始標志位歸零，等待下一次信號。
    }
}

void CommandRxEndUart2(void){
    if(CmdRxStartUart2){
        if(CmdRxCntUart2 < sizeof(CmdRxBufferUart2)){
            CmdRxBufferUart2[CmdRxCntUart2++] = CmdRxTempUart2;
        }else{
            CmdRxCntUart2 = 0;
        }
        if(CmdRxBufferUart2[0]!= '#'){
            CmdRxCntUart2 = 0;
        }
        if(CmdRxTempUart2 == 0x0A){//換行符0x0D 0x0A
            if(CmdLFUart2==0){//command lind feed flag
                CmdLFUart2 = 1;
            /* }else{ */
                CmdRecvOKUart2 = 1;
            }
            CmdRxCntUart2 = 0;
            CmdRxEndUart2 = 1;
        }
        CmdRxStartUart2 = 0;//接收完成後，起始標志位歸零，等待下一次信號。
    }
}

void CommandRxEndUart4(void){
    if(CmdRxStartUart4){
        if(CmdRxCntUart4 < sizeof(CmdRxBufferUart4)){
            CmdRxBufferUart4[CmdRxCntUart4++] = CmdRxTempUart4;
        }else{
            CmdRxCntUart4 = 0;
        }
//        if(CmdRxBufferUart4[0]!= '#'){
//            CmdRxCntUart4 = 0;
//        }
        if(CmdRxTempUart4 == 0x0A){//換行符0x0D 0x0A
            if(CmdLFUart4==0){//command lind feed flag
                CmdLFUart4 = 1;
                CmdRecvOKUart4 = 1;
            }
            CmdRxCntUart4 = 0;
            CmdRxEndUart4 = 1;
        }
        CmdRxStartUart4 = 0;//接收完成後，起始標志位歸零，等待下一次信號。
    }
}
void CommandBufferClear(void){
    static uint8_t i;
    for(i=0;i<sizeof(CmdRxBufferUart2);i++){
        CmdRxBufferUart2[i]=0;
        CmdRxBufferUart1[i]=0;
//        CmdRxBufferUart4[i]=0;
    }
}
