/***************************************************************************
File		: adc.c
Author		: ZhangYiPeng
Date		: 2018-03-01 10:25:22
Description : 配置adc初始化及读取模块
    -adc1 pc0 通道10
****************************************************************************/

#include "adc.h"

void adc_init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_ADC1,ENABLE);

	RCC_ADCCLKConfig(RCC_PCLK2_Div6);//12M  adc分频72/6=12.

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;//ADC
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AIN;	//模拟输入引脚
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);

    ADC_DeInit(ADC1);//复位adc1寄存器

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;//ADC工作模式：ADC1和ADC2工作在独立模式
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;//模数转换工作在单通道模式
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;//模数转换工作在单词转换模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//转换由软件而不是外部触发启动
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//ADC数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel = 1;//顺序进行规则转换的ADC通道的数目
	ADC_Init(ADC1, &ADC_InitStructure);

	/* ADC_RegularChannelConfig(ADC1,ADC_Channel_1,1,ADC_SampleTime_239Cycles5); */

	ADC_Cmd(ADC1,ENABLE);//使能adc

	ADC_ResetCalibration(ADC1);//使能复位校准
	while(ADC_GetResetCalibrationStatus(ADC1));//等待复位校准结束
	ADC_StartCalibration(ADC1);//开启AD校准
	while(ADC_GetCalibrationStatus(ADC1));//等待校准结束


}

u16 Get_Adc(u8 ch){//设置指定ADC的规则组通道，一个序列，采样时间
    ADC_RegularChannelConfig(ADC1,ch,1,ADC_SampleTime_239Cycles5);//ADC1，adc通道，采样时间为239.5
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);//使能指定的adc1的软件转换启动功能
    while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC));//等待转换结束
    return ADC_GetConversionValue(ADC1);
}

