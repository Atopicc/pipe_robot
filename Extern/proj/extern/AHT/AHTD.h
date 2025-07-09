#ifndef __AHDT_H
#define __AHDT_H

#include "debug.h"
#include "ch32v30x_gpio.h"

// Òý½Å¶¨Òå
#define I2C_SCL_PORT GPIOB
#define I2C_SDA_PORT GPIOB
#define I2C_SCL_PIN  GPIO_Pin_6
#define I2C_SDA_PIN  GPIO_Pin_7

void delay_us(uint32_t us);
void DI2C_Init(void);
void I2C_Start(void);
void I2C_Stop(void);
uint8_t I2C_Wait_Ack(void);
void I2C_Ack(void);
void I2C_NAck(void);
void I2C_Send_Byte(uint8_t data);
uint8_t I2C_Read_Byte(uint8_t ack);
uint8_t DAHT20_Init(void);
uint8_t AHT20_Read(float *humidity, float *temperature);
uint8_t AHT20_Read_Data(float *temperature, float *humidity);

#endif
