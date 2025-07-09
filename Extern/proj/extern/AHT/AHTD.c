#include "AHTD.h"

// 延时函数（需根据实际时钟调整）
void delay_us(uint32_t us)
{
    us *= SystemCoreClock / 1000000 / 5;
    while(us--);
}

// 软件I2C初始化
void DI2C_Init(void) {
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    // SCL配置为推挽输出
    GPIO_InitStructure.GPIO_Pin = I2C_SCL_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(I2C_SCL_PORT, &GPIO_InitStructure);

    // SDA配置为推挽输出
    GPIO_InitStructure.GPIO_Pin = I2C_SDA_PIN;
    GPIO_Init(I2C_SDA_PORT, &GPIO_InitStructure);

    // 初始状态拉高
    GPIO_SetBits(I2C_SCL_PORT, I2C_SCL_PIN);
    GPIO_SetBits(I2C_SDA_PORT, I2C_SDA_PIN);
}

// 产生起始信号
void I2C_Start(void) {
    GPIO_SetBits(I2C_SDA_PORT, I2C_SDA_PIN);
    GPIO_SetBits(I2C_SCL_PORT, I2C_SCL_PIN);
    delay_us(10);
    GPIO_ResetBits(I2C_SDA_PORT, I2C_SDA_PIN);
    delay_us(10);
    GPIO_ResetBits(I2C_SCL_PORT, I2C_SCL_PIN);
}

// 产生停止信号
void I2C_Stop(void) {
    GPIO_ResetBits(I2C_SDA_PORT, I2C_SDA_PIN);
    GPIO_ResetBits(I2C_SCL_PORT, I2C_SCL_PIN);
    delay_us(10);
    GPIO_SetBits(I2C_SCL_PORT, I2C_SCL_PIN);
    delay_us(10);
    GPIO_SetBits(I2C_SDA_PORT, I2C_SDA_PIN);
    delay_us(10);
}

// 等待ACK
uint8_t I2C_Wait_Ack(void) {
    GPIO_InitTypeDef GPIO_InitStructure;

    // 切换SDA为输入模式
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
    
    // 恢复SDA为输出模式
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(I2C_SDA_PORT, &GPIO_InitStructure);
    return 0; // ACK
}

// 发送一个字节
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

// 读取一个字节
uint8_t I2C_Read_Byte(uint8_t ack) {
    uint8_t data = 0;
    GPIO_InitTypeDef GPIO_InitStructure;

    // 切换SDA为输入模式
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

    // 恢复SDA为输出模式
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(I2C_SDA_PORT, &GPIO_InitStructure);

    // 发送ACK/NACK
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

// 初始化AHT20
uint8_t DAHT20_Init(void) {
    // 增加初始延时
    Delay_Ms(100);  // 上电后等待稳定
    
    // 发送初始化命令
    I2C_Start();
    I2C_Send_Byte(0x70);
    if(I2C_Wait_Ack()) {
        I2C_Stop();
        return 2;
    }
    
    I2C_Send_Byte(0xBE); // 初始化命令
    if(I2C_Wait_Ack()) {
        I2C_Stop();
        return 3;
    }
    
    I2C_Send_Byte(0x08); // 参数1
    if(I2C_Wait_Ack()) {
        I2C_Stop();
        return 4;
    }
    
    I2C_Send_Byte(0x00); // 参数2
    if(I2C_Wait_Ack()) {
        I2C_Stop();
        return 5;
    }
    
    I2C_Stop();
    Delay_Ms(500); // 延长初始化等待时间
    return 0;
}

// 读取温湿度数据
uint8_t AHT20_Read(float *humidity, float *temperature) {
    uint8_t data[6] = {0};
    
    // 触发测量
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
    
    // 等待测量完成
    delay_us(80000);
    
    // 读取数据
    I2C_Start();
    I2C_Send_Byte(0x71); // 读地址
    if(I2C_Wait_Ack()) return 5;
    
    for(uint8_t i=0; i<6; i++) {
        data[i] = I2C_Read_Byte(i==5?0:1);
    }
    I2C_Stop();
    
    // 检查状态位
    if(data[0] & 0x80) return 6; // 设备忙
    
    // 转换数据
    uint32_t hum_raw = ((uint32_t)data[1] << 12) | ((uint32_t)data[2] << 4) | (data[3] >> 4);
    uint32_t temp_raw = ((uint32_t)(data[3]&0x0F) << 16) | ((uint32_t)data[4] << 8) | data[5];
    
    *humidity = (hum_raw * 100.0) / (1 << 20);
    *temperature = (temp_raw * 200.0) / (1 << 20) - 50;
    
    return 0;
}
