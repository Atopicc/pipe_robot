#include "AHTD.h"

// ��ʱ�����������ʵ��ʱ�ӵ�����
void delay_us(uint32_t us)
{
    us *= SystemCoreClock / 1000000 / 5;
    while(us--);
}

// ���I2C��ʼ��
void DI2C_Init(void) {
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    // SCL����Ϊ�������
    GPIO_InitStructure.GPIO_Pin = I2C_SCL_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(I2C_SCL_PORT, &GPIO_InitStructure);

    // SDA����Ϊ�������
    GPIO_InitStructure.GPIO_Pin = I2C_SDA_PIN;
    GPIO_Init(I2C_SDA_PORT, &GPIO_InitStructure);

    // ��ʼ״̬����
    GPIO_SetBits(I2C_SCL_PORT, I2C_SCL_PIN);
    GPIO_SetBits(I2C_SDA_PORT, I2C_SDA_PIN);
}

// ������ʼ�ź�
void I2C_Start(void) {
    GPIO_SetBits(I2C_SDA_PORT, I2C_SDA_PIN);
    GPIO_SetBits(I2C_SCL_PORT, I2C_SCL_PIN);
    delay_us(10);
    GPIO_ResetBits(I2C_SDA_PORT, I2C_SDA_PIN);
    delay_us(10);
    GPIO_ResetBits(I2C_SCL_PORT, I2C_SCL_PIN);
}

// ����ֹͣ�ź�
void I2C_Stop(void) {
    GPIO_ResetBits(I2C_SDA_PORT, I2C_SDA_PIN);
    GPIO_ResetBits(I2C_SCL_PORT, I2C_SCL_PIN);
    delay_us(10);
    GPIO_SetBits(I2C_SCL_PORT, I2C_SCL_PIN);
    delay_us(10);
    GPIO_SetBits(I2C_SDA_PORT, I2C_SDA_PIN);
    delay_us(10);
}

// �ȴ�ACK
uint8_t I2C_Wait_Ack(void) {
    GPIO_InitTypeDef GPIO_InitStructure;

    // �л�SDAΪ����ģʽ
    GPIO_InitStructure.GPIO_Pin = I2C_SDA_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(I2C_SDA_PORT, &GPIO_InitStructure);

    GPIO_SetBits(I2C_SCL_PORT, I2C_SCL_PIN);
    delay_us(10);
    if(GPIO_ReadInputDataBit(I2C_SDA_PORT, I2C_SDA_PIN)) {
        GPIO_ResetBits(I2C_SCL_PORT, I2C_SCL_PIN);
        return 1; // NACK
    }
    GPIO_ResetBits(I2C_SCL_PORT, I2C_SCL_PIN);
    
    // �ָ�SDAΪ���ģʽ
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(I2C_SDA_PORT, &GPIO_InitStructure);
    return 0; // ACK
}

// ����һ���ֽ�
void I2C_Send_Byte(uint8_t data) {
    for(uint8_t i=0; i<8; i++) {
        GPIO_ResetBits(I2C_SCL_PORT, I2C_SCL_PIN);
        if(data & 0x80)
            GPIO_SetBits(I2C_SDA_PORT, I2C_SDA_PIN);
        else
            GPIO_ResetBits(I2C_SDA_PORT, I2C_SDA_PIN);
        delay_us(4);
        GPIO_SetBits(I2C_SCL_PORT, I2C_SCL_PIN);
        delay_us(10);
        data <<= 1;
    }
    GPIO_ResetBits(I2C_SCL_PORT, I2C_SCL_PIN);
}

// ��ȡһ���ֽ�
uint8_t I2C_Read_Byte(uint8_t ack) {
    uint8_t data = 0;
    GPIO_InitTypeDef GPIO_InitStructure;

    // �л�SDAΪ����ģʽ
    GPIO_InitStructure.GPIO_Pin = I2C_SDA_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(I2C_SDA_PORT, &GPIO_InitStructure);

    for(uint8_t i=0; i<8; i++) {
        data <<= 1;
        GPIO_SetBits(I2C_SCL_PORT, I2C_SCL_PIN);
        delay_us(4);
        if(GPIO_ReadInputDataBit(I2C_SDA_PORT, I2C_SDA_PIN)) data |= 0x01;
        GPIO_ResetBits(I2C_SCL_PORT, I2C_SCL_PIN);
        delay_us(10);
    }

    // �ָ�SDAΪ���ģʽ
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(I2C_SDA_PORT, &GPIO_InitStructure);

    // ����ACK/NACK
    if(ack) {
        GPIO_ResetBits(I2C_SDA_PORT, I2C_SDA_PIN);
    } else {
        GPIO_SetBits(I2C_SDA_PORT, I2C_SDA_PIN);
    }
    GPIO_SetBits(I2C_SCL_PORT, I2C_SCL_PIN);
    delay_us(10);
    GPIO_ResetBits(I2C_SCL_PORT, I2C_SCL_PIN);
    return data;
}

// ��ʼ��AHT20
uint8_t DAHT20_Init(void) {
    // ���ӳ�ʼ��ʱ
    Delay_Ms(100);  // �ϵ��ȴ��ȶ�
    
    // ���ͳ�ʼ������
    I2C_Start();
    I2C_Send_Byte(0x70);
    if(I2C_Wait_Ack()) {
        I2C_Stop();
        return 2;
    }
    
    I2C_Send_Byte(0xBE); // ��ʼ������
    if(I2C_Wait_Ack()) {
        I2C_Stop();
        return 3;
    }
    
    I2C_Send_Byte(0x08); // ����1
    if(I2C_Wait_Ack()) {
        I2C_Stop();
        return 4;
    }
    
    I2C_Send_Byte(0x00); // ����2
    if(I2C_Wait_Ack()) {
        I2C_Stop();
        return 5;
    }
    
    I2C_Stop();
    Delay_Ms(500); // �ӳ���ʼ���ȴ�ʱ��
    return 0;
}

// ��ȡ��ʪ������
uint8_t AHT20_Read(float *humidity, float *temperature) {
    uint8_t data[6] = {0};
    
    // ��������
    I2C_Start();
    I2C_Send_Byte(0x70);
    if(I2C_Wait_Ack()) return 1;
    
    I2C_Send_Byte(0xAC);
    if(I2C_Wait_Ack()) return 2;
    
    I2C_Send_Byte(0x33);
    if(I2C_Wait_Ack()) return 3;
    
    I2C_Send_Byte(0x00);
    if(I2C_Wait_Ack()) return 4;
    I2C_Stop();
    
    // �ȴ��������
    delay_us(80000);
    
    // ��ȡ����
    I2C_Start();
    I2C_Send_Byte(0x71); // ����ַ
    if(I2C_Wait_Ack()) return 5;
    
    for(uint8_t i=0; i<6; i++) {
        data[i] = I2C_Read_Byte(i==5?0:1);
    }
    I2C_Stop();
    
    // ���״̬λ
    if(data[0] & 0x80) return 6; // �豸æ
    
    // ת������
    uint32_t hum_raw = ((uint32_t)data[1] << 12) | ((uint32_t)data[2] << 4) | (data[3] >> 4);
    uint32_t temp_raw = ((uint32_t)(data[3]&0x0F) << 16) | ((uint32_t)data[4] << 8) | data[5];
    
    *humidity = (hum_raw * 100.0) / (1 << 20);
    *temperature = (temp_raw * 200.0) / (1 << 20) - 50;
    
    return 0;
}
