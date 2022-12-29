#include "Time.h"
#include "stm32f10x_tim.h"

u32 Sec=0;
u32 Sec_buf=0;
uint8 Flag_1ms = 0;
uint8 Flag_10ms = 0;

/******************************		ͨ�ö�ʱ��		**********************************/
//ͨ�ö�ʱ���жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��

//��ʱ��TIM2��ʼ��
void TIM2_Int_Init(u16 arr,u16 psc, uint8 Preem, uint8 Resq)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStr;
	NVIC_InitTypeDef NVIC_InitStr;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //ʱ��ʹ��
	
	TIM_TimeBaseStr.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStr.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStr.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStr.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStr); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM3�ж�,��������ж�

	//�ж����ȼ�NVIC����
	NVIC_InitStr.NVIC_IRQChannel = TIM2_IRQn;  //TIM3�ж�
	NVIC_InitStr.NVIC_IRQChannelPreemptionPriority = Preem;  //��ռ���ȼ�0��
	NVIC_InitStr.NVIC_IRQChannelSubPriority = Resq;  //�����ȼ�3��
	NVIC_InitStr.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStr);  //��ʼ��NVIC�Ĵ���

	TIM_Cmd(TIM2, ENABLE);  //ʹ��TIMx
}

void TIM3_Int_Init(u16 arr,u16 psc,uint8 Preem, uint8 Resq)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStr;
	NVIC_InitTypeDef NVIC_InitStr;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //ʱ��ʹ��
	
	//��ʱ��TIM3��ʼ��
	TIM_TimeBaseStr.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStr.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStr.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStr.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStr); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM3�ж�,��������ж�

	//�ж����ȼ�NVIC����
	NVIC_InitStr.NVIC_IRQChannel = TIM3_IRQn;  //TIM3�ж�
	NVIC_InitStr.NVIC_IRQChannelPreemptionPriority = Preem;  //��ռ���ȼ�0��
	NVIC_InitStr.NVIC_IRQChannelSubPriority = Resq;  //�����ȼ�3��
	NVIC_InitStr.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStr);  //��ʼ��NVIC�Ĵ���

	//TIM_Cmd(TIM3, ENABLE);  //ʹ��TIMx					 
}



void TIM4_Int_Init(u16 arr,u16 psc, uint8 Preem, uint8 Resq)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStr;
	NVIC_InitTypeDef NVIC_InitStr;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //ʱ��ʹ��
	
	//��ʱ��TIM3��ʼ��
	TIM_TimeBaseStr.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStr.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStr.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStr.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStr); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM3�ж�,��������ж�

	//�ж����ȼ�NVIC����
	NVIC_InitStr.NVIC_IRQChannel = TIM4_IRQn;  //TIM3�ж�
	NVIC_InitStr.NVIC_IRQChannelPreemptionPriority = Preem;  //��ռ���ȼ�0��
	NVIC_InitStr.NVIC_IRQChannelSubPriority = Resq;  //�����ȼ�3��
	NVIC_InitStr.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStr);  //��ʼ��NVIC�Ĵ���

	TIM_Cmd(TIM4, ENABLE);  //ʹ��TIMx
}



//��ʱ��2�жϷ������
void TIM2_IRQHandler(void)   //TIM2�ж�
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)  //���TIM3�����жϷ������
	{
		Sec++;
		if(Sec>1000000)
			Sec=0;
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);  //���TIMx�����жϱ�־ 
	}
}


//��ʱ��3�жϷ������
void TIM3_IRQHandler(void)   //TIM3�ж�
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //���TIM3�����жϷ������
	{
		Sec_buf++;
		if(Sec_buf>1000000)
			Sec_buf=0;
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);  //���TIMx�����жϱ�־ 
	}
}


/////////////////////  usmart.c�ļ�ʹ��	 ///////////
////��ʱ��4�жϷ������
//void TIM4_IRQHandler(void)   //TIM4�ж�
//{
//	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)  //���TIM3�����жϷ������
//	{
//		//�ж��߼���������
//		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);  //���TIMx�����жϱ�־ 
//	}
//}

//#include "stm32f103_capture.h"  �������벶��
//��ʱ��5�жϷ������
//void TIM5_IRQHandler(void)   //TIM5�ж�
//{
//	if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)  //���TIM3�����жϷ������
//	{
//		//�ж��߼���������
//		TIM_ClearITPendingBit(TIM5, TIM_IT_Update);  //���TIMx�����жϱ�־ 
//	}
//}








