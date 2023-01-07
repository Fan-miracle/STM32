#include "key.h"


extern u32 Sec_buf;						//��ʱ��3


void Key_Init(void)
{
	GPIO_InitTypeDef GPIO_Str;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//ʹ��PORTA,PORTEʱ��
	GPIO_Str.GPIO_Mode = GPIO_Mode_IPU;//���ó���������
	GPIO_Str.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_Str.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_Str);
	
//	GPIO_Str.GPIO_Mode = GPIO_Mode_IPU;//���ó���������
//	GPIO_Str.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
//	GPIO_Init(GPIOB,&GPIO_Str);
}

//GPIO_Mode_IPD�� ��һ�˽�3.3V			
//GPIO_Mode_IPU�� ��һ�˽�GND


//����������
//���ذ���ֵ
//mode:0,��֧��������;1,֧��������;
//ע��˺�������Ӧ���ȼ�,				KEY_SET>KEY_RST>KEY_UP
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//�������ɿ���־
	if(mode)key_up=1;  //֧������	
	if(key_up == 0 && Sec_buf>100)
	{
		key_up=1;							//��������һ���δ��������֧������
	}
	if(key_up&&(KEY_UP==0||KEY_DWN==0||KEY_LFT==0||KEY_RHT==0||KEY_SET==0||KEY_RST==0))		//��������
	{
		delay_ms(20);//ȥ���� 
		key_up=0;
		TIM_Cmd(TIM3, ENABLE);  //ʹ��TIMx								
		if(KEY_SET==0)					return KEY_SET_PRES;								//���ð���
		else if(KEY_RST==0)			return KEY_RST_PRES;
		else if(KEY_UP==0)			return KEY_UP_PRES;									//����
		else if(KEY_DWN==0)			return KEY_DWN_PRES;								//����
		else if(KEY_LFT==0)			return KEY_LFT_PRES;	
		else if(KEY_RHT==0)			return KEY_RHT_PRES;		
//		else if(KEY_MID==0)			return KEY_MID_PRES;	
	}
	else if(KEY_UP==1&&KEY_DWN==1&&KEY_LFT==1&&KEY_RHT==1&&KEY_SET==1&&KEY_RST==1)				//��������
	{
		TIM_Cmd(TIM3, DISABLE);  //ʹ��TIMx	
		Sec_buf = 0;
		key_up=1; 	    
	}
 	return 0;// �ް�������
}














