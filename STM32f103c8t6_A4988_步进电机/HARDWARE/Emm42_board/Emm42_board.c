#include "Emm42_board.h"

/**
	*	@brief		外设时钟初始化
	*	@param		无
	*	@retval		无
	*/
void Emm42_clock_init(void)
{
	RCC_APB2PeriphClockCmd(Emm42_RCC_GPIOA, ENABLE);	//使能GPIOA端口时钟
}

/**
	*	@brief		gpio引脚初始化
	*	@param		无
	*	@retval		无
	*/
void Emm42_gpio_init(void)
{
/**************************************************************
	*	1. STM32的PA5接Emm42闭环驱动的En引脚（确保Emm42_闭环驱动屏幕上的En选项选择Hold或者L，默认是Hold）
	*	2. STM32的PA6接Emm42闭环驱动的Stp引脚
	* 3. STM32的PA7接Emm42闭环驱动的Dir引脚
***************************************************************/
 GPIO_InitTypeDef  GPIO_InitStructure;
 GPIO_InitStructure.GPIO_Pin = Emm42_En_Pin | Emm42_Stp_Pin | Emm42_Dir_Pin;
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 GPIO_Init(Emm42_GPIO, &GPIO_InitStructure);
 GPIO_ResetBits(Emm42_GPIO, Emm42_En_Pin | Emm42_Stp_Pin | Emm42_Dir_Pin);
}

/**
	*	@brief		板载初始化
	*	@param		无
	*	@retval		无
	*/
void Emm42_board_init(void)
{
	Emm42_clock_init();	/* 开启外设时钟 */
	Emm42_gpio_init();	/* 初始化GPIO */
}
