#include "usart.h"

// ����1��ʼ��
void USART1_Init(uint32_t baudrate) {
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    USART_InitTypeDef USART_InitStructure = {0};
    NVIC_InitTypeDef NVIC_InitStructure = {0};

    // ʹ��ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);

    // ����USART1 Tx (PA9) ��Ϊ���츴�����
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // ����USART1 Rx (PA10) ��Ϊ��������
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // USART��������
    USART_InitStructure.USART_BaudRate = baudrate;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART1, &USART_InitStructure);

    // ʹ��USART1�����ж�
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

    // ����USART1�ж�
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    // ʹ��USART1
    USART_Cmd(USART1, ENABLE);
}

// ����4��ʼ��
void UART4_Init(uint32_t baudrate) {
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    USART_InitTypeDef USART_InitStructure = {0};
    NVIC_InitTypeDef NVIC_InitStructure = {0};

    // ʹ��ʱ��
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);

    // ʹ��AFIOʱ���Խ�����ӳ������
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

    GPIO_PinRemapConfig(GPIO_FullRemap_USART4, ENABLE);

    // ����UART4 Tx (PE0) ��Ϊ���츴�����
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOE, &GPIO_InitStructure);

    // ����UART4 Rx (PE1) ��Ϊ��������
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOE, &GPIO_InitStructure);

    // UART��������
    USART_InitStructure.USART_BaudRate = baudrate;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(UART4, &USART_InitStructure);

    // ʹ��UART4�����ж�
    USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);

    // ����UART4�ж�
    NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    // ʹ��UART4
    USART_Cmd(UART4, ENABLE);
}

// ����1����һ���ֽ�
void USART1_SendByte(uint8_t data) {
    USART_SendData(USART1, data);
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}

// ����1�����ַ���
void USART1_SendString(char *str) {
    while(*str) {
        USART1_SendByte(*str++);
    }
}

void USART1_SendString_Len(char *str, uint16_t len)
{
    int local_len = len;
    while(local_len--)
    {
        USART1_SendByte(*str++);
    }
}

// ����4����һ���ֽ�
void UART4_SendByte(uint8_t data) {
    USART_SendData(UART4, data);
    while(USART_GetFlagStatus(UART4, USART_FLAG_TXE) == RESET);
}

// ����4�����ַ���
void UART4_SendString(char *str) {
    while(*str) {
        UART4_SendByte(*str++);
    }
}

void UART4_SendString_Len(char *str, uint16_t len)
{
    int local_len = len;
    while(local_len--)
    {
        UART4_SendByte(*str++);
    }
}

// �����ĸ�ʽ�����ͺ���
void USART1_Printf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    char buffer[256];
    int len = vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    
    for(int i = 0; i < len; i++) {
        USART1_SendByte(buffer[i]);
    }
}

void UART4_Printf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    char buffer[256];
    int len = vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    
    for(int i = 0; i < len; i++) {
        UART4_SendByte(buffer[i]);
    }
}
