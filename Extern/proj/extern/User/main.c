#include "debug.h"
#include "string.h"
#include "PStwo.h"
#include "AHTD.h"
#include "comm_protocol.h"
#include "usart.h"
#include "Motor.h"
#include "led.h"
#include "stdlib.h"
#include "timer.h"

// 初始化通信处理器
volatile CommHandler comm_handler = {
    .huart_master = USART1,  // 连接主控板的UART实例
    .rx_index = 0};

uint8_t Temp = 20;
uint8_t Humi = 20;
uint16_t dis_x = 1;
uint16_t dis_y = 1;
uint16_t dis_z = 1;

uint8_t flag = 0;
uint8_t trans_flag = 0;
uint8_t motor_flag = 0;

typedef union{
	char payload[6];
	struct{
		uint16_t X;
		uint16_t Y;
		uint16_t Z;
	};
} IMUData_t;

IMUData_t imudata = {
	0x01
};

void TIM1_UP_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void USART1_IRQHandler (void) __attribute__ ((interrupt ("WCH-Interrupt-fast")));

void receive_handler(void);
void transmit_handler(void);



int main(void)
{
	SystemCoreClockUpdate();
	Delay_Init();
	LED_Init();
	PS2_Init();
	PS2_SetInit();
	// DI2C_Init();
	mo_init();
	

	USART1_Init(115200);
	UART4_Init(115200);

	Timer1_Init();
	USART1_Printf ("SystemClk:%d\r\n", SystemCoreClock);
    USART1_Printf ("ChipID:%08x\r\n", DBGMCU_GetCHIPID());
	while(1)
	{
		PS2_Read();
		imudata.X++;
		// USART1_Printf("LX:%d LY:%d\r\nRX:%d RY:%d\r\nkry:%d\r\n\r\n\r\n",PS2_LX,PS2_LY,PS2_RX,PS2_RY,PS2_KEY);
		receive_handler();
		transmit_handler();

		Delay_Ms(100);
		if(PS2_KEY == 13)
		{
			motor_flag ^= 1;
			Motor_Control(motor_flag);
		}
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
			comm_handler.rx_buffer[comm_handler.rx_index++] = '\0';
        }

        if (is_recieving)
		{
			comm_handler.rx_buffer[comm_handler.rx_index++] = data;
			
		}
            

        // 清除中断标志
        USART_ClearITPendingBit (USART1, USART_IT_RXNE);
    }
}

void UART4_IRQHandler (void)
{
	if (USART_GetITStatus (UART4, USART_IT_RXNE) != RESET) {
        // 清除中断标志
        USART_ClearITPendingBit (UART4, USART_IT_RXNE);
    }
}

void receive_handler(void)
{
	if (comm_handler.is_finished) {
        comm_handler.is_finished = 0;
        ParseCommunicationFrame((CommHandler*)&comm_handler);
    }
}

void transmit_handler(void)
{
	// PS2_Read();
	char p[12];
	char t[12];		//温湿度
	char i[12];		//imu
	memset(p,0x00,sizeof(p));
	memset(t,0x00,sizeof(t));
	memset(i,0x00,sizeof(i));


	// 拓展板发给主控

	//前进
	if(PS2_LY < 30)
	{
		p[0] = 0xAA;p[1] = 0xD1;p[2] = 0xC3;
		p[3] = 0x06;
		p[4] = 0x01;p[5] = 0x00;p[6] = 0x00;
		p[7] = 0x00;p[8] = 0x00;p[9] = 0x00;
		p[10] = 0xFF;
		p[11] = '\0';
		USART_SendString_Len(p,11);
		Delay_Ms(50);
	}
	//后退
	else if(PS2_LY > 220)
	{
		p[0] = 0xAA;p[1] = 0xD1;p[2] = 0xC3;
		p[3] = 0x06;
		p[4] = 0x00;p[5] = 0x01;p[6] = 0x00;
		p[7] = 0x00;p[8] = 0x00;p[9] = 0x00;
		p[10] = 0xFF;
		p[11] = '\0';
		USART_SendString_Len(p,11);
		Delay_Ms(50);
	}
	//前展开
	if(PS2_RY < 30)
	{
		p[0] = 0xAA;p[1] = 0xD1;p[2] = 0xC3;
		p[3] = 0x06;
		p[4] = 0x00;p[5] = 0x00;p[6] = 0x01;
		p[7] = 0x00;p[8] = 0x00;p[9] = 0x00;
		p[10] = 0xFF;
		p[11] = '\0';
		USART_SendString_Len(p,11);
		Delay_Ms(50);
	}
	//前缩起
	else if(PS2_RY > 220)
	{
		p[0] = 0xAA;p[1] = 0xD1;p[2] = 0xC3;
		p[3] = 0x06;
		p[4] = 0x00;p[5] = 0x00;p[6] = 0x00;
		p[7] = 0x01;p[8] = 0x00;p[9] = 0x00;
		p[10] = 0xFF;
		p[11] = '\0';
		USART_SendString_Len(p,11);
		Delay_Ms(50);
	}
	//后展开
	if(PS2_RX < 30)
	{
		p[0] = 0xAA;p[1] = 0xD1;p[2] = 0xC3;
		p[3] = 0x06;
		p[4] = 0x00;p[5] = 0x00;p[6] = 0x00;
		p[7] = 0x00;p[8] = 0x01;p[9] = 0x00;
		p[10] = 0xFF;
		p[11] = '\0';
		USART_SendString_Len(p,11);
		Delay_Ms(50);
	}
	//后缩起
	else if(PS2_RX > 220)
	{
		p[0] = 0xAA;p[1] = 0xD1;p[2] = 0xC3;
		p[3] = 0x06;
		p[4] = 0x00;p[5] = 0x00;p[6] = 0x00;
		p[7] = 0x00;p[8] = 0x00;p[9] = 0x01;
		p[10] = 0xFF;
		p[11] = '\0';
		USART_SendString_Len(p,11);
		Delay_Ms(50);
	}
	//停止

	if(PS2_KEY == 11)
	{
    	p[0] = 0xAA; p[1] = 0xD1; p[2] = 0xCC;
    	p[3] = 0x01;
    	p[4] = 0x01;  // 切换状态
    	p[5] = 0xFF;
    	p[6] = '\0';
		USART_SendString_Len(p,6);
		Delay_Ms(50);
	}
	//模式切换
	else if(PS2_KEY == 1)
	{
		static int mode_state = 0;  // 静态变量，保持上次的状态

		p[0] = 0xAA; p[1] = 0xD1; p[2] = 0xCE;
    	p[3] = 0x01;
    	p[4] = (mode_state^=1) ? 0x00 : 0x01;  // 切换状态0x01 手动，0x02 自动
    	p[5] = 0xFF;
    	p[6] = '\0';
		USART_SendString_Len(p,6);
		Delay_Ms(50);
	}

	//拓展板发给ESP32

	//拍照 0xC4
	if(PS2_KEY == 10)
	{
		p[0] = 0xAA; p[1] = 0xD2; p[2] = 0xC4;
    	p[3] = 0x01;
		p[4] = 0x01;
    	p[5] = 0xFF;
    	p[6] = '\0';
		USART_SendString_Len(p,6);
		Delay_Ms(50);
	}
	//灯光 0xC7
	if(PS2_KEY == 12)
	{
		static int led_state = 0;

		p[0] = 0xAA; p[1] = 0xD2; p[2] = 0xC7;
    	p[3] = 0x01;
		p[4] = (led_state^=1) ? 0x00 : 0x01;	//0x01开灯，0x02关灯
    	p[5] = 0xFF;
    	p[6] = '\0';
		USART_SendString_Len(p,6);
		Delay_Ms(50);
	}

	if(flag)
	{
		flag = 0;
		if(trans_flag)
		{
			//温湿度
			t[0] = 0xAA; t[1] = 0xD2; t[2] = 0xC5;
			t[3] = 0x02;
			t[4] = Temp; t[5] = Humi;
			t[6] = 0xFF;
			t[7] = '\0';
			USART_SendString_Len(t,7);
		}
		
		else {
			//imu 0xC6
			i[0] = 0xAA; i[1] = 0xD2; i[2] = 0xC6;
			i[3] = 0x06;
			i[4] = imudata.payload[0]; i[5] = imudata.payload[1]; 
			i[6] = imudata.payload[2]; i[7] = imudata.payload[3]; 
			i[8] = imudata.payload[4]; i[9] = imudata.payload[5];
			i[10] = 0xFF;
			i[11] = '\0';
			USART_SendString_Len(i,11);
		}
	}
}


// 定时器1中断服务函数

void TIM1_UP_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)
    {
        flag = 1;
		trans_flag = !trans_flag;
		imudata.X ++;
		Humi++;
		Temp++;
    }
	TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
}