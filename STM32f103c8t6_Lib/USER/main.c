#include "delay.h"
#include "sys.h"
#include "usart.h"	
#include "oled.h"




int main(void)
{	

		
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);	//串口初始化为115200
	delay_init();		//延时初始化 
	OLED_Init();			//初始化OLED  
	OLED_Clear(); 			//OLED清屏
	
	
	OLED_ShowString(20,0,"MPU6050 OK",12); 
	OLED_Refresh_Gram();
	
 	while(1)
	{

	
	} 	
}

