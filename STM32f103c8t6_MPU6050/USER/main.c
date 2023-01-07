#include "delay.h"
#include "sys.h"
#include "oled.h"
#include "led.h"
#include "usart.h"	
#include "mpu6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h" 


int main(void)
 {	
	u8 t=0,a=0,report=1;			//默认开启上报
	u8 key;
	float pitch,roll,yaw; 		//欧拉角
	short aacx,aacy,aacz;		//加速度传感器原始数据
	short gyrox,gyroy,gyroz;	//陀螺仪原始数据
	short temp;					//温度	
	short temp1,pitch1,roll1,yaw1;
		
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);	//串口初始化为115200
	delay_init();		//延时初始化 
	LED_Init();		//LED初始化
	OLED_Init();			//初始化OLED  
	OLED_Clear(); 			//OLED清屏
	MPU_Init();					//初始化MPU6050
	
	OLED_ShowString(20,0,"MPU6050",12);
	OLED_Refresh_Gram();

	while(mpu_dmp_init())
 	{
		OLED_ShowString(20,0,"MPU6050 Error",12);
		OLED_Refresh_Gram();
 		delay_ms(500);
	}  
	
	OLED_ShowString(20,0,"MPU6050 OK",12); 
 	OLED_ShowString(0,14," Temp:     . C",12);	
 	OLED_ShowString(0,27,"Pitch:     . C",12);	
 	OLED_ShowString(0,39," Roll:     . C",12);	 
 	OLED_ShowString(0,51," Yaw :     . C",12);	 
	OLED_Refresh_Gram();
	
 	while(1)
	{

		if(mpu_dmp_get_data(&pitch,&roll,&yaw)==0)
		{ 
			temp=MPU_Get_Temperature();	//得到温度值
			MPU_Get_Accelerometer(&aacx,&aacy,&aacz);	//得到加速度传感器数据
			MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);	//得到陀螺仪数据
			if((t%10)==0)
			{ 
				if(temp<0)
				{
					OLED_ShowChar(40,14,'-',12,1);		//显示负号
					temp=-temp;		//转为正数
				}else OLED_ShowChar(40,14,' ',12,1);		//去掉负号 
				OLED_ShowNum(40+8,14,temp/100,3,12);		//显示整数部分	    
				OLED_ShowNum(40+8+8+8+8,14,temp%10,1,12);		//显示小数部分 
				temp1=temp;
				
				temp=pitch*10;				
				if(temp<0)
				{
					OLED_ShowChar(40,27,'-',12,1);		//显示负号
					temp=-temp;		//转为正数
				}else OLED_ShowChar(40,27,' ',12,1);		//去掉负号 
				OLED_ShowNum(40+8,27,temp/10,3,12);		//显示整数部分	    
				OLED_ShowNum(40+8+8+8+8,27,temp%10,1,12);		//显示小数部分 
				pitch1=temp;
				
				temp=roll*10;				
				if(temp<0)
				{
					OLED_ShowChar(40,39,'-',12,1);		//显示负号
					temp=-temp;		//转为正数
				}else OLED_ShowChar(40,39,' ',12,1);		//去掉负号 
				OLED_ShowNum(40+8,39,temp/10,3,12);		//显示整数部分	    
				OLED_ShowNum(40+8+8+8+8,39,temp%10,1,12);		//显示小数部分 
				roll1=temp;
				
				temp=yaw*10;
				if(temp<0)
				{
					OLED_ShowChar(40,51,'-',12,1);		//显示负号
					temp=-temp;		//转为正数
				}else OLED_ShowChar(40,51,' ',12,1);		//去掉负号 
				OLED_ShowNum(40+8,51,temp/10,3,12);		//显示整数部分	    
				OLED_ShowNum(40+8+8+8+8,51,temp%10,1,12);		//显示小数部分  
				yaw1=temp;
				
				OLED_Refresh_Gram();
				printf("temp1:%d.%d   pitch1:%d.%d     roll1:%d.%d     yaw1:%d.%d  \r\n",temp1/100,temp1%10,
				pitch1/10,pitch1%10,roll1/10,roll1%10,yaw1/10,yaw1%10);
				t=0;
				a++;
				if(a==100)LED0=!LED0;//LED闪烁				
			}
		}
		t++; 
	} 	
}

