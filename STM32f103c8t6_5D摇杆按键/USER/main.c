//#include "stm32f10x_conf.h"					//�ڴ˴�������Ҫ�Ĺٷ���
#include "delay.h"
#include "sys.h"
#include "usart.h"	

#include "led.h"
#include "key.h"
#include "Time.h"
#include "oled.h"

extern u32 Sec;								//��ʱ��2
extern u32 Sec_buf;						//��ʱ��3


int UP=0;//�Ϸ��򰴼�
int DWN = 0;//�·��򰴼�
int LFT =0;//|���򰴼�
int RHT =0;//|�ҷ��򰴼�
int MID =0;//|�м䰴��
int SET_A =0; //|���ð���
int RST_B =0;//|��λ����

int main(void)
{	
	u8 key;   			//�������
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	//���ڳ�ʼ��Ϊ115200
	delay_init();				//��ʱ��ʼ�� 
	TIM2_Int_Init(999,71,2,0);				                //��ʱ1ms			������⣬����
	TIM3_Int_Init(999,719,2,1);				                //��ʱ10ms			�����¼�ִ��
	
	OLED_Init();				//��ʼ��OLED  
	OLED_Clear(); 			//OLED����
	Key_Init();					//������ʼ��
	LED_Init();					//LED��ʼ��
	
	OLED_ShowString(0,0,"SET_A:",12);
	OLED_ShowString(64,0,"RST_B:",12);
	OLED_ShowString(0,15,"UP:",12);
	OLED_ShowString(64,15,"DWN:",12);
	OLED_ShowString(0,30,"LFT:",12);
	OLED_ShowString(64,30,"RHT:",12);
	OLED_ShowString(0,45,"MID:",12);
	OLED_ShowString(64,45,"LED:",12);
	OLED_Refresh_Gram();
 	while(1)
	{
		key=KEY_Scan(0); 
		if(key)
		{
			switch(key)
			{
				case KEY_UP_PRES:  UP = UP+1;  	 break;
				case KEY_DWN_PRES: DWN = DWN+1;  break;
				case KEY_LFT_PRES: LFT = LFT+1;  break;
				case KEY_RHT_PRES: RHT = RHT+1;  break;
				case KEY_MID_PRES: MID = MID+1;  break;
				case KEY_SET_PRES: SET_A = SET_A+1;  break;
				case KEY_RST_PRES: RST_B = RST_B+1;  break;
				default: break;
			}
		}
		if(Sec > 1000)
		{
			Sec = 0;
			LED0=!LED0;
		}
		OLED_ShowNum(32,0,SET_A,2,12);		  //��ʾ��������	 
		OLED_ShowNum(96,0,RST_B,2,12);		//��ʾ��������	 
		OLED_ShowNum(32,15,UP,2,12);		//��ʾ��������	 
    OLED_ShowNum(96,15,DWN,2,12);		//��ʾ��������	
		OLED_ShowNum(32,30,LFT,2,12);		//��ʾ��������			
		OLED_ShowNum(96,30,RHT,2,12);	//��ʾ��������	
		OLED_ShowNum(32,45,MID,2,12);	//��ʾ��������	
		OLED_ShowNum(96,45,LED0,2,12);	//��ʾ��������	
		OLED_Refresh_Gram();
	} 	
}

