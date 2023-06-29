#include "key.h"
#include "delay.h"

#define KEY11 GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1)
#define KEY22 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2)
#define KEY33 GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_6)
#define KEY41 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3)
#define KEY42 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)
#define KEY51 GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_3)
#define KEY52 GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5)
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK Mini STM32������
//�������� ��������		   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2014/3/06
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									   
//////////////////////////////////////////////////////////////////////////////////	 
 	    
//������ʼ������ 
//PA15��PC5 ���ó�����
void KEY_Init(void)
{
	
		GPIO_InitTypeDef GPIO_InitStructure;

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC,ENABLE);//ʹ��PORTA,PORTCʱ��

		GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//�ر�jtag��ʹ��SWD��������SWDģʽ����
		
		GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1;//PC1
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
		GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIOC1
		
		GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2;//PA2
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
		GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA2
	 
		GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6;//PC6
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
		GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��

		GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_3;//PA3
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
		GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA3
		
		GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_5;//PA5
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
		GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA5
		
		GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_3;//PC3
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
		GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIOC3
		
		GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_5;//PC5
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
		GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIOC5
} 
//����������
//���ذ���ֵ
//mode:0,��֧��������;1,֧��������;
//����ֵ��
//0��û���κΰ�������
//KEY0_PRES��KEY0����
//KEY1_PRES��KEY1����
//WKUP_PRES��WK_UP���� 
//ע��˺�������Ӧ���ȼ�,KEY0>KEY1>WK_UP!!

	u8 KEY_Scan(u8 mode)
	{	 
		static u8 key_up=1;//�������ɿ���־
		if(mode)key_up=1;  //֧������		  
		if(key_up&&(KEY11==0||KEY22==0||KEY33==0))
		{
			delay_ms(10);//ȥ���� 
			key_up=0;
			if(KEY11==0)return KEY0_PRES;
			else if(KEY22==0)return KEY1_PRES;
			else if(KEY33==0)return WKUP_PRES; 
		}else if(KEY11==1&&KEY22==1&&KEY33==1)key_up=1; 	     
		return 0;// �ް�������
	}
