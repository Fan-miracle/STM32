//#include "stm32f10x_conf.h"					//在此处打开所需要的官方库
#include "delay.h"
#include "sys.h"
#include "usart.h"	

#include "led.h"
#include "key.h"
#include "Time.h"
#include "oled.h"

extern u32 Sec;								//定时器2
extern u32 Sec_buf;						//定时器3


int UP=0;//上方向按键
int DWN = 0;//下方向按键
int LFT =0;//|左方向按键
int RHT =0;//|右方向按键
int MID =0;//|中间按键
int SET_A =0; //|设置按键
int RST_B =0;//|复位按键

int main(void)
{	
	u8 key;   			//按键检测
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);	//串口初始化为115200
	delay_init();				//延时初始化 
	TIM2_Int_Init(999,71,2,0);				                //定时1ms			按键检测，计秒
	TIM3_Int_Init(999,719,2,1);				                //定时10ms			用于事件执行
	
	OLED_Init();				//初始化OLED  
	OLED_Clear(); 			//OLED清屏
	Key_Init();					//按键初始化
	LED_Init();					//LED初始化
	
	OLED_ShowString(0,0,"SET_A:",12);
	OLED_ShowString(64,0,"RST_B:",12);
	OLED_ShowString(0,15,"UP:",12);
	OLED_ShowString(64,15,"DWN:",12);
	OLED_ShowString(0,30,"LFT:",12);
	OLED_ShowString(64,30,"RHT:",12);
	OLED_ShowString(0,45,"MID:",12);
	OLED_ShowString(64,45,"LED:",12);
	OLED_Refresh_Gram();
 	while(1)
	{
		key=KEY_Scan(0); 
		if(key)
		{
			switch(key)
			{
				case KEY_UP_PRES:  UP = UP+1;  	 break;
				case KEY_DWN_PRES: DWN = DWN+1;  break;
				case KEY_LFT_PRES: LFT = LFT+1;  break;
				case KEY_RHT_PRES: RHT = RHT+1;  break;
				case KEY_MID_PRES: MID = MID+1;  break;
				case KEY_SET_PRES: SET_A = SET_A+1;  break;
				case KEY_RST_PRES: RST_B = RST_B+1;  break;
				default: break;
			}
		}
		if(Sec > 1000)
		{
			Sec = 0;
			LED0=!LED0;
		}
		OLED_ShowNum(32,0,SET_A,2,12);		  //显示整数部分	 
		OLED_ShowNum(96,0,RST_B,2,12);		//显示整数部分	 
		OLED_ShowNum(32,15,UP,2,12);		//显示整数部分	 
    OLED_ShowNum(96,15,DWN,2,12);		//显示整数部分	
		OLED_ShowNum(32,30,LFT,2,12);		//显示整数部分			
		OLED_ShowNum(96,30,RHT,2,12);	//显示整数部分	
		OLED_ShowNum(32,45,MID,2,12);	//显示整数部分	
		OLED_ShowNum(96,45,LED0,2,12);	//显示整数部分	
		OLED_Refresh_Gram();
	} 	
}

