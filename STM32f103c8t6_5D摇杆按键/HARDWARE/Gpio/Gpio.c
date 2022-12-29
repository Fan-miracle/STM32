#include "Gpio.h"


//使能APB1总线上的时钟，可同时多组开启
void RCC_APB1EN(uint16 EN_RCC)				//
{
	RCC_APB1PeriphClockCmd(EN_RCC,ENABLE);
}

//使能APB2总线上的时钟，可同时多组开启
void RCC_APB2EN(uint16 EN_RCC)
{
	RCC_APB2PeriphClockCmd(EN_RCC,ENABLE);
}

//初始化GPIO
//一次只能设置对一组的同一模式的GPIO
void GPIO_INIT(GPIO_TypeDef* GPIO_X, uint16 GPIO_Pin_x, uint8 GPIO_Mode, uint8 GPIO_PUT)
{
	GPIO_InitTypeDef GPIO_InitStr;               	//声明一个结构体变量
	
	GPIO_InitStr.GPIO_Pin = GPIO_Pin_x;							//口同时多引脚设置
	switch(GPIO_Mode)
	{
		case 0x00: GPIO_InitStr.GPIO_Mode = GPIO_Mode_AIN;         break;		//模拟输入
		case 0x04: GPIO_InitStr.GPIO_Mode = GPIO_Mode_IN_FLOATING; break;		//浮空输入
		case 0x28: GPIO_InitStr.GPIO_Mode = GPIO_Mode_IPD;				 break;   //下拉输入
		case 0x48: GPIO_InitStr.GPIO_Mode = GPIO_Mode_IPU; 				 break;		//上拉输入
		case 0x14: GPIO_InitStr.GPIO_Mode = GPIO_Mode_Out_OD;      break;		//开漏输出
		case 0x10: GPIO_InitStr.GPIO_Mode = GPIO_Mode_Out_PP;      break;		//推挽输出
		case 0x1C: GPIO_InitStr.GPIO_Mode = GPIO_Mode_AF_OD;     	 break;		//复用开漏输出
		case 0x18: GPIO_InitStr.GPIO_Mode = GPIO_Mode_AF_PP;			 break;		//复用推挽输出
	}
	if(GPIO_PUT==1)
		GPIO_InitStr.GPIO_Speed = GPIO_Speed_50MHz;		//默认50Hz,
	GPIO_Init(GPIO_X, &GPIO_InitStr);
	if(GPIO_PUT==1)
	  GPIO_SetBits(GPIO_X,GPIO_Pin_x);
}



