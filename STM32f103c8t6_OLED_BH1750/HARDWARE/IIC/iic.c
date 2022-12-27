/*********************************************************************************************
* �ļ���iic.c
* ���ߣ�zonesion
* ˵����iic��������
* �޸ģ�
* ע�ͣ�
*********************************************************************************************/

/*********************************************************************************************
* ͷ�ļ�
*********************************************************************************************/
#include "stm32f10x.h"
#include "iic.h"
#include "delay.h"

/*********************************************************************************************
* �궨��
*********************************************************************************************/
#define I2C_GPIO                GPIOB //GPIOB  ���ظ� GPIOD
#define I2C_CLK                 RCC_APB2Periph_GPIOB  //RCC_APB2Periph_GPIOD  //RCC_AHB1Periph_GPIOB  ���ظ�
#define PIN_SCL                 GPIO_Pin_9  //���ظ� GPIO_Pin_6
#define PIN_SDA                 GPIO_Pin_8  //���ظ� GPIO_Pin_7

#define SDA_R                   GPIO_ReadInputDataBit(I2C_GPIO,PIN_SDA) //���ظ�

/*********************************************************************************************
* ���ƣ�iic_init()
* ���ܣ�I2C��ʼ������
* ��������
* ���أ���
* �޸ģ�
* ע�ͣ�
*********************************************************************************************/
//void iic_init(void)
//{
//  GPIO_InitTypeDef  GPIO_InitStructure;
//  //RCC_AHB1PeriphClockCmd(I2C_CLK, ENABLE);
//  RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );
//	
//  GPIO_InitStructure.GPIO_Pin = PIN_SCL | PIN_SDA;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ; //GPIO_Mode_OUT;  //�������
//  //GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; //GPIO_Speed_2MHz;
//	GPIO_Init(I2C_GPIO, &GPIO_InitStructure);
//	
//  GPIO_SetBits(GPIOB,PIN_SCL | PIN_SDA);//GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
//  
//    
//  
//}
void iic_init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  //RCC_AHB1PeriphClockCmd(I2C_CLK, ENABLE);
  RCC_APB2PeriphClockCmd(	I2C_CLK, ENABLE );
	
  GPIO_InitStructure.GPIO_Pin = PIN_SCL | PIN_SDA;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ; //GPIO_Mode_OUT;  //�������
  //GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; //GPIO_Speed_2MHz;
	GPIO_Init(I2C_GPIO, &GPIO_InitStructure);
	
  GPIO_SetBits(I2C_GPIO,PIN_SCL | PIN_SDA);//GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  
    
  
}
/*********************************************************************************************
* ���ƣ�sda_out()
* ���ܣ�����SDAΪ���
* ��������
* ���أ���
* �޸ģ�
* ע�ͣ�
*********************************************************************************************/
void sda_out(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin = PIN_SDA;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;//GPIO_Mode_OUT;
 // GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	
	GPIO_Init(I2C_GPIO, &GPIO_InitStructure);
  //GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_SetBits(I2C_GPIO,PIN_SDA);
    
}

/*********************************************************************************************
* ���ƣ�sda_in()
* ���ܣ�����SDAΪ����
* ��������
* ���أ���
* �޸ģ�
* ע�ͣ�
*********************************************************************************************/
void sda_in(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin = PIN_SDA;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//GPIO_Mode_IN;
  //GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(I2C_GPIO, &GPIO_InitStructure); 
  //GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_SetBits(I2C_GPIO,PIN_SDA);
   
}

/*********************************************************************************************
* ���ƣ�iic_start()
* ���ܣ�I2C��ʼ�ź�
* ��������
* ���أ���
* �޸ģ�
* ע�ͣ�
*********************************************************************************************/
void iic_start(void)
{
  sda_out();
  GPIO_SetBits(I2C_GPIO,PIN_SDA);                               //����������
  GPIO_SetBits(I2C_GPIO,PIN_SCL);                               //����ʱ����
  delay_us(5);                                                  //��ʱ
  GPIO_ResetBits(I2C_GPIO,PIN_SDA);                             //�����½���
  delay_us(5);                                                  //��ʱ
  GPIO_ResetBits(I2C_GPIO,PIN_SCL);                             //����ʱ����
}

/*********************************************************************************************
* ���ƣ�iic_stop()
* ���ܣ�I2Cֹͣ�ź�
* ��������
* ���أ���
* �޸ģ�
* ע�ͣ�
*********************************************************************************************/
void iic_stop(void)
{
  sda_out();
  GPIO_ResetBits(I2C_GPIO,PIN_SDA);                             //����������
  GPIO_SetBits(I2C_GPIO,PIN_SCL);                               //����ʱ����
  delay_us(5);                                                  //��ʱ5us
  GPIO_SetBits(I2C_GPIO,PIN_SDA);                               //����������
  delay_us(5);                                                  //��ʱ5us
}

/*********************************************************************************************
* ���ƣ�iic_send_ack()
* ���ܣ�I2C����Ӧ��
* ������ack -- Ӧ���ź�
* ���أ���
* �޸ģ�
* ע�ͣ�
*********************************************************************************************/
void iic_send_ack(int ack)
{
  sda_out();
  if(ack)
    GPIO_SetBits(I2C_GPIO,PIN_SDA);                             //дӦ���ź�
  else
    GPIO_ResetBits(I2C_GPIO,PIN_SCL); 
  GPIO_SetBits(I2C_GPIO,PIN_SCL);                               //����ʱ����
  delay_us(5);                                                  //��ʱ
  GPIO_ResetBits(I2C_GPIO,PIN_SCL);                             //����ʱ����
  delay_us(5);                                                  //��ʱ
}

/*********************************************************************************************
* ���ƣ�iic_recv_ack()
* ���ܣ�I2C����Ӧ��
* ��������
* ���أ���
* �޸ģ�
* ע�ͣ�
*********************************************************************************************/
int iic_recv_ack(void)
{
  int CY = 0;
  sda_in();
  GPIO_SetBits(I2C_GPIO,PIN_SCL);                               //����ʱ����
  delay_us(5);                                                  //��ʱ
  CY = SDA_R;                                                   //��Ӧ���ź�
  GPIO_ResetBits(I2C_GPIO,PIN_SDA);                             //����ʱ����
  delay_us(5);                                                  //��ʱ
  return CY;
}

/*********************************************************************************************
* ���ƣ�iic_write_byte()
* ���ܣ�I2Cдһ���ֽ����ݣ�����ACK����NACK���Ӹߵ��ͣ����η���
* ������data -- Ҫд������
* ���أ���
* �޸ģ�
* ע�ͣ�
*********************************************************************************************/
unsigned char iic_write_byte(unsigned char data)
{
  unsigned char i;
  sda_out();
  GPIO_ResetBits(I2C_GPIO,PIN_SCL);                             //����ʱ����
  for(i = 0;i < 8;i++){                                         
    if(data & 0x80){                                            //�ж��������λ�Ƿ�Ϊ1
      GPIO_SetBits(I2C_GPIO,PIN_SDA);  	                                                
    }
    else
      GPIO_ResetBits(I2C_GPIO,PIN_SDA); 
    delay_us(5);                                                //��ʱ5us
    GPIO_SetBits(I2C_GPIO,PIN_SCL); 	                        //���SDA�ȶ�������SCL���������أ��ӻ���⵽��������ݲ���
    delay_us(5);                                                //��ʱ5us
    GPIO_ResetBits(I2C_GPIO,PIN_SCL);                           //����ʱ����
    delay_us(5);                                                //��ʱ5us
    data <<= 1;                                                 //��������һλ
  } 
  delay_us(5);                                                  //��ʱ2us
  sda_in();
  GPIO_SetBits(I2C_GPIO,PIN_SDA);                               //����������
  GPIO_SetBits(I2C_GPIO,PIN_SCL);                               //����ʱ����
  delay_us(5);                                                  //��ʱ2us���ȴ��ӻ�Ӧ��
  if(SDA_R){			                                //SDAΪ�ߣ��յ�NACK
    return 1;	
  }else{ 				                        //SDAΪ�ͣ��յ�ACK
    GPIO_ResetBits(I2C_GPIO,PIN_SCL);                           //�ͷ�����                  
    delay_us(5);                                                //��ʱ2us���ȴ��ӻ�Ӧ��
    return 0;
  }
}

/*********************************************************************************************
* ���ƣ�iic_read_byte()
* ���ܣ�I2Cдһ���ֽ����ݣ�����ACK����NACK���Ӹߵ��ͣ����η���
* ������data -- Ҫд������
* ���أ���
* �޸ģ�
* ע�ͣ�
*********************************************************************************************/
unsigned char iic_read_byte(unsigned char ack)
{
  unsigned char i,data = 0;
  sda_in();
  GPIO_ResetBits(I2C_GPIO,PIN_SCL); 
  GPIO_SetBits(I2C_GPIO,PIN_SDA);  			        //�ͷ�����	
  for(i = 0;i < 8;i++){
    GPIO_SetBits(I2C_GPIO,PIN_SCL);  		                //����������
    delay_us(30);	                                        //��ʱ�ȴ��ź��ȶ�
    data <<= 1;	
    if(SDA_R){ 		                                        //������ȡ����
      data |= 0x01;
    }else{
      data &= 0xfe;
    }
    delay_us(10);
    GPIO_ResetBits(I2C_GPIO,PIN_SCL);    		        //�½��أ��ӻ�������һλֵ
    delay_us(20);
  }
  sda_out();
  if(ack)
    GPIO_SetBits(I2C_GPIO,PIN_SDA);	                        //Ӧ��״̬
  else
    GPIO_ResetBits(I2C_GPIO,PIN_SDA);  
  delay_us(10);
  GPIO_SetBits(I2C_GPIO,PIN_SCL);                        
  delay_us(50);          
  GPIO_ResetBits(I2C_GPIO,PIN_SCL); 
  delay_us(50);
  return data;
}

//////////////////BMP280//////////////////////////////////////////////////////////////////////////////////////
//void IIC_Init(void)
//{					     
//	GPIO_InitTypeDef GPIO_InitStructure;
//	//RCC->APB2ENR|=1<<4;//��ʹ������IO PORTCʱ�� 
//	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA, ENABLE );	
//	   
//	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4|GPIO_Pin_5;
//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP ;                            //�������
//	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
//	GPIO_Init(GPIOA,&GPIO_InitStructure);
// 
//	IIC_SCL=1;
//	IIC_SDA=1;

//}
//����IIC��ʼ�ź�
void IIC_Start(void)
{
	sda_out();                                                                 //sda�����
	IIC_SDA=1;	  	  
	IIC_SCL=1;
	delay_us(4);
 	IIC_SDA=0;                                                                 //START:when CLK is high,DATA change form high to low 
	delay_us(4);
	IIC_SCL=0;                                                                 //ǯסI2C���ߣ�׼�����ͻ�������� 
}	  
//����IICֹͣ�ź�
void IIC_Stop(void)
{
	sda_out();                                                                 //sda�����
	IIC_SCL=0;
	IIC_SDA=0;                                                                 //STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	IIC_SCL=1; 
	IIC_SDA=1;                                                                 //����I2C���߽����ź�
	delay_us(4);							   	
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	sda_in();                                                                  //SDA����Ϊ����  
	IIC_SDA=1;delay_us(1);	   
	IIC_SCL=1;delay_us(1);	 
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL=0;                                                                 //ʱ�����0 	   
	return 0;  
} 
//����ACKӦ��
void IIC_Ack(void)
{
	IIC_SCL=0;
	sda_out();
	IIC_SDA=0;
	delay_us(2);
	IIC_SCL=1;
	delay_us(2);
	IIC_SCL=0;
}
//������ACKӦ��		    
void IIC_NAck(void)
{
	IIC_SCL=0;
	sda_out();
	IIC_SDA=1;
	delay_us(2);
	IIC_SCL=1;
	delay_us(2);
	IIC_SCL=0;
}					 				     
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	sda_out(); 	    
    IIC_SCL=0;                                                                 //����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {              
        IIC_SDA=(txd&0x80)>>7;
        txd<<=1; 	  
		delay_us(2);                                                           //��TEA5767��������ʱ���Ǳ����
		IIC_SCL=1;
		delay_us(2); 
		IIC_SCL=0;	
		delay_us(2);
    }	 
} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	sda_in();                                                                  //SDA����Ϊ����
    for(i=0;i<8;i++ )
	{
        IIC_SCL=0; 
        delay_us(2);
		IIC_SCL=1;
        receive<<=1;
        if(READ_SDA)receive++;   
		delay_us(1); 
    }					 
    if (!ack)
        IIC_NAck();                                                            //����nACK
    else
        IIC_Ack();                                                             //����ACK   
    return receive;
}

//��ָ����ַ����һ������
//ReadAddr:��ʼ�����ĵ�ַ  
//����ֵ  :����������
u8 iicDevReadByte(u8 devaddr,u8 addr)
{				  
	u8 temp=0;		  	    																 
	iic_start();  
	IIC_Send_Byte(devaddr);                                                    //��������д���� 	   
	IIC_Wait_Ack(); 
	IIC_Send_Byte(addr);                                                       //���͵͵�ַ
	IIC_Wait_Ack();	

	iic_start();  	 	   
	IIC_Send_Byte(devaddr|1);                                                  //��������������			   
	IIC_Wait_Ack();	 
	temp=IIC_Read_Byte(0);			   
	IIC_Stop();                                                                //����һ��ֹͣ����	    
	return temp;
}

//����������ֽ�
//addr:��ʼ��ַ
//rbuf:�����ݻ���
//len:���ݳ���
void iicDevRead(u8 devaddr,u8 addr,u8 len,u8 *rbuf)
{
	int i=0;
	IIC_Start();  
	IIC_Send_Byte(devaddr);  
	IIC_Wait_Ack();	
	IIC_Send_Byte(addr);                                                       //��ַ����  
	IIC_Wait_Ack();	

	IIC_Start();  	
	IIC_Send_Byte(devaddr|1);  	
	IIC_Wait_Ack();	
	for(i=0; i<len; i++)
	{
		if(i==len-1)
		{
			rbuf[i]=IIC_Read_Byte(0);                                          //���һ���ֽڲ�Ӧ��
		}
		else
			rbuf[i]=IIC_Read_Byte(1);
	}
	IIC_Stop( );	
}

//��ָ����ַд��һ������
//WriteAddr :д�����ݵ�Ŀ�ĵ�ַ    
//DataToWrite:Ҫд�������
void iicDevWriteByte(u8 devaddr,u8 addr,u8 data)
{				   	  	    																 
	IIC_Start();  
	IIC_Send_Byte(devaddr);                                                    //��������д���� 	 
	IIC_Wait_Ack();	   
	IIC_Send_Byte(addr);                                                       //���͵͵�ַ
	IIC_Wait_Ack(); 	 										  		   
	IIC_Send_Byte(data);                                                       //�����ֽ�							   
	IIC_Wait_Ack();  		    	   
	IIC_Stop();		                                                           //����һ��ֹͣ���� 	 
}

//����д����ֽ�
//addr:��ʼ��ַ
//wbuf:д���ݻ���
//len:���ݵĳ���
void iicDevWrite(u8 devaddr,u8 addr,u8 len,u8 *wbuf)
{
	int i=0;
	IIC_Start();  
	IIC_Send_Byte(devaddr);  	
	IIC_Wait_Ack();	
	IIC_Send_Byte(addr);  //��ַ����
	IIC_Wait_Ack();	
	for(i=0; i<len; i++)
	{
		IIC_Send_Byte(wbuf[i]);  
		IIC_Wait_Ack();		
	}
	IIC_Stop( );	
}
