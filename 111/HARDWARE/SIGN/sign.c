#include "sign.h"
u16 D_Sine[256]; 
u16 D_Triangular[256];
u16 D_Square[256];

/********���Ҳ������***********/
//cycle	:���α��λ��	(0~256)
void Sine_Wave_Data(u16 cycle ,u16 *D_Sine,float Um)
{  
    u16 i;
    for( i=0;i<cycle;i++)
    D_Sine[i]=(u16)(Um*(sin(i*2*3.1415926/cycle)+1)*4095/2);
}

/********���ǲ������***********/
void Triangular_Wave_Data( u16 cycle ,u16 *D_Triangular,float Um)
{
    u16 i;
    for( i=0;i<cycle/2;i++)
	{
		D_Triangular[i]= (u16)(Um*4095*2*i/cycle);
	}
	for( i=cycle/2;i<cycle;i++)
	{
		D_Triangular[i]= (u16)(Um*2*4095*(cycle-i)/cycle);
	}
        
}

/********���������***********/
void Square_Wave_Data(u16 cycle ,u16 *D_Square,float Um)
{
	u16 i;
	for(i=0;i<cycle/2;i++)
	{
		D_Square[i]=(u16)(0);
	}
	for( i=cycle/2;i<cycle;i++)
	{
		D_Square[i]=(u16)(Um*4095);
	}
}


/****************��ʼ������******************/
void Wave_GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    //RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //��ʱ��
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;       //�������ģʽ
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   //������� 
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_4 ; //ѡ������
    GPIO_SetBits(GPIOA,GPIO_Pin_4)  ;   //�������
    GPIO_Init(GPIOA, &GPIO_InitStructure);      //��ʼ��
}

/******************DAC��ʼ����*************************/
void Wave_DAC_Config( void)
{
    DAC_InitTypeDef            DAC_InitStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);//��DACʱ��
     
  /**************DAC�ṹ��ʼ��*******************/
    DAC_StructInit(&DAC_InitStructure);    
    DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;//����������
    DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Disable; //��ʹ���������
    DAC_InitStructure.DAC_Trigger = DAC_Trigger_T2_TRGO;//DAC����Ϊ��ʱ��2����
    DAC_Init(DAC_Channel_1, &DAC_InitStructure);//��ʼ��
    DAC_Cmd(DAC_Channel_1, ENABLE);    //ʹ��DAC��ͨ��1
    DAC_DMACmd(DAC_Channel_1, ENABLE); //ʹ��DACͨ��1��DMA  
}

/*********��ʱ����ʼ��************/
void Wave_TIM_Config(u32 f1)
{
    TIM_TimeBaseInitTypeDef    TIM_TimeBaseStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);//��ʱ��
    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.TIM_Prescaler = 0x0;     //��Ԥ��Ƶ
    TIM_TimeBaseStructure.TIM_ClockDivision = 0x0; //����Ƶ<br>����TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//���ϼ���
    TIM_TimeBaseStructure.TIM_Period = f1;//�������Ƶ��
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
    TIM_SelectOutputTrigger(TIM2, TIM_TRGOSource_Update);//����TIME�������Ϊ����ģʽ
}

/*********Sine DMA����***********/
void Sine_Wave_DMA_Config(void)
{                  
    DMA_InitTypeDef            DMA_InitStructure;
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2, ENABLE);//����DMA2ʱ��
     
    DMA_StructInit( &DMA_InitStructure);        //DMA�ṹ���ʼ��
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;//�ӼĴ���������
    DMA_InitStructure.DMA_BufferSize = 256;//�Ĵ�����С
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//�����ַ������
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; //�ڴ��ַ����
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;//���Ϊ����
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;//���Ϊ����
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;//���ȼ��ǳ���
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;//�ر��ڴ浽�ڴ�ģʽ
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;//ѭ������ģʽ
	
    DMA_InitStructure.DMA_PeripheralBaseAddr = DAC_DHR12R1;//�����ַΪDACͨ��1�ĵ�ַ
    DMA_InitStructure.DMA_MemoryBaseAddr =(uint32_t)D_Sine;//�������ݱ��ڴ��ַ
    DMA_Init(DMA2_Channel3, &DMA_InitStructure);//��ʼ��
    DMA_Cmd(DMA2_Channel3, ENABLE); //ʹ��DMAͨ��3  ����  
		
}

/*********Triangular DMA����***********/
void Triangular_Wave_DMA_Config(void)
{                  
    DMA_InitTypeDef            DMA_InitStructure;
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2, ENABLE);//����DMA2ʱ��
     
    DMA_StructInit( &DMA_InitStructure);        //DMA�ṹ���ʼ��
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;//�ӼĴ���������
    DMA_InitStructure.DMA_BufferSize = 256;//�Ĵ�����С
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//�����ַ������
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; //�ڴ��ַ����
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;//���Ϊ����
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;//���Ϊ����
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;//���ȼ��ǳ���
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;//�ر��ڴ浽�ڴ�ģʽ
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;//ѭ������ģʽ
	
    DMA_InitStructure.DMA_PeripheralBaseAddr = DAC_DHR12R1;//�����ַΪDACͨ��1�ĵ�ַ
    DMA_InitStructure.DMA_MemoryBaseAddr =(uint32_t)D_Triangular;//�������ݱ��ڴ��ַ
    DMA_Init(DMA2_Channel3, &DMA_InitStructure);//��ʼ��
    DMA_Cmd(DMA2_Channel3, ENABLE); //ʹ��DMAͨ��3  ����  
		
}

/*********Square DMA����***********/
void Square_Wave_DMA_Config(void)
{                  
    DMA_InitTypeDef            DMA_InitStructure;
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2, ENABLE);//����DMA2ʱ��
     
    DMA_StructInit( &DMA_InitStructure);        //DMA�ṹ���ʼ��
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;//�ӼĴ���������
    DMA_InitStructure.DMA_BufferSize =256;//�Ĵ�����С
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//�����ַ������
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; //�ڴ��ַ����
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;//���Ϊ����
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;//���Ϊ����
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;//���ȼ��ǳ���
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;//�ر��ڴ浽�ڴ�ģʽ
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;//ѭ������ģʽ
	
    DMA_InitStructure.DMA_PeripheralBaseAddr = DAC_DHR12R1;//�����ַΪDACͨ��1�ĵ�ַ
    DMA_InitStructure.DMA_MemoryBaseAddr =(uint32_t)D_Square;//�������ݱ��ڴ��ַ
    DMA_Init(DMA2_Channel3, &DMA_InitStructure);//��ʼ��
    DMA_Cmd(DMA2_Channel3, ENABLE); //ʹ��DMAͨ��3  ����  
		
}

/**********���Ҳ���ʼ��**********************/
//Freq:	Ƶ��ֵ��0~17 000)Hz
//Um			 :	��ѹ��ֵ��0.0~1.5��V
/*******************************************/

void Sine_Wave_Init(u16 Freq,float Um)
{
	u32 f1;
	f1=(u32)(72000000/sizeof(D_Sine)*2/Freq);//����Ƶ��
	Sine_Wave_Data(256,D_Sine,Um);     //����������Ҳ��Ĳ��α�
	Wave_GPIO_Config();             //��ʼ��io
	Wave_TIM_Config(f1);            //��ʼ����ʱ��
	Wave_DAC_Config();              //����DAC
	Sine_Wave_DMA_Config();              //����DMA
	TIM_Cmd(TIM2, ENABLE);             //������ʱ��
}

/**********���ǲ���ʼ��**********************/
void Triangular_Wave_Init(u16 Freq,float Um)
{
	u32 f1;
	f1=(u32)(72000000/sizeof(D_Triangular)*2/Freq);//����Ƶ��
	Triangular_Wave_Data(256,D_Triangular,Um);     //����������Ҳ��Ĳ��α�
	Wave_GPIO_Config();             //��ʼ��io
	Wave_TIM_Config(f1);            //��ʼ����ʱ��
	Wave_DAC_Config();              //����DAC
	Triangular_Wave_DMA_Config();              //����DMA
	TIM_Cmd(TIM2, ENABLE);             //������ʱ��
}

/**********������ʼ��**********************/
void Square_Wave_Init(u16 freq,float Um)
{
	u32 f1;
	f1=(u32)(72000000/sizeof(D_Square)*2/freq);//����Ƶ��
	Square_Wave_Data(256,D_Square,Um);     //����������Ҳ��Ĳ��α�
	Wave_GPIO_Config();             //��ʼ��io
	Wave_TIM_Config(f1);            //��ʼ����ʱ��
	Wave_DAC_Config();              //����DAC
	Square_Wave_DMA_Config();          //����DMA
	TIM_Cmd(TIM2, ENABLE);             //������ʱ��
}

