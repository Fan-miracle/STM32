//#include "stm32f10x_conf.h"					//在此处打开所需要的官方库
#include "delay.h"
#include "sys.h"
#include "usart.h"	
#include "Time.h"
#include "oled.h"

#include "Emm42_board.h"
#include "Emm42_delay.h"
#include "Emm42_usart.h"
#include "Emm42_me.h"


float MotorAngle;					//电机位置
float AngleError;					//位置误差
int32 Pulse_num;					//脉冲数


int main(void)
{	

		
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);	//串口初始化为115200
	delay_init();		//延时初始化 
	TIM2_Int_Init(999,71,2,0);				                //定时1ms			按键检测，计秒
	TIM3_Int_Init(999,719,2,1);				                //定时10ms			用于事件执行
	OLED_Init();			//初始化OLED  
	OLED_Clear(); 			//OLED清屏
	
	Emm42_board_init(); 															//初始化板载外设
	Emm42_delay_ms(1200);															//延时1.2秒等待Emm闭环驱动板上电初始化完毕
	OLED_ShowString(20,0,"MPU6050 OK",12); 
	OLED_Refresh_Gram();
	
 	while(1)
	{
		Motor_speed_pos();
//Motor_speed();
//		Emm42_delay_ms(8000);
//		Motor_Enabled();
	  MotorAngle = Emm42_MotorAngle();					//电机位置
		AngleError = Emm42_MotorError();					//位置误差
		Pulse_num = Emm42_Pulse_count();					//脉冲数
		OLED_ShowNum(40+8,14,MotorAngle,8,12);		//显示整数部分	  
		OLED_ShowNum(40+8,27,AngleError,8,12);		//显示整数部分	 
		OLED_ShowNum(40+8,39,Pulse_num,8,12);		//显示整数部分	    
		OLED_Refresh_Gram();
//	
	
	} 	
}

