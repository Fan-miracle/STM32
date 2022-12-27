//#include "stm32f10x_conf.h"					//�ڴ˴�������Ҫ�Ĺٷ���
#include "delay.h"
#include "sys.h"
#include "usart.h"	
#include "Time.h"
#include "oled.h"

#include "PWM.h"


extern u32 Sec;
extern u32 Sec_buf;


//LD-2701����ת�Ƕ�Ϊ270�ȣ���1750~1950��Ӧ0~270�ȣ�
int main(void)
{	
	int i = 50;_Bool dir_flag = 1;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	//���ڳ�ʼ��Ϊ115200
	delay_init();		//��ʱ��ʼ�� 
	TIM2_Int_Init(999,71,2,0);				                //��ʱ1ms			������⣬����
	TIM3_Int_Init(999,719,2,1);				                //��ʱ10ms			�����¼�ִ��
	OLED_Init();			//��ʼ��OLED  
	OLED_Clear(); 			//OLED����
	TIM4_PWM_Init(1999,719);   //PWMƵ��=72000000/��719+1��/��1999+1��=50hz=20ms
	
	OLED_ShowString(0,0,"Servo Angle:",12); 
	OLED_Refresh_Gram();
	
 	while(1)
	{
		if(Sec > 200)
		{
			Sec = 0;
			if(dir_flag)
			{
				i=i+1;
			}
			else
			{
				i=i-1;
			}
			TIM_SetCompare1(TIM4,2000-i);			//PB6;  1750=2.5ms=90��			1800=2ms=45��;			1850=1.5s=0��;		1900=1ms=-45��;			1950=0.5ms=-90��
			TIM_SetCompare2(TIM4,2000-i);			//PB7;
			OLED_ShowNum(40,0,i,8,12);		//��ʾ��������	  
			OLED_ShowNum(40,20,dir_flag,8,12);		//��ʾ��������	  			
			OLED_Refresh_Gram();
			if(i>=250)
			{
				dir_flag=0;
			}
			else if(i<=50)
			{
				dir_flag=1;
			}				
			
		}
	} 	
}

