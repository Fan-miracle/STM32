//#include "stm32f10x_conf.h"					//�ڴ˴�������Ҫ�Ĺٷ���
#include "delay.h"
#include "sys.h"
#include "Time.h"
#include "usart.h"	
#include "oled.h"
#include "Emm42_board.h"
#include "Emm42_delay.h"

extern u32 Sec;
extern u32 Sec_buf;


//����
int main(void)
{	
  __IO int32_t i = 0, j = 0;	u8 cntDir = 0;
	 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 															//���ڳ�ʼ��Ϊ115200
	delay_init();																			//��ʱ��ʼ�� 
	OLED_Init();																			//��ʼ��OLED  
	OLED_Clear(); 																		//OLED����
	 
	Emm42_board_init(); 															//��ʼ����������
	Emm42_delay_ms(1200);															//��ʱ1.2��ȴ�Emm�ջ��������ϵ��ʼ�����
	 
	OLED_ShowString(20,0,"Stepping Motor",12);
	OLED_Refresh_Gram();
	//	WHILEѭ��������
	//		* 1. ���ȡ��PA6��Stp���ţ�6400�Σ�Ҳ���Ƿ���3200��������ջ�������
	//		* 2. ��ʱ1�벢�ı�PA7��Dir���ţ���ƽ
	//		* 3. �ٷ���3200������
	//		*	����˳ʱ��תһȦ -> ��ʱ1�� -> ��ʱ��תһȦ -> ��ʱ1�� -> ˳ʱ��תһȦ -> ���ѭ��...
	while(1)
	{
		j = 3200;														
		while(j--);																										//�ߵ͵�ƽ��ʱ������������ʱ���һ��(���Ƶ��ת���ٶ�)
		Emm42_GPIO->ODR ^= Emm42_Stp_Pin;															//���ȡ��PA6��Stp���ţ�
			if(cntDir)	{--i;}	else	{++i;}															//��¼IOȡ��������IOȡ������ = 2������������
			//����PA6��Stp���ţ�ȡ����6400�Σ���������3200������
			//16ϸ���£�����3200��������ת��һȦ��1.8�ȵ����
			//���Լ�����6400�������ת��һȦ�����ڿ�ʼ�л�����
			if(i >= 6400)
			{
				Emm42_delay_ms(1000);																				/* ��ʱ1�� */
				GPIO_SetBits(Emm42_GPIO, Emm42_Dir_Pin);		cntDir = 1;			/* �ı�PA7��Dir���ţ���ƽ���л�����ʱ�뷽��ת�� */
			}
			else if(i == 0)
			{

				Emm42_delay_ms(1000);																				/* ��ʱ1�� */
				GPIO_ResetBits(Emm42_GPIO, Emm42_Dir_Pin);	cntDir = 0;			/* �ı�PA7��Dir���ţ���ƽ�л���˳ʱ�뷽��ת�� */
			}
	} 	
}
