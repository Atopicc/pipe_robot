#ifndef __MYI2C_H
#define __MYI2C_H

#include "debug.h"
//DA 7 CL 6
#define  IIC_SDA_H  GPIO_SetBits(GPIOB,GPIO_Pin_7)    //配置SDA接口高电平
#define  IIC_SDA_L  GPIO_ResetBits(GPIOB,GPIO_Pin_7)  //配置SDA接口低电平

#define  IIC_SCL_H  GPIO_SetBits(GPIOB,GPIO_Pin_6)    //配置SCL接口高电平
#define  IIC_SCL_L  GPIO_ResetBits(GPIOB,GPIO_Pin_6)  //配置SCL接口低电平

#define  I2C_SDA_READ()  GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7)  //读SDA口线状态

void IIC_Init(void);         //IIC初始化函数
void IIC_Idle_State(void);   //IIC空闲状态
void IIC_Start(void);        //IIC开始信号函数
void IIC_Stop(void);         //IIC停止信号函数
void IIC_SendByte(u8 data);  //IIC发送一个字节
u8   IIC_ReadByte(unsigned char ack);     //IIC读取一个字节
u8   IIC_WaitAck(void);      //等待响应信号（ACK或者NACK）
void IIC_ACK(void);          //IIC发出ACK信号
void IIC_NACK(void);         //IIC发出NACK信号
uint8_t Soft_I2C_Read(uint8_t dev_addr, uint8_t reg_addr, uint8_t len, unsigned char *data_buf);
uint8_t Soft_I2C_Write(uint8_t dev_addr, uint8_t reg_addr, uint8_t len, unsigned char *data_buf);
void IIC_NAck();
void IIC_Ack();

#endif