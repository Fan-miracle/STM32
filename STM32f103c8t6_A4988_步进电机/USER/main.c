//#include "stm32f10x_conf.h"					//在此处打开所需要的官方库
#include "delay.h"
#include "sys.h"
#include "Time.h"
#include "usart.h"	
#include "oled.h"
#include "Emm42_board.h"
#include "Emm42_delay.h"

extern u32 Sec;
extern u32 Sec_buf;


//程序
int main(void)
{	
  __IO int32_t i = 0, j = 0;	u8 cntDir = 0;
	 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		//设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);	 															//串口初始化为115200
	delay_init();																			//延时初始化 
	OLED_Init();																			//初始化OLED  
	OLED_Clear(); 																		//OLED清屏
	 
	Emm42_board_init(); 															//初始化板载外设
	Emm42_delay_ms(1200);															//延时1.2秒等待Emm闭环驱动板上电初始化完毕
	 
	OLED_ShowString(20,0,"Stepping Motor",12);
	OLED_Refresh_Gram();
	//	WHILE循环发脉冲
	//		* 1. 异或取反PA6（Stp引脚）6400次，也就是发送3200个脉冲给闭环驱动板
	//		* 2. 延时1秒并改变PA7（Dir引脚）电平
	//		* 3. 再发送3200个脉冲
	//		*	现象：顺时针转一圈 -> 延时1秒 -> 逆时针转一圈 -> 延时1秒 -> 顺时针转一圈 -> 如此循环...
	while(1)
	{
		j = 3200;														
		while(j--);																										//高低电平的时间间隔，即脉冲时间的一半(控制电机转动速度)
		Emm42_GPIO->ODR ^= Emm42_Stp_Pin;															//异或取反PA6（Stp引脚）
			if(cntDir)	{--i;}	else	{++i;}															//记录IO取反次数（IO取反次数 = 2倍的脉冲数）
			//控制PA6（Stp引脚）取反了6400次，即发送了3200个脉冲
			//16细分下，发送3200个脉冲电机转动一圈（1.8度电机）
			//所以计数到6400即电机旋转了一圈后，现在开始切换方向
			if(i >= 6400)
			{
				Emm42_delay_ms(1000);																				/* 延时1秒 */
				GPIO_SetBits(Emm42_GPIO, Emm42_Dir_Pin);		cntDir = 1;			/* 改变PA7（Dir引脚）电平，切换到逆时针方向转动 */
			}
			else if(i == 0)
			{

				Emm42_delay_ms(1000);																				/* 延时1秒 */
				GPIO_ResetBits(Emm42_GPIO, Emm42_Dir_Pin);	cntDir = 0;			/* 改变PA7（Dir引脚）电平切换到顺时针方向转动 */
			}
	} 	
}
