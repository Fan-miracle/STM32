/*********************************************************************************************
* �ļ���iic.h
* ���ߣ�zonesion
* ˵����iicͷ�ļ�
* �޸ģ�
* ע�ͣ�
*********************************************************************************************/
#ifndef _IIC_H_
#define _IIC_H_
#include "sys.h"

//IO��������
#define SDA_IN()  {GPIOA->CRL&=0XFF0FFFFF;GPIOA->CRL|=8<<(4*(5-0));}
#define SDA_OUT() {GPIOA->CRL&=0XFF0FFFFF;GPIOA->CRL|=3<<(4*(5-0));}

//IO��������	 
//#define IIC_SCL    PAout(4)                                                   //SCL
//#define IIC_SDA    PAout(5)                                                   //SDA	 
//#define READ_SDA   PAin(5)                                                    //����SDA 

#define IIC_SCL    PBout(9)                                                   //SCL
#define IIC_SDA    PBout(8)                                                   //SDA	 
#define READ_SDA   PBin(8)                                                    //����SDA 

//IIC���в�������
void IIC_Init(void);                                                           //��ʼ��IIC��IO��				 
void IIC_Start(void);				                                           //����IIC��ʼ�ź�
void IIC_Stop(void);	  			                                           //����IICֹͣ�ź�
void IIC_Send_Byte(u8 txd);			                                           //IIC����һ���ֽ�
u8 IIC_Read_Byte(unsigned char ack);                                           //IIC��ȡһ���ֽ�
u8 IIC_Wait_Ack(void); 				                                           //IIC�ȴ�ACK�ź�
void IIC_Ack(void);					                                           //IIC����ACK�ź�
void IIC_NAck(void);				                                           //IIC������ACK�ź�

void IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 IIC_Read_One_Byte(u8 daddr,u8 addr);	
			 
u8 iicDevReadByte(u8 devaddr,u8 addr);	                                       /*��һ�ֽ�*/
void iicDevWriteByte(u8 devaddr,u8 addr,u8 data);	                           /*дһ�ֽ�*/
void iicDevRead(u8 devaddr,u8 addr,u8 len,u8 *rbuf);                           /*������ȡ����ֽ�*/
void iicDevWrite(u8 devaddr,u8 addr,u8 len,u8 *wbuf);        

/*********************************************************************************************
* �ⲿԭ�ͺ���
*********************************************************************************************/
//void iic_delay_us(unsigned int i);
void iic_init(void);
void iic_start(void);
void iic_stop(void);
void iic_send_ack(int ack);
int iic_recv_ack(void);
unsigned char iic_write_byte(unsigned char data);
unsigned char iic_read_byte(unsigned char ack);
//void delay(unsigned int t);

#endif 

