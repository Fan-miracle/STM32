/*****************************************************************************************************************************************************														
����֪ʶ������
TIM1_ETR     PA12            
TIM1_CH1     PA8            TIM2_CH1_ETR PA0            TIM3_CH1     PA6            TIM4_CH1     PB6 
TIM1_CH2     PA9            TIM2_CH2     PA1            TIM3_CH2     PA7            TIM4_CH2     PB7
TIM1_CH3     PA10           TIM2_CH3     PA2            TIM3_CH3     PB0            TIM4_CH3     PB8 
TIM1_CH4     PA11           TIM2_CH4     PA3            TIM3_CH4     PB1            TIM4_CH4     PB9  

 ����1�� PA9-TX  PA10-RX      ����2��PA2-TX  PA3-RX      ����3�� PB10-TX PB11-RX
 
		 SG90������Ʒ�����
                         --�ߵ�ƽʱ��ΪT1--                          ������20ms:
                            ���� ���� ���� ����
                           |           |                              �ߵ�ƽʱ��T1Ϊ 0.5ms     ���ת��0��
													 |           |                              �ߵ�ƽʱ��T1Ϊ   1ms     ���ת��45��
													 |           |                              �ߵ�ƽʱ��T1Ϊ 1.5ms     ���ת��90��
													 |           |                              �ߵ�ƽʱ��T1Ϊ   2ms     ���ת��135��
														             ���� ���� ���� ���� ���� ����            �ߵ�ƽʱ��T1Ϊ 2.5ms     ���ת��180��
                           --------������ T2Ϊ20ms--------
												 
			����˼·��1��Ctrl + c  Ȼ��  Ctrl + v     ����������				

											|                
											|
											|
								--------------
                
								��180�ȶ��Ϊ�����壺�ߵ�ƽʱ��T1Ϊ 1.5ms     ���ת��90��    Ϊ     0��
								
								           ��Զ��ԣ��ߵ�ƽʱ��T1Ϊ 0.5ms     ���ת��0��     Ϊ   -90��
                                     �ߵ�ƽʱ��T1Ϊ   1ms     ���ת��45��    Ϊ   -45��
																		 �ߵ�ƽʱ��T1Ϊ 1.5ms     ���ת��90��    Ϊ     0��
                                     �ߵ�ƽʱ��T1Ϊ   2ms     ���ת��135��   Ϊ   +45��
																		 �ߵ�ƽʱ��T1Ϊ 2.5ms     ���ת��180��   Ϊ   +90��
																		 
																		 
		//-90��    ���ת��0��
		//TIM_SetCompare1(TIM4,1945);//ռ�ձ�(2000-1945)/2000*20ms=0.5ms 
		
		//-45��    ���ת��45��
		//TIM_SetCompare1(TIM4,1900);//ռ�ձ�(2000-1900)/2000*20ms=1ms
		
		//0��      ���ת��90��
		//TIM_SetCompare1(TIM4,1850);//ռ�ձ�(2000-1850)/2000*20ms=1.5ms
		
		//+45��    ���ת��135��
		//TIM_SetCompare1(TIM4,1800);//ռ�ձ�(2000-1800)/2000*20ms=2ms
		
		//+90��    ���ת��180��
		//TIM_SetCompare1(TIM4,1750);//ռ�ձ�(2000-1750)/2000*20ms=2.5ms
	
	
*************************************************************************************************************************************************/

#include "PWM.h"

//TIM4 PWM���ֳ�ʼ?
//PWM�����ʼ��
//arr:�Զ���װ��ֵ        psc:ʱ��Ԥ��Ƶ��


/******************************************************************************
* ģ������
* ��Ŀ���Ż����� ��  8·PWM���
* ��������       ��  2022/05/14
* ������         ��  ־��
* ģ�鹦��       ��  
* �޸�����       ��
* �ο��ĵ�       ��  ��ͨSTM32F4�⺯����
* ��Ŀ����ƽ̨   ��  STM32F103C8T6
* ����           ��  PWM��һ�㲽��
										 ʵ��Ҫ��TIM4������PWM���,��ʹ��TIM4��ͨ��1��2��3��4,�����ӳ�䵽PB6\PB7\PB8\PB9,����PWM�����ƶ��

											1��ʹ�ܶ�ʱ�������IOʱ�ӣ����ú���:RCC_APB1PeriphClockCmd();RCC_APB2PeriphClockCmd();
											2����ʼ��IOΪ���ù�����������ú���:GPIO_Init();�������ǰ�PB6\PB7\PB8\PB9������ʱ����PWM�������,Ҫ��ӳ�����ü�GPIO_Mode_AF_PP;
											   �������������������Ҫ����AFIOʱ�ӡ�
												 
											3����ʼ����ʱ�������ú���:TIM_TimeBaseInit();
											4����ʼ������Ƚϲ��������ú���:TIM_OCInitStructure();
											5��ʹ��Ԥװ�ؼĴ��������ú���:TIM_OC1PreloadConfig();
											6��ʹ�ܶ�ʱ�������ú���:TIM_Cmd();											
											7�����ö����ʼ�Ƕȣ����ú�����TIM_SetCompare1(TIM4,1945);
															
����֪ʶ������
TIM1_ETR     PA12            
TIM1_CH1     PA8            TIM2_CH1_ETR PA0            TIM3_CH1     PA6            TIM4_CH1     PB6 
TIM1_CH2     PA9            TIM2_CH2     PA1            TIM3_CH2     PA7            TIM4_CH2     PB7
TIM1_CH3     PA10           TIM2_CH3     PA2            TIM3_CH3     PB0            TIM4_CH3     PB8 
TIM1_CH4     PA11           TIM2_CH4     PA3            TIM3_CH4     PB1            TIM4_CH4     PB9  

					
//TIM3������ӳ��
	
	*�鿴�����ֲᣬ���ŵĶ�ʱ��ͨ������ȫӳ�䣬���ǲ���ӳ��
	*���ߵ��ò�������ͬ
	*��ȫӳ�� ��GPIO_FullRemap_TIM4
	*����ӳ�� ��GPIO_PartialRemap_TIM4
	*
   
	//����TIM4_CH1��ӳ�䵽PB6��
  //GPIO_PinRemapConfig(GPIO_PartialRemap_TIM4,ENABLE);
*******************************************************************************/


void TIM4_PWM_Init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;   					 				//��ʼ��TIM4����ARR,PSC�������PWM������
	TIM_OCInitTypeDef  TIM_OCInitStructure;                         //PWMͨ������
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);     			  //ʹ�ܶ�ʱ��4
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);      				//AFIO���ù���ʱ��ʹ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  ,ENABLE);   				//GPIOBʹ��
	
	
	//���ø�����Ϊ�����������
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;	       //TIM4_CH1/CH2/CH3/CH4
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;                                   //�����������
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);                                             //��ʼ��GPIO
	
	
	//��ʼ��TIM4,����TIM4��ARR��PSC
	TIM_TimeBaseStruct.TIM_Period = arr;                   					 //�����Զ���װ������ֵ   //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 
	TIM_TimeBaseStruct.TIM_Prescaler = psc;                					 //����Ԥ��Ƶֵ           //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  ����Ƶ
	TIM_TimeBaseStruct.TIM_ClockDivision = 0;               				 //����ʱ�ӷָ�TDTS = Tck_tim	
	TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;         //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStruct);                      //����ָ��������ʼ��TIMx  //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
	
	
	
	//�����ʼ��������ѡ���ĸ�ͨ������ʼ��PWM���ģʽ���Ƚ�������ԡ� �Ƚ����ʹ�ܡ� �Ƚ�ֵCCRx��ֵ
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;                  //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;      //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_Pulse = 0;                                 //���ô�װ�벶��ȽϼĴ���������ֵ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;          //�������:TIM����Ƚϼ��Ը�
	
	TIM_OC1Init(TIM4,&TIM_OCInitStructure);                            //����TIMX�Ĳ����趨��ʼ������ TIM1 ch1 ch2 ch3 ch4	
	TIM_OC2Init(TIM4,&TIM_OCInitStructure);
	TIM_OC3Init(TIM4,&TIM_OCInitStructure);
  TIM_OC4Init(TIM4,&TIM_OCInitStructure);

	
	TIM_OC1PreloadConfig(TIM4,TIM_OCPreload_Enable);  //ʹ��Ԥװ�ؼĴ���
  TIM_OC2PreloadConfig(TIM4,TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM4,TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM4,TIM_OCPreload_Enable);
	
	TIM_ARRPreloadConfig(TIM4, ENABLE); //ʹ��TIMx��ARR�ϵ�Ԥװ�ؼĴ���	
	
	TIM_Cmd(TIM4,ENABLE);     //ʹ��TIM4
	
	
	//�������ú���
	//���ã����ĸ�ͨ����ѡ��һ�������ñȽ�ֵ��ͨ���ڳ�ʼ���������Ѿ������˱Ƚ�ֵ���˺������ڳ���ʼ��֮����޸�
	//TIM_SetCompare1(TIM4,1850);
	//TIM_SetCompare2(TIM4,1850);
	//TIM_SetCompare3(TIM4,1850);
	//TIM_SetCompare4(TIM4,1850);
	
	

}








