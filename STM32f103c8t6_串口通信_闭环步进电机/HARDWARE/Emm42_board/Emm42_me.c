#include "Emm42_me.h"

uint8_t cmd[10] = {0}; uint16_t i = 0;



//���Ʊջ������ʹ��״̬
void Motor_Enabled(void)
{
	cmd[0] = 0x01;	/* ��ַ */
	cmd[1] = 0xF3;	/* ������ */
	cmd[2] = 0x00;	/* ����01 F3 00 6B���Կ��Ʊջ�������ڲ�ʹ��״̬������01 F3 01 6B���Կ��Ʊջ��������ʹ��״̬��*/
	cmd[3] = 0x6B;	/* �̶�У���ֽ� */
	for(i=0; i < 4; i++) { usartSend(cmd[i]); }									/* �������� */
	rxReceiveCount = 0; while(rxFrameFlag == 0);								/* �ȴ����շ������� */
	rxFrameFlag = 0;
}

//���Ʊջ����������ת�����ٶ�ģʽ����
void Motor_speed(void)
{
		cmd[0] = 0x01;	/* ��ַ */
		cmd[1] = 0xF6;	/* ������ */
		cmd[2] = 0x15;	/* ������ֽ� + �ٶȸ߰��ֽ� */
		cmd[3] = 0xFF;	/* �ٶ��ֽ�,( (uint16_t)(cmd[2] & 0x0F) << 8 | (uint16_t)cmd[3] )����ٶ� */
		cmd[4] = 0x00;	/* ���ٶ� */
		cmd[5] = 0x6B;;	/* �̶�У���ֽ� */
				
		for(i=0; i < 6; i++) 		/* �������� */
		{ 
			usartSend(cmd[i]); 
		}				
		rxReceiveCount = 0; 
		while(rxFrameFlag == 0); //�ȴ����շ������* Emm42_V4.0�ջ����յ�����󽫻᷵�����
		rxFrameFlag = 0;
}


//���Ʊջ��������˶��ĽǶȣ���λ��ģʽ����
void Motor_speed_pos(void)
{
		/**********************************************************
		***	�����������λ�ÿ��������ʽ��
			��ַ 0xFD  2�ֽڷ���+�ٶ�  ���ٶ�   3�ֽ�����   CRC
			[0]  [1]     [2]  [3]       [4]   [5] [6] [7]  [8]
		**********************************************************/	
		cmd[0] = 0x01;	/* ��ַ */
		cmd[1] = 0xFD;	/* ������ */
		cmd[2] = 0x14;	/* ������ֽ� + �ٶȸ߰��ֽ� */
		cmd[3] = 0xFF;	/* �ٶ��ֽ�,( (uint16_t)(cmd[2] & 0x0F) << 8 | (uint16_t)cmd[3] )����ٶ� */
		cmd[4] = 0x40;	/* ���ٶ� */
		cmd[5] = 0x00;	/* ���������ֽ� */
		cmd[6] = 0x0C;	/* ���������ֽ� */
		cmd[7] = 0x80;	/* ���������ֽ� */
		cmd[8] = 0x6B;;	/* �̶�У���ֽ� */
				
		for(i=0; i < 9; i++) 		/* �������� */
		{ 
			usartSend(cmd[i]); 
		}				
		rxReceiveCount = 0; 
		while(rxFrameFlag == 0); //�ȴ����շ������* Emm42_V4.0�ջ����յ�����󽫻᷵�����
		//1.������յ������Ǵ�������򷵻أ�01����ַ�� EE 6B��У���룩
		//2.������յ���������ȷ����򷵻أ�01����ַ�� 02 6B��У���룩
		//3.���λ�ÿ�������ִ����ɣ��򷵻أ�01����ַ�� 9F 6B��У���룩
		rxFrameFlag = 0;
}

//��ȡ���ʵʱλ��
float Emm42_MotorAngle(void)
{
	int32_t motorPosition;  float motorAngle;
	cmd[0] = 0x01;	/* ��ַ */
	cmd[1] = 0x36;	/* ������ */
	cmd[2] = 0x6B;	/* �̶�У���ֽ� */
	for(i=0; i < 3; i++) { usartSend(cmd[i]); }									/* �������� */
	rxReceiveCount = 0; while(rxFrameFlag == 0);								/* �ȴ����շ������� */
	if(rxBuffer[0] == cmd[0])		/* У���ַ */
	{
		motorPosition = (int32_t)rxBuffer[1] << 24 | (int32_t)rxBuffer[2] << 16 | (int32_t)rxBuffer[3] << 8 | (int32_t)rxBuffer[4];		/* ƴ�ӳɵ��λ�� */
		motorAngle = (float)( ( (int64_t)motorPosition * (int64_t)225) / (int64_t)4096 ) / (float)10.0;																/* ת���ɽǶȵ�λ */
	}
	rxFrameFlag = 0;
	return motorAngle;
}

//��ȡλ�����
float Emm42_MotorError(void)
{
	int16 posError; float angleError;
	cmd[0] = 0x01;	/* ��ַ */
	cmd[1] = 0x39;	/* ������ */
	cmd[2] = 0x6B;	/* �̶�У���ֽ� */
	for(i=0; i < 3; i++) { usartSend(cmd[i]); }									/* �������� */
	rxReceiveCount = 0; while(rxFrameFlag == 0);								/* �ȴ����շ������� */
	if(rxBuffer[0] == cmd[0])		/* У���ַ */
	{
		posError = (int32_t)rxBuffer[1] << 8 | (int32_t)rxBuffer[2] ;	/* ƴ�ӳɵ��λ�� */
		angleError = (float)( ( (int64_t)posError * (int64_t)225) / (int64_t)4096 ) / (float)10.0;																/* ת���ɽǶȵ�λ */
	}
	rxFrameFlag = 0;
	return angleError*1000;
}



//��ȡ����������
int32 Emm42_Pulse_count(void)
{
	int32 pulse_num;
	cmd[0] = 0x01;	/* ��ַ */
	cmd[1] = 0x33;	/* ������ */
	cmd[2] = 0x6B;	/* �̶�У���ֽ� */
	for(i=0; i < 3; i++) { usartSend(cmd[i]); }									/* �������� */
	rxReceiveCount = 0; while(rxFrameFlag == 0);								/* �ȴ����շ������� */
	if(rxBuffer[0] == cmd[0])		/* У���ַ */
	{
		pulse_num = (int32_t)rxBuffer[1] << 24 | (int32_t)rxBuffer[2] << 16 | (int32_t)rxBuffer[3] << 8 | (int32_t)rxBuffer[4];		/* ƴ�ӳɵ��λ�� */
	}
	rxFrameFlag = 0;
	return pulse_num;
}



