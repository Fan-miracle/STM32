#ifndef __Emm42_BOARD_H
#define __Emm42_BOARD_H

#include "stm32f10x.h"

#define		Emm42_RCC_GPIOA		RCC_APB2Periph_GPIOA
#define		Emm42_GPIO				GPIOA
#define		Emm42_En_Pin			GPIO_Pin_5
#define		Emm42_Stp_Pin			GPIO_Pin_6
#define		Emm42_Dir_Pin			GPIO_Pin_7

void Emm42_clock_init(void);
void Emm42_gpio_init(void);
void Emm42_board_init(void);

#endif
