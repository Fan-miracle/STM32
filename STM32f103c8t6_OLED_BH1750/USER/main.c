//#include "stm32f10x_conf.h"					//打开所需要的库
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "Time.h"
#include "oled.h"

#include "iic.h"
#include "BH1750.h"

extern u32 Sec;
extern u32 Sec_buf;

int main(void)
{	
	float light_data = 0;
		
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);	//串口初始化为115200
	delay_init();		//延时初始化 
	TIM2_Int_Init(999,71,2,0);				                //定时1ms			按键检测，计秒
	TIM3_Int_Init(999,719,2,1);				                //定时10ms			用于事件执行
	OLED_Init();			//初始化OLED  
	OLED_Clear(); 			//OLED清屏
	
	
	OLED_ShowString(0,0,"light:",12); 
	OLED_Refresh_Gram();
	bh1750_init();
	delay_ms(750);
 	while(1)
	{
		if(Sec > 200)
		{
			Sec = 0;
			light_data = bh1750_get_data(); //获取光照数据
			OLED_ShowNum(35,0,light_data,4,12);		//显示整数部分	    
			OLED_Refresh_Gram();
		}
	
	} 	
}

