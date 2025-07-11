#include "debug.h"                  // Device header
#include "PStwo.h"

#define DELAY_TIME  Delay_Us(5); 

int PS2_LX,PS2_LY,PS2_RX,PS2_RY,PS2_KEY=0; //PS2相关变量
u8 PS2_ON_Flag = 0;

u16 Handkey;	// 按键值读取，零时存储。
u8 Comd[2]={0x01,0x42};	//开始命令。请求数据
u8 Data[9]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}; //数据存储数组
u16 MASK[]={
    PSB_SELECT,
    PSB_L3,
    PSB_R3 ,
    PSB_START,
    PSB_PAD_UP,
    PSB_PAD_RIGHT,
    PSB_PAD_DOWN,
    PSB_PAD_LEFT,
    PSB_L2,
    PSB_R2,
    PSB_L1,
    PSB_R1 ,
    PSB_GREEN,
    PSB_RED,
    PSB_BLUE,
    PSB_PINK
	};	//按键值与按键名

// 全局变量用于记录前一次按键状态
uint8_t prevKeyState = 0;

// void PS2_Read(void)
// {
// 	PS2_LX=PS2_AnologData(PSS_LX);    //PS2数据采集    
// 	PS2_LY=PS2_AnologData(PSS_LY);
// 	PS2_RX=PS2_AnologData(PSS_RX);
// 	PS2_RY=PS2_AnologData(PSS_RY);
// 	PS2_KEY=PS2_DataKey();	
// }

void PS2_Read(void)
{
	PS2_LX=PS2_AnologData(PSS_LX);    //PS2数据采集    
	PS2_LY=PS2_AnologData(PSS_LY);
	PS2_RX=PS2_AnologData(PSS_RX);
	PS2_RY=PS2_AnologData(PSS_RY);

	uint8_t currentKey = PS2_DataKey();
	// 只有当按键从无到有时才更新键值
    if(currentKey != 0 && prevKeyState == 0)
    {
        PS2_KEY = currentKey;
    }
	else
    {
        PS2_KEY = 0;  
    }
    
    // 更新前一次按键状态
    prevKeyState = (currentKey != 0);
}

// void PS2_Init(void)
// {
// 	GPIO_InitTypeDef GPIO_InitStructure;
// 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //使能端口时钟
// 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;				//端口配置 PB15
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;			//上拉输入
// 	GPIO_Init(GPIOB, &GPIO_InitStructure);					//根据设定参数初始化GPIO	 	

// 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14|GPIO_Pin_12|GPIO_Pin_13;	//端口配置 PB4 PB5
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		//推挽输出
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//50M
// 	GPIO_Init(GPIOB, &GPIO_InitStructure);					//根据设定参数初始化GPIO		
// }

void PS2_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //使能端口时钟
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;				//端口配置 PB15
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;			//上拉输入
	GPIO_Init(GPIOB, &GPIO_InitStructure);					//根据设定参数初始化GPIO	 	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15|GPIO_Pin_12|GPIO_Pin_13;	//端口配置 PB4 PB5
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//50M
	GPIO_Init(GPIOB, &GPIO_InitStructure);					//根据设定参数初始化GPIO		
}

//向手柄发送命令
void PS2_Cmd(u8 CMD)
{
	volatile u16 ref=0x01;
	Data[1] = 0;
	for(ref=0x01;ref<0x0100;ref<<=1)
	{
		if(ref&CMD)
		{
			DO_H;                   //输出一位控制位
		}
		else DO_L;

		CLK_H;                        //时钟拉高
		DELAY_TIME;
		CLK_L;
		DELAY_TIME;
		CLK_H;
		if(DI)
			Data[1] = ref|Data[1];
	}
	Delay_Us(16);
}
//判断是否为红灯模式,0x41=模拟绿灯，0x73=模拟红灯
//返回值；0，红灯模式
//		  其他，其他模式
u8 PS2_RedLight(void)
{
	CS_L;
	PS2_Cmd(Comd[0]);  //开始命令
	PS2_Cmd(Comd[1]);  //请求数据
	CS_H;
	if( Data[1] == 0X73)   return 0 ;
	else return 1;

}
//读取手柄数据
void PS2_ReadData(void)
{
	volatile u8 byte=0;
	volatile u16 ref=0x01;
	CS_L;
	PS2_Cmd(Comd[0]);  //开始命令
	PS2_Cmd(Comd[1]);  //请求数据
	for(byte=2;byte<9;byte++)          //开始接受数据
	{
		for(ref=0x01;ref<0x100;ref<<=1)
		{
			CLK_H;
			DELAY_TIME;
			CLK_L;
			DELAY_TIME;
			CLK_H;
			if(DI)
			Data[byte] = ref|Data[byte];
		}
        Delay_Us(16);
	}
	CS_H;
}

//对读出来的PS2的数据进行处理,只处理按键部分  
//只有一个按键按下时按下为0， 未按下为1
u8 PS2_DataKey()
{
	u8 index;

	PS2_ClearData();
	PS2_ReadData();

	Handkey=(Data[4]<<8)|Data[3];     //这是16个按键  按下为0， 未按下为1
	for(index=0;index<16;index++)
	{	    
		if((Handkey&(1<<(MASK[index]-1)))==0)
		return index+1;
	}
	return 0;          //没有任何按键按下
}

//得到一个摇杆的模拟量	 范围0~256
u8 PS2_AnologData(u8 button)
{
	return Data[button];
}

//清除数据缓冲区
void PS2_ClearData()
{
	u8 a;
	for(a=0;a<9;a++)
		Data[a]=0x00;
}
/******************************************************
Function:    void PS2_Vibration(u8 motor1, u8 motor2)
Description: 手柄震动函数，
Calls:		 void PS2_Cmd(u8 CMD);
Input: motor1:右侧小震动电机 0x00关，其他开
	   motor2:左侧大震动电机 0x40~0xFF 电机开，值越大 震动越大
******************************************************/
void PS2_Vibration(u8 motor1, u8 motor2)
{
	CS_L;
	Delay_Us(16);
    PS2_Cmd(0x01);  //开始命令
	PS2_Cmd(0x42);  //请求数据
	PS2_Cmd(0X00);
	PS2_Cmd(motor1);
	PS2_Cmd(motor2);
	PS2_Cmd(0X00);
	PS2_Cmd(0X00);
	PS2_Cmd(0X00);
	PS2_Cmd(0X00);
	CS_H;
	Delay_Us(16);
}
//short poll
void PS2_ShortPoll(void)
{
	CS_L;
	Delay_Us(16);
	PS2_Cmd(0x01);  
	PS2_Cmd(0x42);  
	PS2_Cmd(0X00);
	PS2_Cmd(0x00);
	PS2_Cmd(0x00);
	CS_H;
	Delay_Us(16);	
}
//进入配置
void PS2_EnterConfing(void)
{
    CS_L;
	Delay_Us(16);
	PS2_Cmd(0x01);  
	PS2_Cmd(0x43);  
	PS2_Cmd(0X00);
	PS2_Cmd(0x01);
	PS2_Cmd(0x00);
	PS2_Cmd(0X00);
	PS2_Cmd(0X00);
	PS2_Cmd(0X00);
	PS2_Cmd(0X00);
	CS_H;
	Delay_Us(16);
}
//发送模式设置
void PS2_TurnOnAnalogMode(void)
{
	CS_L;
	PS2_Cmd(0x01);  
	PS2_Cmd(0x44);  
	PS2_Cmd(0X00);
	PS2_Cmd(0x01); //analog=0x01;digital=0x00  软件设置发送模式
	PS2_Cmd(0x03); //Ox03锁存设置，即不可通过按键“MODE”设置模式。
				   //0xEE不锁存软件设置，可通过按键“MODE”设置模式。
	PS2_Cmd(0X00);
	PS2_Cmd(0X00);
	PS2_Cmd(0X00);
	PS2_Cmd(0X00);
	CS_H;
	Delay_Us(16);
}
//振动设置
void PS2_VibrationMode(void)
{
	CS_L;
	Delay_Us(16);
	PS2_Cmd(0x01);  
	PS2_Cmd(0x4D);  
	PS2_Cmd(0X00);
	PS2_Cmd(0x00);
	PS2_Cmd(0X01);
	CS_H;
	Delay_Us(16);	
}
//完成并保存配置
void PS2_ExitConfing(void)
{
    CS_L;
	Delay_Us(16);
	PS2_Cmd(0x01);  
	PS2_Cmd(0x43);  
	PS2_Cmd(0X00);
	PS2_Cmd(0x00);
	PS2_Cmd(0x5A);
	PS2_Cmd(0x5A);
	PS2_Cmd(0x5A);
	PS2_Cmd(0x5A);
	PS2_Cmd(0x5A);
	CS_H;
	Delay_Us(16);
}
//手柄配置初始化
void PS2_SetInit(void)
{
	PS2_ShortPoll();
	PS2_ShortPoll();
	PS2_ShortPoll();
	PS2_EnterConfing();		//进入配置模式
	PS2_TurnOnAnalogMode();	//“红绿灯”配置模式，并选择是否保存
	PS2_VibrationMode();	//开启震动模式
	PS2_ExitConfing();		//完成并保存配置
}

