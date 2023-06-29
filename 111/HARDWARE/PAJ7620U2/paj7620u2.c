#include "paj7620u2.h"
#include "paj7620u2_cfg.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "key.h"
#include "sign.h"
#include "menu.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK MiniV3 STM32������
//PAJ7620U2 ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2017/7/1
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////

//ѡ��PAJ7620U2 BANK����
void paj7620u2_selectBank(bank_e bank)
{
	switch(bank)
	{
		case BANK0: GS_Write_Byte(PAJ_REGITER_BANK_SEL,PAJ_BANK0);break;//BANK0�Ĵ�������
		case BANK1: GS_Write_Byte(PAJ_REGITER_BANK_SEL,PAJ_BANK1);break;//BANK1�Ĵ�������
	}
			
}

//PAJ7620U2����
u8 paj7620u2_wakeup(void)
{ 
	u8 data=0x0a;
	GS_WakeUp();//����PAJ7620U2
	delay_ms(5);//����ʱ��>400us
	GS_WakeUp();//����PAJ7620U2
	delay_ms(5);//����ʱ��>400us
	paj7620u2_selectBank(BANK0);//����BANK0�Ĵ�������
	data = GS_Read_Byte(0x00);//��ȡ״̬
	if(data!=0x20) return 0; //����ʧ��
	
	return 1;
}

//PAJ7620U2��ʼ��
//����ֵ��0:ʧ�� 1:�ɹ�
u8 paj7620u2_init(void)
{
	u8 i;
	u8 status;
	
	GS_i2c_init();//IIC��ʼ��
    status = paj7620u2_wakeup();//����PAJ7620U2
	if(!status) return 0;
	paj7620u2_selectBank(BANK0);//����BANK0�Ĵ�������
	for(i=0;i<INIT_SIZE;i++)
	{
		GS_Write_Byte(init_Array[i][0],init_Array[i][1]);//��ʼ��PAJ7620U2
	}
    paj7620u2_selectBank(BANK0);//�л���BANK0�Ĵ�������
	
	return 1;
}

//���˵�
void paj7620u2_test_ui(void)
{
	POINT_COLOR=BLUE;//��������Ϊ��ɫ
	LCD_Fill(30,170,300,300,WHITE);
	LCD_ShowString(30,170,200,16,16,"KEY1:   Gesture test");//����ʶ�����
	LCD_ShowString(30,190,200,16,16,"KEY0:   Ps test     ");//�ӽ��������
	
}

//����ʶ�����
void Gesture_test(void)
{   
	u8 i;
    u8 status;
	u8 data[2]={0x00};
	u16 gesture_data;
	paj7620u2_selectBank(BANK0);//����BANK0�Ĵ�������
	for(i=0;i<GESTURE_SIZE;i++)
	{
		GS_Write_Byte(gesture_arry[i][0],gesture_arry[i][1]);//����ʶ��ģʽ��ʼ��
	}
	paj7620u2_selectBank(BANK0);//�л���BANK0�Ĵ�������
	i=0;
	POINT_COLOR=BLUE;//��������Ϊ��ɫ
	
	
       		
        status = GS_Read_nByte(PAJ_GET_INT_FLAG1,2,&data[0]);//��ȡ����״̬			
		if(!status)
		{   
			gesture_data =(u16)data[1]<<8 | data[0];
			if(gesture_data) 
			{
				switch(gesture_data)
				{
					case GES_UP:               LCD_ShowString(110,140,200,16,24,"UP          ");
					                           printf("Up\r\n");                  break; //����
					case GES_DOWM:             LCD_ShowString(100,140,200,16,24,"Dowm        ");      
               						           printf("Dowm\r\n");                break; //����
					case GES_LEFT:             LCD_ShowString(100,140,200,16,24,"Left        ");           
  						                       printf("Left\r\n");                break; //����
					case GES_RIGHT:            LCD_ShowString(100,140,200,16,24,"Right       ");       
                						       printf("Right\r\n");               break; //����
					case GES_FORWARD:          LCD_ShowString(80,140,200,16,24,"Forward     ");        
						                       printf("Forward\r\n");             break; //��ǰ
					case GES_BACKWARD:         LCD_ShowString(80,140,200,16,24,"Backward    ");    
            						           printf("Backward\r\n");            break; //���
					case GES_CLOCKWISE:        LCD_ShowString(70,140,200,16,24,"Clockwise   ");     
                						       printf("Clockwise\r\n");     LED1=0;LED0=0; 
                                               LCD_ShowString(100,210,200,16,24,"ON         ");break; //˳ʱ��
					case GES_COUNT_CLOCKWISE:  LCD_ShowString(50,140,200,16,24,"AntiClockwise");  
                   						       printf("AntiClockwise\r\n"); LED1=1;LED0=1;
                                               LCD_ShowString(100,210,200,16,24,"OFF         ");break; //��ʱ��
					case GES_WAVE:             LCD_ShowString(100,140,200,16,24,"Wave         ");    
						                       printf("Wave\r\n");                break; //�Ӷ�
					default:break;
					
				}	
                			
			}
			
		}
		 
	
}

//       ����ʶ����                       //
//       UP>>���Ҳ�                         //
//       Clockwise>>���ǲ�                  //
//       AntiClockwise>>����                //
//       UP,Ƶ��+1KHz,�������Ҳ�            //
//       Down,Ƶ��-1KHz                     //
//       Left,��ֵ+0.65v(���Ϊ3.25v)       //
//       Right,��ֵ-0.65v                   //
void Gesture_test_sine(void)
{   
    static u32 freq=1000;
    static float Um=0.2;
    float a;
    u8 b=0;
	u8 i;
    u8 status;
	u8 data[2]={0x00};
	u16 gesture_data;
    POINT_COLOR=RED;
    LCD_DrawLine(0,48,240,48);
    POINT_COLOR=BLUE;
    LCD_DrawLine(0,50,240,50);
	paj7620u2_selectBank(BANK0);//����BANK0�Ĵ�������
	for(i=0;i<GESTURE_SIZE;i++)
	{
		GS_Write_Byte(gesture_arry[i][0],gesture_arry[i][1]);//����ʶ��ģʽ��ʼ��
	}
	paj7620u2_selectBank(BANK0);//�л���BANK0�Ĵ�������
	i=0;
	POINT_COLOR=BLUE;//��������Ϊ��ɫ
	
	
       		
        status = GS_Read_nByte(PAJ_GET_INT_FLAG1,2,&data[0]);//��ȡ����״̬			
		if(!status)
		{   
			gesture_data =(u16)data[1]<<8 | data[0];
			if(gesture_data) 
			{
				switch(gesture_data)
				{
					case GES_UP:               LCD_ShowString(0,20,240,16,24,"*********UP*********");
                                               printf("Up\r\n");
                                               freq+=1000;
                                               Sine_Wave_Init(freq,Um);
                                               POINT_COLOR=RED;
                                               LCD_ShowString(24,80,200,24,24,"   ASin(WX+&)+K:   ");break; //����,Ƶ��+1KHz,�������Ҳ�
                    
					case GES_DOWM:             LCD_ShowString(0,20,240,16,24,"********Dowm********");      
               						           printf("Dowm\r\n");
                                               freq-=1000;
                                               Sine_Wave_Init(freq,Um);                     break; //����,Ƶ��-1KHz
                    
					case GES_LEFT:             LCD_ShowString(0,20,240,16,24,"********Left********");           
  						                       printf("Left\r\n");Um+=0.2;
                                               Sine_Wave_Init(freq,Um);                    break; //����,��ֵ+0.65v(���Ϊ3.25v)
                    
					case GES_RIGHT:            LCD_ShowString(0,20,240,16,24,"********Right*******");       
                						       printf("Right\r\n");Um-=0.2;
                                               Sine_Wave_Init(freq,Um);                    break; //����,��ֵ-0.65v
                    
					case GES_FORWARD:          LCD_ShowString(0,20,240,16,24,"******Forward*******");        
						                       printf("Forward\r\n");                       break;//��ǰ
                                               
					case GES_BACKWARD:         LCD_ShowString(0,20,240,16,24,"******Backward******");    
            						           printf("Backward\r\n");                      break; //���
                                               
					case GES_CLOCKWISE:        LCD_ShowString(0,20,240,16,24,"******Clockwise*****");     
                						       printf("Clockwise\r\n");
                                               Triangular_Wave_Init(freq,Um);
                                               POINT_COLOR=RED;
                                               LCD_ShowString(6,80,240,24,24,"  Triangular_Wave:");break; //˳ʱ��,�������ǲ�
                                               
					case GES_COUNT_CLOCKWISE:  LCD_ShowString(0,20,240,16,24,"****AntiClockwise****");  
                   						       printf("AntiClockwise\r\n");
                                               Square_Wave_Init(freq,Um);
                                               POINT_COLOR=RED;//��������Ϊ��ɫ 
                                               LCD_ShowString(2,80,240,24,24,"     Square_Wave:   ");break; //��ʱ�룬��������	

					case GES_WAVE:             LCD_ShowString(0,20,200,16,24,"********Wave********");    
						                       printf("Wave\r\n");                                   break; //�Ӷ�
                    
					default:break;					
				}	               			
			}			
		}
    POINT_COLOR=RED;//��������Ϊ��ɫ 						      
	LCD_ShowString(60,130,200,24,24,"F:");
    LCD_ShowString(160,130,200,24,24,"HZ");    
	LCD_ShowString(60,160,200,24,24,"A:");
    LCD_ShowString(160,160,200,24,24,"V");
    LCD_ShowString(112,160,200,24,24,".");
    LCD_ShowString(60,200,200,16,16,"UP  :F+  Down  :F-");
    LCD_ShowString(60,220,200,16,16,"Left:A+  Ringht:A-");
    POINT_COLOR=BLUE;
    LCD_ShowxNum(100,130,freq,5,24,0X80);
    a=(Um*3.25);                           //�õ���ѹֵ   		               
    b=a;
    LCD_ShowxNum(100,160,a,1,24,0);    //��ʾ��ѹֵ��������
    a-=b;
    a*=1000;
    LCD_ShowxNum(124,160,a,3,24,0X80); 	//��ʾ��ѹֵ��С������
}


//�ӽ�������
void Ps_test(void)
{
    u8 i;
	u8 key;
	u8 data[2]={0x00};
	u8 obj_brightness=0;
	u16 obj_size=0;
	
	paj7620u2_selectBank(BANK0);//����BANK0�Ĵ�������
	for(i=0;i<PROXIM_SIZE;i++)
	{
		GS_Write_Byte(proximity_arry[i][0],proximity_arry[i][1]);//�ӽ����ģʽ��ʼ��
	}
	paj7620u2_selectBank(BANK0);//����BANK0�Ĵ�������
	i=0;
	POINT_COLOR=BLUE;//��������Ϊ��ɫ
	LCD_Fill(30,170,300,300,WHITE);
	LCD_ShowString(30,180,200,16,16,"KEY_UP: Exit the test");
	LCD_ShowString(30,210,200,16,16,"Ps test");
	LCD_ShowString(30,240,200,16,16,"Brightness");
	LCD_ShowString(160,240,200,16,16,"Size");
	POINT_COLOR=RED;//��������Ϊ��ɫ	
	
	while(1)
	{	
		key = KEY_Scan(0);
		if(key==WKUP_PRES) break;
		
		obj_brightness = GS_Read_Byte(PAJ_GET_OBJECT_BRIGHTNESS);//��ȡ��������
		data[0] = GS_Read_Byte(PAJ_GET_OBJECT_SIZE_1);//��ȡ�����С
		data[1] = GS_Read_Byte(PAJ_GET_OBJECT_SIZE_2);
		obj_size = ((u16)data[1] & 0x0f)<<8 | data[0];
		LCD_ShowxNum(50,270,obj_brightness,3,24,0);
		LCD_ShowxNum(152,270,obj_size,3,24,0);
		printf("obj_brightness: %d\r\n",obj_brightness);
        printf("obj_size: %d\r\n",obj_size);
		
		delay_ms(100);
		i++;
		if(i==5)
		{
		    LED0=!LED0;//��ʾϵͳ��������	
			i=0;
		}
	}
	
}
//PAJ7620U2����������
void paj7620u2_sensor_test(void)
{   
	 u8 i=0;
	 u8 key;
	
     paj7620u2_test_ui();//���˵���ʾ
	 while(1)
	 {
		 key = KEY_Scan(0);//����ɨ��
		 if(key)
		 {
			 switch(key)
			 {
				 case KEY1_PRES:  Gesture_test();   break;//���Ƽ��ģʽ
				 case KEY0_PRES:  Ps_test();        break;//�ӽ����ģʽ  
			 }
			 paj7620u2_test_ui();
		 }
		delay_ms(50);
		i++;
		if(i==5)
		{
		    LED0=!LED0;//��ʾϵͳ��������	
			i=0;
		}
		 
	 }
}
