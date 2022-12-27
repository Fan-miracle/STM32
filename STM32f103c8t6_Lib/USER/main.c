#include "delay.h"
#include "sys.h"
#include "usart.h"	
#include "oled.h"




int main(void)
{	

		
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	//���ڳ�ʼ��Ϊ115200
	delay_init();		//��ʱ��ʼ�� 
	OLED_Init();			//��ʼ��OLED  
	OLED_Clear(); 			//OLED����
	
	
	OLED_ShowString(20,0,"MPU6050 OK",12); 
	OLED_Refresh_Gram();
	
 	while(1)
	{

	
	} 	
}

