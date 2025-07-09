#include "debug.h"
#include "pwm.h"
#include "led.h"
#include "adc.h"
#include "motor.h"
#include "comm_protocol.h"
#include "usart.h"

// 初始化通信处理器
volatile CommHandler comm_handler = {
    .huart_cam = UART4,  // 连接CAM的UART实例
    .huart_ext = USART1,  // 连接扩展板的UART实例
    .rx_index = 0};

void USART1_IRQHandler (void) __attribute__ ((interrupt ("WCH-Interrupt-fast")));
void UART4_IRQHandler (void) __attribute__ ((interrupt ("WCH-Interrupt-fast")));
void checkbuf (void);
void SendSatus(void);

int main (void) {
    SystemCoreClockUpdate();
    Delay_Init();
    LED_Init();
    USART1_Init(115200);
    UART4_Init(115200);
    USART1_Printf("SystemClk:%d\r\n", SystemCoreClock);
    USART1_Printf("ChipID:%08x\r\n", DBGMCU_GetCHIPID());
    UART4_Printf("ChipID:%08x\r\n", DBGMCU_GetCHIPID());
    PWMOutputInit();
    ADCInit();
    MotorInit();
    Servo_Reset();
    
    while (1) {

        // setSpeed(1,100);

        if (comm_handler.is_finished) {
            comm_handler.is_finished = 0;

            // GPIO_ResetBits(GPIOB,GPIO_Pin_12);
            // USART1_Printf((char*)&comm_handler.rx_buffer); // 调试用
            // UART4_Printf("Recived");
            ParseCommunicationFrame((CommHandler*)&comm_handler);
        }

        // Delay_Ms (100);
    }
}

void USART1_IRQHandler (void) {
    static uint8_t is_recieving = 0;

    if (USART_GetITStatus (USART1, USART_IT_RXNE) != RESET) {
        uint8_t data = USART_ReceiveData (USART1);

        if (data == FRAME_HEADER) {
            is_recieving = 1;
            comm_handler.rx_index = 0;
        } else if (data == FRAME_TAIL) {
            is_recieving = 0;
            comm_handler.is_finished = 1;
            comm_handler.rx_buffer[comm_handler.rx_index++] = FRAME_TAIL;
            comm_handler.rx_buffer[comm_handler.rx_index++] = '\0';  // 调试用
        }

        if (is_recieving)
            comm_handler.rx_buffer[comm_handler.rx_index++] = data;

        // 清除中断标志
        USART_ClearITPendingBit (USART1, USART_IT_RXNE);
    }
}

void UART4_IRQHandler (void) {
    static uint8_t is_recieving = 0;

    if (USART_GetITStatus (UART4, USART_IT_RXNE) != RESET) {
        uint8_t data = USART_ReceiveData (UART4);

        if (data == FRAME_HEADER) {
            is_recieving = 1;
            comm_handler.rx_index = 0;
        } else if (data == FRAME_TAIL) {
            is_recieving = 0;
            comm_handler.is_finished = 1;
            comm_handler.rx_buffer[comm_handler.rx_index++] = FRAME_TAIL;
            comm_handler.rx_buffer[comm_handler.rx_index++] = '\0';  // 调试用
        }

        if (is_recieving)
            comm_handler.rx_buffer[comm_handler.rx_index++] = data;

        // 清除中断标志
        USART_ClearITPendingBit (UART4, USART_IT_RXNE);
    }
}

void SendSatus(void)
{
    unsigned char buff[20];
    char percent = voltage-12000;

    ADCTask();

    buff[0] = FRAME_HEADER;
    buff[1] = DEV_CAM;
    buff[2] = CMD_MA_BATTERY;
    buff[3] = 0x01;
    buff[4] = percent;
    buff[5] = 0xFF;
    UART4_SendString_Len((char*)buff,6);
}
