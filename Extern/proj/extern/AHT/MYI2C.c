#include "MYI2C.h"

//��ʼ��IIC
void IIC_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE );

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;//ʹ��PA1��PA2��Ϊģ��IIC���ţ�PA1��ӦSDA��PA2��ӦSCL
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD ;   //��©���ģʽ
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    IIC_Idle_State();
}

//IIC����״̬
//��IIC���ߵ�SDA��SCL�����ź���ͬʱ���ڸߵ�ƽʱ���涨ΪIIC���ߵĿ���״̬
void IIC_Idle_State()
{
    IIC_SDA_H;
    IIC_SCL_H;

    Delay_Us(4);
}

//IIC��ʼ�ź�
//��IIC SCL�ߴ��ڸߵ�ƽʱ��SDA���ɸߵ�ƽ��͵�ƽ���䣬ΪIIC��ʼ�źţ����ÿ�ʼ�ź�ǰ���뱣֤IIC���ߴ��ڿ���״̬
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

//IICֹͣ�ź�
//��IIC SCL�ߴ��ڸߵ�ƽʱ��SDA���ɵ͵�ƽ��ߵ�ƽ���䣬ΪIICֹͣ�ź�
void IIC_Stop()
{
    IIC_SDA_L;
    IIC_SCL_H;

    Delay_Us(4);

    IIC_SDA_H;
}

//IIC����һ���ֽ����ݣ���8bit��
void IIC_SendByte(u8 data)
{
    u8 i;
    //�ȷ����ֽڵĸ�λbit7
    for (i = 0; i < 8; i++)
    {
        if (data & 0x80)  //�ж�8λ����ÿһλ��ֵ��0��1��
        {
            IIC_SDA_H;
        }
        else
        {
            IIC_SDA_L;
        }

        Delay_Us(4);      //����SCL�߲����ߵ͵�ƽ���䣬����ͨѶʱ�ӣ�ͬʱ������ʱ������SCLΪ�ߵ�ƽ�ڼ��ȡSDA�ߵ�ƽ�߼�
        IIC_SCL_H;
        Delay_Us(4);
        IIC_SCL_L;

        if (i == 7)
        {
            IIC_SDA_H;    //����SDA������ߵ�ƽ���ͷ����ߣ��ȴ����շ�Ӧ���ź�
        }

        data <<= 1;       //����һ��bit
        Delay_Us(4);
    }
}

//IIC��ȡһ���ֽ�
u8 IIC_ReadByte(unsigned char ack)
{
    u8 i;
    u8 value;

    //������1��bitΪ���ݵ�bit7
    value = 0;
    for(i = 0; i < 8; i++)
    {
        value <<= 1;
        IIC_SCL_H;
        Delay_Us(4);
        if (I2C_SDA_READ()) //������ʱ������SCLΪ�ߵ�ƽ�ڼ��ȡSDA�ߵ�ƽ�߼�
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


//IIC�ȴ�Ӧ���ź�
u8 IIC_WaitAck(void)
{
    uint8_t rvalue;

    IIC_SDA_H;     //���Ͷ��ͷ�SDA���ߣ��ɽ��ն˿���SDA��
    Delay_Us(4);
    IIC_SCL_H;     //��SCLΪ�ߵ�ƽ�ڼ�ȴ���Ӧ����SDA��Ϊ�ߵ�ƽ����ʾNACK�źţ���֮��ΪACK�ź�
    Delay_Us(4);
    if(I2C_SDA_READ())  //��ȡSDA��״̬�ж���Ӧ���ͣ��ߵ�ƽ������ȥ��ΪNACK�źţ���֮��ΪACK�ź�
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

//����Ӧ���ź�ACK
void IIC_ACK(void)
{
    IIC_SDA_L;
    Delay_Us(4);
    IIC_SCL_H;   //��SCL��Ϊ�ߵ�ƽ�ڼ��ȡSDA��Ϊ�͵�ƽ����ΪACK��Ӧ
    Delay_Us(4);
    IIC_SCL_L;
    Delay_Us(4);
    IIC_SDA_H;
}

//������Ӧ���ź�NACK
void IIC_NACK(void)
{
    IIC_SDA_H;
    Delay_Us(4);
    IIC_SCL_H;   //��SCL��Ϊ�ߵ�ƽ�ڼ��ȡSDA��Ϊ�ߵ�ƽ����ΪNACK��Ӧ
    Delay_Us(4);
    IIC_SCL_L;
    Delay_Us(4);
}

/**
  * @brief  ��I2C�豸���������ݣ������ڷ���IICͨ��Э��ļĴ�����ַΪuint8���͵�������
  * @param  addr:I2C�ӻ�������ַ
  * @param  reg: I2C�ӻ��Ĵ�����ַ
  * @param  len: ��������
  * @param  buf: uint8��������
  * @retval 0,����; ����,�������;
  */
uint8_t Soft_I2C_Read(uint8_t dev_addr, uint8_t reg_addr, uint8_t len, unsigned char *data_buf)
{
	IIC_Start();
	IIC_SendByte(dev_addr << 1 | I2C_Direction_Transmitter);//����������ַ+д����
	if(IIC_WaitAck())//�ȴ�Ӧ��
	{
		IIC_Stop();
		return 1;
	}
	
	IIC_SendByte(reg_addr);//д�Ĵ�����ַ
    IIC_WaitAck();//�ȴ�Ӧ��
	
	IIC_Start();
	IIC_SendByte(dev_addr << 1 | I2C_Direction_Receiver);//����������ַ+������
	IIC_WaitAck();//�ȴ�Ӧ��
	
    while(len)
	{
		if(len==1)*data_buf=IIC_ReadByte(0);//������,����nACK
		else *data_buf=IIC_ReadByte(1);//������,����ACK
		len--;
		data_buf++;
	}
    IIC_Stop();//����һ��ֹͣ����
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
  * @brief  ��I2C�豸����д���ݣ������ڷ���IICͨ��Э��ļĴ�����ַΪuint8���͵�������
  * @param  addr:I2C�ӻ�������ַ
  * @param  reg: I2C�ӻ��Ĵ�����ַ
  * @param  len: д�볤��
  * @param  buf: uint8��������
  * @retval 0,����; ����,�������;
  */
uint8_t Soft_I2C_Write(uint8_t dev_addr, uint8_t reg_addr, uint8_t len, unsigned char *data_buf)
{
    uint8_t i;
	
	IIC_Start();
	IIC_SendByte(dev_addr << 1 | I2C_Direction_Transmitter);//����������ַ+д����
	if(IIC_WaitAck())//�ȴ�Ӧ��
	{
		IIC_Stop();
		return 1;
	}
	
	IIC_SendByte(reg_addr);//д�Ĵ�����ַ
    IIC_WaitAck();//�ȴ�Ӧ��
	
	for(i=0;i<len;i++)
	{
		IIC_SendByte(data_buf[i]);//��������
		if(IIC_WaitAck())//�ȴ�ACK
		{
			IIC_Stop();
			return 1;
		}
	}
    IIC_Stop();
	return 0;
}
