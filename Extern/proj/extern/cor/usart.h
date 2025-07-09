#ifndef __USART_H
#define __USART_H

#include "debug.h"
#include "stdarg.h"

void USART1_Init(uint32_t baudrate);
void UART4_Init(uint32_t baudrate);
void USART1_SendByte(uint8_t data);
void USART1_SendString(char *str);
void UART4_SendByte(uint8_t data);
void UART4_SendString(char *str);
void USART1_Printf(const char *format, ...);
void UART4_Printf(const char *format, ...);
void USART_SendString_Len(char *str, uint16_t len);

#endif
