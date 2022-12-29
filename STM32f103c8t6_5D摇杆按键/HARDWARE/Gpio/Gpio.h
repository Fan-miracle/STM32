#ifndef _GPIO_H
#define _GPIO_H

#include "sys.h"

//APB1ENR
#define RCC_APB1_TIM2              ((uint32_t)0x00000001)
#define RCC_APB1_TIM3              ((uint32_t)0x00000002)
#define RCC_APB1_TIM4              ((uint32_t)0x00000004)
#define RCC_APB1_TIM5              ((uint32_t)0x00000008)
#define RCC_APB1_TIM6              ((uint32_t)0x00000010)
#define RCC_APB1_TIM7              ((uint32_t)0x00000020)
#define RCC_APB1_TIM12             ((uint32_t)0x00000040)
#define RCC_APB1_TIM13             ((uint32_t)0x00000080)
#define RCC_APB1_TIM14             ((uint32_t)0x00000100)
#define RCC_APB1_WWDG              ((uint32_t)0x00000800)
#define RCC_APB1_SPI2              ((uint32_t)0x00004000)
#define RCC_APB1_SPI3              ((uint32_t)0x00008000)
#define RCC_APB1_USART2            ((uint32_t)0x00020000)
#define RCC_APB1_USART3            ((uint32_t)0x00040000)
#define RCC_APB1_UART4             ((uint32_t)0x00080000)
#define RCC_APB1_UART5             ((uint32_t)0x00100000)
#define RCC_APB1_I2C1              ((uint32_t)0x00200000)
#define RCC_APB1_I2C2              ((uint32_t)0x00400000)
#define RCC_APB1_USB               ((uint32_t)0x00800000)
#define RCC_APB1_CAN1              ((uint32_t)0x02000000)
#define RCC_APB1_CAN2              ((uint32_t)0x04000000)
#define RCC_APB1_BKP               ((uint32_t)0x08000000)
#define RCC_APB1_PWR               ((uint32_t)0x10000000)
#define RCC_APB1_DAC               ((uint32_t)0x20000000)
#define RCC_APB1_CEC               ((uint32_t)0x40000000)

//APB2ENR
#define RCC_APB2_AFIO              ((uint32_t)0x00000001)
#define RCC_APB2_GPIOA             ((uint32_t)0x00000004)
#define RCC_APB2_GPIOB             ((uint32_t)0x00000008)
#define RCC_APB2_GPIOC             ((uint32_t)0x00000010)
#define RCC_APB2_GPIOD             ((uint32_t)0x00000020)
#define RCC_APB2_GPIOE             ((uint32_t)0x00000040)
#define RCC_APB2_GPIOF             ((uint32_t)0x00000080)
#define RCC_APB2_GPIOG             ((uint32_t)0x00000100)
#define RCC_APB2_ADC1              ((uint32_t)0x00000200)
#define RCC_APB2_ADC2              ((uint32_t)0x00000400)
#define RCC_APB2_TIM1              ((uint32_t)0x00000800)
#define RCC_APB2_SPI1              ((uint32_t)0x00001000)
#define RCC_APB2_TIM8              ((uint32_t)0x00002000)
#define RCC_APB2_USART1            ((uint32_t)0x00004000)
#define RCC_APB2_ADC3              ((uint32_t)0x00008000)
#define RCC_APB2_TIM15             ((uint32_t)0x00010000)
#define RCC_APB2_TIM16             ((uint32_t)0x00020000)
#define RCC_APB2_TIM17             ((uint32_t)0x00040000)
#define RCC_APB2_TIM9              ((uint32_t)0x00080000)
#define RCC_APB2_TIM10             ((uint32_t)0x00100000)
#define RCC_APB2_TIM11             ((uint32_t)0x00200000)

#define GPIO_Pin_0                 ((uint16_t)0x0001) 
#define GPIO_Pin_1                 ((uint16_t)0x0002)  
#define GPIO_Pin_2                 ((uint16_t)0x0004) 
#define GPIO_Pin_3                 ((uint16_t)0x0008) 
#define GPIO_Pin_4                 ((uint16_t)0x0010)  
#define GPIO_Pin_5                 ((uint16_t)0x0020)  
#define GPIO_Pin_6                 ((uint16_t)0x0040)  
#define GPIO_Pin_7                 ((uint16_t)0x0080)  
#define GPIO_Pin_8                 ((uint16_t)0x0100)  
#define GPIO_Pin_9                 ((uint16_t)0x0200)  
#define GPIO_Pin_10                ((uint16_t)0x0400)  
#define GPIO_Pin_11                ((uint16_t)0x0800)  
#define GPIO_Pin_12                ((uint16_t)0x1000)  
#define GPIO_Pin_13                ((uint16_t)0x2000)  
#define GPIO_Pin_14                ((uint16_t)0x4000)  
#define GPIO_Pin_15                ((uint16_t)0x8000)  
#define GPIO_Pin_All               ((uint16_t)0xFFFF) 


#define GPIO_OUT 1
#define GPIO_IN  0

void LED_Init(void);
void RCC_APB1EN(uint16 EN_RCC);
void RCC_APB2EN(uint16 EN_RCC);
void GPIO_INIT(GPIO_TypeDef* GPIO_X, uint16 GPIO_Pin_x, uint8 GPIO_Mode, uint8 GPIO_PUT);





#endif


