#include "debug.h"
#include "pwm.h"

// 初始化舵机参数数组
const ServerData_t Servers[SERVER_COUNT] = {
    [SERVER6]  = {TIM9, TIM_SetCompare1},
    [SERVER7]  = {TIM9, TIM_SetCompare2},
    [SERVER8]  = {TIM8, TIM_SetCompare1},
    [SERVER9]  = {TIM8, TIM_SetCompare2},
    [SERVER10] = {TIM8, TIM_SetCompare3},
    [SERVER11] = {TIM8, TIM_SetCompare4}
};


/*********************************************************************
 * @fn      TIM1_OutCompare_Init
 *
 * @brief   Initializes TIM1 output compare.
 *
 * @param   arr - the period value.
 *          psc - the prescaler value.
 *          ccp - the pulse value.
 *
 * @return  none
 */
void TIM8_PWMOut_Init( u16 arr, u16 psc, u16 ccp )
{
	GPIO_InitTypeDef GPIO_InitStructure={0};
	TIM_OCInitTypeDef TIM_OCInitStructure={0};
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure={0};

	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE );
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
	// RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init( GPIOC, &GPIO_InitStructure);

	TIM_TimeBaseInitStructure.TIM_Period = arr;
	TIM_TimeBaseInitStructure.TIM_Prescaler = psc;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit( TIM8, &TIM_TimeBaseInitStructure);

  	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;

	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
	TIM_OCInitStructure.TIM_Pulse = ccp;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;

	TIM_OC1Init( TIM8, &TIM_OCInitStructure );
	TIM_OC2Init( TIM8, &TIM_OCInitStructure );
	TIM_OC3Init( TIM8, &TIM_OCInitStructure );
	TIM_OC4Init( TIM8, &TIM_OCInitStructure );

	TIM_OC1PreloadConfig( TIM8, TIM_OCPreload_Enable );
	TIM_OC2PreloadConfig( TIM8, TIM_OCPreload_Enable );
	TIM_OC3PreloadConfig( TIM8, TIM_OCPreload_Enable );
	TIM_OC4PreloadConfig( TIM8, TIM_OCPreload_Enable );

	TIM_CtrlPWMOutputs(TIM8, ENABLE );
	TIM_ARRPreloadConfig( TIM8, ENABLE );
	TIM_Cmd( TIM8, ENABLE );
}

void TIM9_PWMOut_Init( u16 arr, u16 psc, u16 ccp )
{
	GPIO_InitTypeDef GPIO_InitStructure={0};
	TIM_OCInitTypeDef TIM_OCInitStructure={0};
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure={0};

	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOD, ENABLE );
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init( GPIOD, &GPIO_InitStructure);

	GPIO_PinRemapConfig(GPIO_FullRemap_TIM9,ENABLE);

	TIM_TimeBaseInitStructure.TIM_Period = arr;
	TIM_TimeBaseInitStructure.TIM_Prescaler = psc;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit( TIM9, &TIM_TimeBaseInitStructure);

#if (PWM_MODE == PWM_MODE1)
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;

#elif (PWM_MODE == PWM_MODE2)
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;

#endif

	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
	TIM_OCInitStructure.TIM_Pulse = ccp;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;

	TIM_OC1Init( TIM9, &TIM_OCInitStructure );
	TIM_OC2Init( TIM9, &TIM_OCInitStructure );

	TIM_OC1PreloadConfig( TIM9, TIM_OCPreload_Enable );
	TIM_OC2PreloadConfig( TIM9, TIM_OCPreload_Enable );

	TIM_CtrlPWMOutputs(TIM9, ENABLE );
	TIM_ARRPreloadConfig( TIM9, ENABLE );
	TIM_Cmd( TIM9, ENABLE );
}

void PWMOutputInit()
{
    TIM9_PWMOut_Init(20000-1, 96-1, 500);
	TIM8_PWMOut_Init(20000-1, 96-1, 500);
}

/*
value: 500 - 2500
angle: -90 - 90
*/
void SetServerAngle(ServerEnum server, int16_t angle)
{
    // 确保角度在有效范围内
    angle = (angle < -90) ? -90 : (angle > 90) ? 90 : angle;
    
    // 线性映射计算公式
    uint16_t value = (uint16_t)(((angle + 90) * (2500 - 500)) / 180.0 + 500);
    
    // 调用对应的设置函数
    Servers[server].setCompare(Servers[server].timer, value);
}

void Servo_Reset(void)
{
	SetServerAngle(SERVER6,0);
	SetServerAngle(SERVER7,0);
	SetServerAngle(SERVER8,0);
	SetServerAngle(SERVER9,0);
	SetServerAngle(SERVER10,0);
	SetServerAngle(SERVER11,0);
}



