#include "MYI2C.h"

//初始化IIC
void IIC_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE );

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;//使用PA1和PA2作为模拟IIC引脚，PA1对应SDA，PA2对应SCL
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD ;   //开漏输出模式
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    IIC_Idle_State();
}

//IIC空闲状态
//当IIC总线的SDA和SCL两条信号线同时处于高电平时，规定为IIC总线的空闲状态
void IIC_Idle_State()
{
    IIC_SDA_H;
    IIC_SCL_H;

    Delay_Us(4);
}

//IIC开始信号
//当IIC SCL线处于高电平时，SDA线由高电平向低电平跳变，为IIC开始信号，配置开始信号前必须保证IIC总线处于空闲状态
void IIC_Start()
{
    IIC_SDA_H;
    IIC_SCL_H;

    Delay_Us(4);

    IIC_SDA_L;
    Delay_Us(4);
    IIC_SCL_L;
    Delay_Us(4);
}

//IIC停止信号
//当IIC SCL线处于高电平时，SDA线由低电平向高电平跳变，为IIC停止信号
void IIC_Stop()
{
    IIC_SDA_L;
    IIC_SCL_H;

    Delay_Us(4);

    IIC_SDA_H;
}

//IIC发送一个字节数据（即8bit）
void IIC_SendByte(u8 data)
{
    u8 i;
    //先发送字节的高位bit7
    for (i = 0; i < 8; i++)
    {
        if (data & 0x80)  //判断8位数据每一位的值（0或1）
        {
            IIC_SDA_H;
        }
        else
        {
            IIC_SDA_L;
        }

        Delay_Us(4);      //控制SCL线产生高低电平跳变，产生通讯时钟，同时利用延时函数在SCL为高电平期间读取SDA线电平逻辑
        IIC_SCL_H;
        Delay_Us(4);
        IIC_SCL_L;

        if (i == 7)
        {
            IIC_SDA_H;    //控制SDA线输出高电平，释放总线，等待接收方应答信号
        }

        data <<= 1;       //左移一个bit
        Delay_Us(4);
    }
}

//IIC读取一个字节
u8 IIC_ReadByte(unsigned char ack)
{
    u8 i;
    u8 value;

    //读到第1个bit为数据的bit7
    value = 0;
    for(i = 0; i < 8; i++)
    {
        value <<= 1;
        IIC_SCL_H;
        Delay_Us(4);
        if (I2C_SDA_READ()) //利用延时函数在SCL为高电平期间读取SDA线电平逻辑
        {
            value++;
        }
        IIC_SCL_L;
        Delay_Us(4);
    }
    if(!ack) IIC_NAck();
    else IIC_Ack();
    return value;
}


//IIC等待应答信号
u8 IIC_WaitAck(void)
{
    uint8_t rvalue;

    IIC_SDA_H;     //发送端释放SDA总线，由接收端控制SDA线
    Delay_Us(4);
    IIC_SCL_H;     //在SCL为高电平期间等待响应，若SDA线为高电平，表示NACK信号，反之则为ACK信号
    Delay_Us(4);
    if(I2C_SDA_READ())  //读取SDA线状态判断响应类型，高电平，返回去，为NACK信号，反之则为ACK信号
    {
        rvalue = 1;
    }
    else
    {
        rvalue = 0;
    }
    IIC_SCL_L;
    Delay_Us(4);
    return rvalue;
}

//产生应答信号ACK
void IIC_ACK(void)
{
    IIC_SDA_L;
    Delay_Us(4);
    IIC_SCL_H;   //在SCL线为高电平期间读取SDA线为低电平，则为ACK响应
    Delay_Us(4);
    IIC_SCL_L;
    Delay_Us(4);
    IIC_SDA_H;
}

//产生非应答信号NACK
void IIC_NACK(void)
{
    IIC_SDA_H;
    Delay_Us(4);
    IIC_SCL_H;   //在SCL线为高电平期间读取SDA线为高电平，则为NACK响应
    Delay_Us(4);
    IIC_SCL_L;
    Delay_Us(4);
}

/**
  * @brief  从I2C设备连续读数据（适用于符合IIC通信协议的寄存器地址为uint8类型的器件）
  * @param  addr:I2C从机器件地址
  * @param  reg: I2C从机寄存器地址
  * @param  len: 读出长度
  * @param  buf: uint8数据数组
  * @retval 0,正常; 其他,错误代码;
  */
uint8_t Soft_I2C_Read(uint8_t dev_addr, uint8_t reg_addr, uint8_t len, unsigned char *data_buf)
{
	IIC_Start();
	IIC_SendByte(dev_addr << 1 | I2C_Direction_Transmitter);//发送器件地址+写命令
	if(IIC_WaitAck())//等待应答
	{
		IIC_Stop();
		return 1;
	}
	
	IIC_SendByte(reg_addr);//写寄存器地址
    IIC_WaitAck();//等待应答
	
	IIC_Start();
	IIC_SendByte(dev_addr << 1 | I2C_Direction_Receiver);//发送器件地址+读命令
	IIC_WaitAck();//等待应答
	
    while(len)
	{
		if(len==1)*data_buf=IIC_ReadByte(0);//读数据,发送nACK
		else *data_buf=IIC_ReadByte(1);//读数据,发送ACK
		len--;
		data_buf++;
	}
    IIC_Stop();//产生一个停止条件
	return 0;
}

void IIC_NAck()
{
    IIC_SCL_L;
	IIC_SDA_H;
	Delay_Us(4);
	IIC_SCL_H;
	Delay_Us(4);
	IIC_SCL_L;
}
void IIC_Ack()
{
    IIC_SCL_L;
	IIC_SDA_L;
	Delay_Us(4);
	IIC_SCL_H;
	Delay_Us(4);
	IIC_SCL_L;
}

/**
  * @brief  向I2C设备连续写数据（适用于符合IIC通信协议的寄存器地址为uint8类型的器件）
  * @param  addr:I2C从机器件地址
  * @param  reg: I2C从机寄存器地址
  * @param  len: 写入长度
  * @param  buf: uint8数据数组
  * @retval 0,正常; 其他,错误代码;
  */
uint8_t Soft_I2C_Write(uint8_t dev_addr, uint8_t reg_addr, uint8_t len, unsigned char *data_buf)
{
    uint8_t i;
	
	IIC_Start();
	IIC_SendByte(dev_addr << 1 | I2C_Direction_Transmitter);//发送器件地址+写命令
	if(IIC_WaitAck())//等待应答
	{
		IIC_Stop();
		return 1;
	}
	
	IIC_SendByte(reg_addr);//写寄存器地址
    IIC_WaitAck();//等待应答
	
	for(i=0;i<len;i++)
	{
		IIC_SendByte(data_buf[i]);//发送数据
		if(IIC_WaitAck())//等待ACK
		{
			IIC_Stop();
			return 1;
		}
	}
    IIC_Stop();
	return 0;
}
