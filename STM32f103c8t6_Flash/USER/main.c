//#include "stm32f10x_conf.h"					//�ڴ˴�������Ҫ�Ĺٷ���
#include "delay.h"
#include "sys.h"
#include "Time.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "oled.h"

#include "stmflash.h"

extern u16 A_Parameter[10],B_Parameter[10],Flash_Parameter[10];  //Flash�������

u16 AAA = 0;
u16 BBB = 0;
u16 CCC = 0;


extern void Data_save(void);
extern void Data_read(void);
int main(void)
{	

		
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	//���ڳ�ʼ��Ϊ115200
	delay_init();		//��ʱ��ʼ�� 
	Key_Init();																				//������ʼ��
	LED_Init();																				//LED��ʼ��
	OLED_Init();			//��ʼ��OLED  
	OLED_Clear(); 			//OLED����

	OLED_ShowString(0,0,"AAA:",12); 
	OLED_ShowString(0,14,"BBB:",12); 
	OLED_ShowString(0,28,"CCC:",12); 
	OLED_Refresh_Gram();
	
	Data_read();
 	while(1)
	{
		AAA += 1;
		BBB += 5;
		CCC += 7;
		Data_save();
		printf("%d,%d,%d\r\n",AAA,BBB,CCC);
		
		OLED_ShowNum(64,0,AAA,4,12);		//��ʾ��������	
		OLED_ShowNum(64,14,BBB,4,12);
		OLED_ShowNum(64,28,CCC,4,12);  
		OLED_Refresh_Gram();		
		delay_ms(1000);
	} 	
}


void Data_save(void)
{
	B_Parameter[0]=AAA;		
	B_Parameter[1]=BBB;	
	B_Parameter[2]=CCC;
	STMFLASH_Write(FLASH_SAVE_ADDR,(u16*)B_Parameter,3);	
}


void Data_read(void)
{
	STMFLASH_Read(FLASH_SAVE_ADDR,(u16*)A_Parameter,10);
	//Flashδд�����ݵ�ʱ������Ϊ65535
	if(A_Parameter[0]==65535&&A_Parameter[1]==65535&&A_Parameter[2]==65535)
	{

	}
	else//Flash�������ݣ����ж�ȡ
	{		
		AAA = A_Parameter[0];
		BBB = A_Parameter[1];
		CCC = A_Parameter[2];
	}
}
