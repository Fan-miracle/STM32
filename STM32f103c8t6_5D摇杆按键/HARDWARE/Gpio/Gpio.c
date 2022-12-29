#include "Gpio.h"


//ʹ��APB1�����ϵ�ʱ�ӣ���ͬʱ���鿪��
void RCC_APB1EN(uint16 EN_RCC)				//
{
	RCC_APB1PeriphClockCmd(EN_RCC,ENABLE);
}

//ʹ��APB2�����ϵ�ʱ�ӣ���ͬʱ���鿪��
void RCC_APB2EN(uint16 EN_RCC)
{
	RCC_APB2PeriphClockCmd(EN_RCC,ENABLE);
}

//��ʼ��GPIO
//һ��ֻ�����ö�һ���ͬһģʽ��GPIO
void GPIO_INIT(GPIO_TypeDef* GPIO_X, uint16 GPIO_Pin_x, uint8 GPIO_Mode, uint8 GPIO_PUT)
{
	GPIO_InitTypeDef GPIO_InitStr;               	//����һ���ṹ�����
	
	GPIO_InitStr.GPIO_Pin = GPIO_Pin_x;							//��ͬʱ����������
	switch(GPIO_Mode)
	{
		case 0x00: GPIO_InitStr.GPIO_Mode = GPIO_Mode_AIN;         break;		//ģ������
		case 0x04: GPIO_InitStr.GPIO_Mode = GPIO_Mode_IN_FLOATING; break;		//��������
		case 0x28: GPIO_InitStr.GPIO_Mode = GPIO_Mode_IPD;				 break;   //��������
		case 0x48: GPIO_InitStr.GPIO_Mode = GPIO_Mode_IPU; 				 break;		//��������
		case 0x14: GPIO_InitStr.GPIO_Mode = GPIO_Mode_Out_OD;      break;		//��©���
		case 0x10: GPIO_InitStr.GPIO_Mode = GPIO_Mode_Out_PP;      break;		//�������
		case 0x1C: GPIO_InitStr.GPIO_Mode = GPIO_Mode_AF_OD;     	 break;		//���ÿ�©���
		case 0x18: GPIO_InitStr.GPIO_Mode = GPIO_Mode_AF_PP;			 break;		//�����������
	}
	if(GPIO_PUT==1)
		GPIO_InitStr.GPIO_Speed = GPIO_Speed_50MHz;		//Ĭ��50Hz,
	GPIO_Init(GPIO_X, &GPIO_InitStr);
	if(GPIO_PUT==1)
	  GPIO_SetBits(GPIO_X,GPIO_Pin_x);
}



