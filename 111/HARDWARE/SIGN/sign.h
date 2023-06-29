#ifndef _SIGN_H
#define _SIGN_H
#include "stm32f10x.h"
#include "stdio.h"
#include "string.h"
#include "math.h"
#include "sys.h"
#include "stm32f10x_dac.h"
#include "stm32f10x_dma.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"
        
/******DAC�Ĵ�����ַ����*******/  
#define DAC_DHR12R1    (u32)&(DAC->DHR12R1)   //DACͨ��1�����ַ
#define DAC_DHR12R2    (u32)&(DAC->DHR12R2)   //DACͨ��2�����ַ

/********���Ҳ������***********/
void Sine_Wave_Data(u16 cycle ,u16 *D_Sine,float Um);
void Square_Wave_Data(u16 cycle ,u16 *D_Square,float Um);
/****************��ʼ������******************/
void SineWave_GPIO_Config(void);

/******************DAC��ʼ����*************************/
void SineWave_DAC_Config( void);

/*********��ʱ����ʼ��************/
void Wave_TIM_Config(u32 Wave1_Fre);

/*********DMA����***********/
void Sine_Wave_DMA_Config(void);
void Square_Wave_DMA_Config(void);
void Triangular_Wave_DMA_Config(void);
    
/**********���Ҳ���ʼ��*****/
void Sine_Wave_Init(u16 freq,float Um);
/**********���ǲ���ʼ��*****/
void Triangular_Wave_Init(u16 Freq,float Um);
/**********������ʼ��*****/
void Square_Wave_Init(u16 freq,float Um);

#endif
