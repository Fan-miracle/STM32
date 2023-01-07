//#include "stm32f10x_conf.h"					//�ڴ˴�������Ҫ�Ĺٷ���
#include "delay.h"
#include "sys.h"
#include "usart.h"	
#include "Time.h"
#include "oled.h"

#include "Emm42_board.h"
#include "Emm42_delay.h"
#include "Emm42_usart.h"
#include "Emm42_me.h"


float MotorAngle;					//���λ��
float AngleError;					//λ�����
int32 Pulse_num;					//������


int main(void)
{	

		
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	//���ڳ�ʼ��Ϊ115200
	delay_init();		//��ʱ��ʼ�� 
	TIM2_Int_Init(999,71,2,0);				                //��ʱ1ms			������⣬����
	TIM3_Int_Init(999,719,2,1);				                //��ʱ10ms			�����¼�ִ��
	OLED_Init();			//��ʼ��OLED  
	OLED_Clear(); 			//OLED����
	
	Emm42_board_init(); 															//��ʼ����������
	Emm42_delay_ms(1200);															//��ʱ1.2��ȴ�Emm�ջ��������ϵ��ʼ�����
	OLED_ShowString(20,0,"MPU6050 OK",12); 
	OLED_Refresh_Gram();
	
 	while(1)
	{
		Motor_speed_pos();
//Motor_speed();
//		Emm42_delay_ms(8000);
//		Motor_Enabled();
	  MotorAngle = Emm42_MotorAngle();					//���λ��
		AngleError = Emm42_MotorError();					//λ�����
		Pulse_num = Emm42_Pulse_count();					//������
		OLED_ShowNum(40+8,14,MotorAngle,8,12);		//��ʾ��������	  
		OLED_ShowNum(40+8,27,AngleError,8,12);		//��ʾ��������	 
		OLED_ShowNum(40+8,39,Pulse_num,8,12);		//��ʾ��������	    
		OLED_Refresh_Gram();
//	
	
	} 	
}

