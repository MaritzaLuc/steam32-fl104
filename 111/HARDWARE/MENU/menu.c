//#include "stm32f10x.h"
//#include "paj7620u2.h"
//#include "menu.h"
//#include "lcd.h"
//#include "key.h"
//#include "sign.h"
//extern const unsigned char gImage_HGTB[];//������:����ͼ��
//extern const unsigned char gImage_HGZB[];//������:�����ֱ�
//extern const unsigned char gImage_BXFSQ[];//������:���η�����
//extern const unsigned char gImage_ZDH[];//�Զ���1901����
//extern const unsigned char gImage_1_1[];//һ���˵���1.����ʶ����
//extern const unsigned char gImage_1_2[];//һ���˵���2.������������
//extern const unsigned char gImage_1_3[];//һ���˵���3.���Ʋ�������
//extern const unsigned char gImage_1_4[];//�����˵�������ʶ����:LED:
//extern const unsigned char gImage_1_5[];//�����˵���1.���Ҳ�
//extern const unsigned char gImage_1_6[];//�����˵���2.���ǲ�
//extern const unsigned char gImage_1_7[];//�����˵���3.����
//float Um=0.2;
//float a;
//u32 freq=1000;
//u8 menu=0;
//u8 in=1;
//u8 b=0;
//u8 t=0;
//u8 x=0;
//u8 key;


////���˵�����
//void startmenu(void)
//{
//     POINT_COLOR=BLUE;
//     LCD_Draw_Picture(80,24,160,104,(u8*)gImage_HGTB);//������:����ͼ��
//     POINT_COLOR=BLACK;
//     LCD_Draw_Picture(0,105,240,170,(u8*)gImage_HGZB);//������:�����ֱ�
//     POINT_COLOR=RED;
//     LCD_DrawLine(0,173,240,173);
//     POINT_COLOR=RED;
//     LCD_DrawLine(0,176,240,176);
//     POINT_COLOR=RED;
//     LCD_DrawLine(0,259,240,259);
//     POINT_COLOR=RED;
//     LCD_DrawLine(0,256,240,256);
//     POINT_COLOR=RED;
//     LCD_Draw_Picture(40,200,200,230,(u8*)gImage_BXFSQ);//���η�����
//     POINT_COLOR=BLUE;
//     LCD_Draw_Picture(54,270,186,290,(u8*)gImage_ZDH);//�Զ���1901����
//}

////һ���˵���1.����ʶ����
//void Submenu1_1(void)
//{   
//    POINT_COLOR=BLACK;
//    LCD_Draw_Picture(0,0,240,65,(u8 *)gImage_HGZB);
//    POINT_COLOR=RED;
//    LCD_DrawLine(0,68,240,68);
//    LCD_Draw_Picture(15,100,220,236,(u8 *)gImage_1_1);
//    POINT_COLOR=BLUE;
//    LCD_ShowString(84,300,48,16,16,"ZDH");
//    LCD_ShowxNum(108,300,1901,4,16,0);
//    LCD_ShowString(140,300,48,16,16,"LP");
//}

////һ���˵���2.������������
//void Submenu1_2(void)
//{ 
//     POINT_COLOR=BLACK;
//     LCD_Draw_Picture(0,0,240,65,(u8 *)gImage_HGZB);//�����ֱ�
//     POINT_COLOR=RED;
//     LCD_DrawLine(0,68,240,68);
//     LCD_Draw_Picture(15,100,220,236,(u8 *)gImage_1_2);
//     POINT_COLOR=BLUE;
//     LCD_ShowString(84,300,48,16,16,"ZDH");
//     LCD_ShowxNum(108,300,1901,4,16,0);
//     LCD_ShowString(140,300,48,16,16,"LP");
//}

////һ���˵���3.���Ʋ�������
//void Submenu1_3(void)
//{    
//     POINT_COLOR=BLACK;
//     LCD_Draw_Picture(0,0,240,65,(u8 *)gImage_HGZB);//�����ֱ�
//     POINT_COLOR=RED;
//     LCD_DrawLine(0,68,240,68);
//     LCD_Draw_Picture(15,100,220,236,(u8 *)gImage_1_3);
//     POINT_COLOR=BLUE;
//     LCD_ShowString(84,300,48,16,16,"ZDH");
//     LCD_ShowxNum(108,300,1901,4,16,0);
//     LCD_ShowString(140,300,48,16,16,"LP");
//}

////�����˵�������ʶ����:
////          LED:
//void Submenu1_4(void)
//{   
//    Gesture_test();
//    POINT_COLOR=RED;
//    LCD_Draw_Picture(0,0,240,320,(u8 *)gImage_1_4);
//    POINT_COLOR=BLUE;
//    LCD_ShowString(84,300,48,16,16,"ZDH");
//    LCD_ShowxNum(108,300,1901,4,16,0);
//    LCD_ShowString(140,300,48,16,16,"LP");
//    key=KEY_Scan(0);
//    if(key==WKUP_PRES)
//    {LCD_Clear(WHITE);
//        menu=1;
//    }
//    
//}

////�����˵���1.���Ҳ�
//void Submenu1_5(void)
//{ 
//    POINT_COLOR=RED;
//    LCD_Draw_Picture(0,0,240,320,(u8 *)gImage_1_5);
//    POINT_COLOR=BLUE;
//    LCD_ShowString(84,300,48,16,16,"ZDH");
//    LCD_ShowxNum(108,300,1901,4,16,0);
//    LCD_ShowString(140,300,48,16,16,"LP");
//}

////�����˵���2.���ǲ�
//void Submenu1_6(void)
//{ 
//    POINT_COLOR=RED;
//    LCD_Draw_Picture(0,0,240,320,(u8 *)gImage_1_6);
//    POINT_COLOR=BLUE;
//    LCD_ShowString(84,300,48,16,16,"ZDH");
//    LCD_ShowxNum(108,300,1901,4,16,0);
//    LCD_ShowString(140,300,48,16,16,"LP");
//}

////�����˵���3.����
//void Submenu1_7(void)    
//{ 
//    POINT_COLOR=RED;
//    LCD_Draw_Picture(0,0,240,320,(u8 *)gImage_1_7);
//    POINT_COLOR=BLUE;
//    LCD_ShowString(84,300,48,16,16,"ZDH");
//    LCD_ShowxNum(108,300,1901,4,16,0);
//    LCD_ShowString(140,300,48,16,16,"LP");
//}


////�����˵������Ҳ�Ƶ�ʷ�ֵ����
//void Submenu1_9(void)
//{  
//  while(in)
//  {
//    Sine_Wave_Init(freq,Um);//���ҳ�ʼ��
//    POINT_COLOR=RED;//��������Ϊ��ɫ 
//    LCD_ShowString(60,80,200,24,24,"ASin(WX+&)+K:");						      
//	LCD_ShowString(60,130,200,24,24,"F:");
//    LCD_ShowString(160,130,200,24,24,"HZ");    
//	LCD_ShowString(60,160,200,24,24,"A:");
//    LCD_ShowString(160,160,200,24,24,"V");
//    LCD_ShowString(112,160,200,24,24,".");
//    LCD_ShowString(60,200,200,16,16,"KEY1:+  KEY0:-");
//   
//    key=KEY_Scan(0);
//    if(key==WKUP_PRES)x++;
//        switch(x) 
//        {            
//            case 0:LCD_ShowString(45,130,200,24,24,"*");
//                   if(key==KEY1_PRES)freq+=1000;
//                   if(key==KEY0_PRES)freq-=1000;break;
//               			  
//            case 1:LCD_ShowString(45,130,200,24,24," ");
//                   LCD_ShowString(45,160,200,24,24,"*");
//                   if(key==KEY1_PRES)Um+=0.2;
//                   if(key==KEY0_PRES)Um-=0.2;break;
//           
//            case 2:menu=5;x=0;in=0;break;
//            default:break;
//        }
//            POINT_COLOR=BLUE;
//            LCD_ShowxNum(100,130,freq,5,24,0X80);
//            a=(Um*3.25);			           //�õ���ѹֵ
//			b=a;
// 			LCD_ShowxNum(100,160,a,1,24,0);    //��ʾ��ѹֵ��������
// 			a-=b;
//			a*=1000;
//			LCD_ShowxNum(124,160,a,3,24,0X80); 	//��ʾ��ѹֵ��С������
//	    
//    }
//   
//     
//}
//void Submenu1_10(void)
//{   
//    while(in)
//  {
//    Triangular_Wave_Init(freq,Um);//���ǲ���ʼ��
//    POINT_COLOR=RED;//��������Ϊ��ɫ 
//    LCD_ShowString(30,80,200,24,24,"Triangular_Wave:");						      
//	LCD_ShowString(60,130,200,24,24,"F:");
//    LCD_ShowString(160,130,200,24,24,"HZ");    
//	LCD_ShowString(60,160,200,24,24,"A:");
//    LCD_ShowString(160,160,200,24,24,"V");
//    LCD_ShowString(112,160,200,24,24,".");
//    LCD_ShowString(60,200,200,16,16,"KEY1:+  KEY0:-");
//   
//    key=KEY_Scan(0);
//    if(key==WKUP_PRES)x++;
//        switch(x) 
//        {            
//            case 0:LCD_ShowString(45,130,200,24,24,"*");
//                   if(key==KEY1_PRES)freq+=1000;
//                   if(key==KEY0_PRES)freq-=1000;break;
//               			  
//            case 1:LCD_ShowString(45,130,200,24,24," ");
//                   LCD_ShowString(45,160,200,24,24,"*");
//                   if(key==KEY1_PRES)Um+=0.2;
//                   if(key==KEY0_PRES)Um-=0.2;break;
//            
//            case 2:menu=6;x=0;in=0;break;
//            default:break;
//        }
//            POINT_COLOR=BLUE;
//            LCD_ShowxNum(100,130,freq,5,24,0X80);
//            a=(Um*3.25);			           //�õ���ѹֵ
//			b=a;
// 			LCD_ShowxNum(100,160,a,1,24,0);    //��ʾ��ѹֵ��������
// 			a-=b;
//			a*=1000;
//			LCD_ShowxNum(124,160,a,3,24,0X80); 	//��ʾ��ѹֵ��С������	    
//    }
//}


//void Submenu1_11(void)
//{   
//    while(in)
//  {
//    Square_Wave_Init(freq,Um);//������ʼ��
//    POINT_COLOR=RED;//��������Ϊ��ɫ 
//    LCD_ShowString(50,80,200,24,24,"Square_Wave:");						      
//	LCD_ShowString(60,130,200,24,24,"F:");
//    LCD_ShowString(160,130,200,24,24,"HZ");    
//	LCD_ShowString(60,160,200,24,24,"A:");
//    LCD_ShowString(160,160,200,24,24,"V");
//    LCD_ShowString(112,160,200,24,24,".");
//    LCD_ShowString(60,200,200,16,16,"KEY1:+  KEY0:-");
//   
//    key=KEY_Scan(0);
//    if(key==WKUP_PRES)x++;
//        switch(x) 
//        {            
//            case 0:LCD_ShowString(45,130,200,24,24,"*");
//                   if(key==KEY1_PRES)freq+=1000;
//                   if(key==KEY0_PRES)freq-=1000;break;
//               			  
//            case 1:LCD_ShowString(45,130,200,24,24," ");
//                   LCD_ShowString(45,160,200,24,24,"*");
//                   if(key==KEY1_PRES)Um+=0.2;
//                   if(key==KEY0_PRES)Um-=0.2;break;
//            
//            case 2:menu=7;x=0;in=0;break;
//            default:break;
//        }
//            POINT_COLOR=BLUE;
//            LCD_ShowxNum(100,130,freq,5,24,0X80);
//            a=(Um*3.25);			 //�õ���ѹֵ
//			b=a;
// 			LCD_ShowxNum(100,160,a,1,24,0);    //��ʾ��ѹֵ��������
// 			a-=b;
//			a*=1000;
//			LCD_ShowxNum(124,160,a,3,24,0X80); 	//��ʾ��ѹֵ��С������	    
//    }
//}

//void Submenu1_12(void)
//{  
//    Gesture_test_sine();
//    
//    key=KEY_Scan(0);
//   
//    if(key==WKUP_PRES)
//    {
//      LCD_Clear(WHITE);
//      menu=3;
//    }       
//}

////����������������ɨ��õ���ֵʹmenuֵ�ı�
//void KeyService(void)
//{        
//    switch(KEY_Scan(0))
//  {
//        case KEY0_PRES: 
//                         LCD_Clear(WHITE);menu++;
//                         if(menu==4)menu=1;
//                         if(menu==5)menu++;
//                         if(menu==8)menu=5;
//                         break;
//        case KEY1_PRES:
//                         LCD_Clear(WHITE);
//                         if(menu==1)menu=4;
//                         if(menu==5)menu=9;in=1;
//                         if(menu==6)menu=10;
//                         if(menu==7)menu=11;        
//                         if(menu==2)menu=5;
//                         if(menu==3)menu=12;
//                         break;
//                 
//        case WKUP_PRES:
//                         LCD_Clear(WHITE);
//                         if(menu<4)menu=0;
//                         if(menu==4)menu=1;
//                         if(menu==5)menu=2;
//                         if(menu==6||menu==7)menu=3;break;				
//                         default:break;
//  }
//}


////LCD��ʾ��������ֵmenuֵ��1����7����ʾ��Ӧ����
//void LCDShow(void)
//{   
//    switch(menu)
//  {
//        case 0:startmenu();break;
//        case 1:Submenu1_1();break;
//        case 2:Submenu1_2();break;
//        case 3:Submenu1_3();break;
//        case 4:Submenu1_4();break;
//        case 5:Submenu1_5();break;
//        case 6:Submenu1_6();break;
//        case 7:Submenu1_7();break;
//        case 9:Submenu1_9();break;
//        case 10:Submenu1_10();break;
//        case 11:Submenu1_11();break;
//        case 12:Submenu1_12();break;
//        default:break;
//  }
//}
