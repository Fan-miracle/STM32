//#include "stm32f10x_conf.h"					//������Ҫ�Ŀ�
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "Time.h"
#include "oled.h"

#include "iic.h"
#include "BH1750.h"

extern u32 Sec;
extern u32 Sec_buf;

int main(void)
{	
	float light_data = 0;
		
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	//���ڳ�ʼ��Ϊ115200
	delay_init();		//��ʱ��ʼ�� 
	TIM2_Int_Init(999,71,2,0);				                //��ʱ1ms			������⣬����
	TIM3_Int_Init(999,719,2,1);				                //��ʱ10ms			�����¼�ִ��
	OLED_Init();			//��ʼ��OLED  
	OLED_Clear(); 			//OLED����
	
	
	OLED_ShowString(0,0,"light:",12); 
	OLED_Refresh_Gram();
	bh1750_init();
	delay_ms(750);
 	while(1)
	{
		if(Sec > 200)
		{
			Sec = 0;
			light_data = bh1750_get_data(); //��ȡ��������
			OLED_ShowNum(35,0,light_data,4,12);		//��ʾ��������	    
			OLED_Refresh_Gram();
		}
	
	} 	
}

