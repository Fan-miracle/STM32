//#include "stm32f10x_conf.h"					//在此处打开所需要的官方库
#include "delay.h"
#include "sys.h"
#include "usart.h"	
#include "Time.h"
#include "oled.h"

#include "PWM.h"


extern u32 Sec;
extern u32 Sec_buf;


//LD-2701的旋转角度为270度，从1750~1950对应0~270度；
int main(void)
{	
	int i = 50;_Bool dir_flag = 1;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);	//串口初始化为115200
	delay_init();		//延时初始化 
	TIM2_Int_Init(999,71,2,0);				                //定时1ms			按键检测，计秒
	TIM3_Int_Init(999,719,2,1);				                //定时10ms			用于事件执行
	OLED_Init();			//初始化OLED  
	OLED_Clear(); 			//OLED清屏
	TIM4_PWM_Init(1999,719);   //PWM频率=72000000/（719+1）/（1999+1）=50hz=20ms
	
	OLED_ShowString(0,0,"Servo Angle:",12); 
	OLED_Refresh_Gram();
	
 	while(1)
	{
		if(Sec > 200)
		{
			Sec = 0;
			if(dir_flag)
			{
				i=i+1;
			}
			else
			{
				i=i-1;
			}
			TIM_SetCompare1(TIM4,2000-i);			//PB6;  1750=2.5ms=90度			1800=2ms=45度;			1850=1.5s=0度;		1900=1ms=-45度;			1950=0.5ms=-90度
			TIM_SetCompare2(TIM4,2000-i);			//PB7;
			OLED_ShowNum(40,0,i,8,12);		//显示整数部分	  
			OLED_ShowNum(40,20,dir_flag,8,12);		//显示整数部分	  			
			OLED_Refresh_Gram();
			if(i>=250)
			{
				dir_flag=0;
			}
			else if(i<=50)
			{
				dir_flag=1;
			}				
			
		}
	} 	
}

