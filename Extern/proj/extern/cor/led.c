#include "led.h"

void LED_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure = {0};
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOD,&GPIO_InitStructure);
	GPIO_SetBits(GPIOD,GPIO_Pin_1);
}

void LEDTask()
{
    GPIO_ResetBits(GPIOD,GPIO_Pin_1);
	Delay_Ms(100);
    GPIO_SetBits(GPIOD,GPIO_Pin_1);
	Delay_Ms(100);
}