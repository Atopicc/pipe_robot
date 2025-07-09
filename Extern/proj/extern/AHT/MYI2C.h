#ifndef __MYI2C_H
#define __MYI2C_H

#include "debug.h"
//DA 7 CL 6
#define  IIC_SDA_H  GPIO_SetBits(GPIOB,GPIO_Pin_7)    //����SDA�ӿڸߵ�ƽ
#define  IIC_SDA_L  GPIO_ResetBits(GPIOB,GPIO_Pin_7)  //����SDA�ӿڵ͵�ƽ

#define  IIC_SCL_H  GPIO_SetBits(GPIOB,GPIO_Pin_6)    //����SCL�ӿڸߵ�ƽ
#define  IIC_SCL_L  GPIO_ResetBits(GPIOB,GPIO_Pin_6)  //����SCL�ӿڵ͵�ƽ

#define  I2C_SDA_READ()  GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7)  //��SDA����״̬

void IIC_Init(void);         //IIC��ʼ������
void IIC_Idle_State(void);   //IIC����״̬
void IIC_Start(void);        //IIC��ʼ�źź���
void IIC_Stop(void);         //IICֹͣ�źź���
void IIC_SendByte(u8 data);  //IIC����һ���ֽ�
u8   IIC_ReadByte(unsigned char ack);     //IIC��ȡһ���ֽ�
u8   IIC_WaitAck(void);      //�ȴ���Ӧ�źţ�ACK����NACK��
void IIC_ACK(void);          //IIC����ACK�ź�
void IIC_NACK(void);         //IIC����NACK�ź�
uint8_t Soft_I2C_Read(uint8_t dev_addr, uint8_t reg_addr, uint8_t len, unsigned char *data_buf);
uint8_t Soft_I2C_Write(uint8_t dev_addr, uint8_t reg_addr, uint8_t len, unsigned char *data_buf);
void IIC_NAck();
void IIC_Ack();

#endif