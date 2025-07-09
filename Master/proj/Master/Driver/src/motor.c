#include "motor.h"

#define TIM_CHANNEL_1 1
#define TIM_CHANNEL_2 2
#define TIM_CHANNEL_3 3
#define TIM_CHANNEL_4 4

// 需要实现的通用PWM设置宏
#define TIM_SetCompareX(TIMx, CHX, VAL) \
    switch (CHX) { \
        case TIM_CHANNEL_1: TIM_SetCompare1(TIMx, VAL); break; \
        case TIM_CHANNEL_2: TIM_SetCompare2(TIMx, VAL); break; \
        case TIM_CHANNEL_3: TIM_SetCompare3(TIMx, VAL); break; \
        case TIM_CHANNEL_4: TIM_SetCompare4(TIMx, VAL); break; \
    }

// 定义电机参数结构
typedef struct {
    TIM_TypeDef* timer;
    uint32_t forward_ch;
    uint32_t reverse_ch;
} MotorConfig;

// 电机配置表
static const MotorConfig config[] = {
    {TIM3, TIM_CHANNEL_1, TIM_CHANNEL_2},  // Motor 1
    {TIM3, TIM_CHANNEL_3, TIM_CHANNEL_4},  // Motor 2
    {TIM4, TIM_CHANNEL_1, TIM_CHANNEL_2},  // Motor 3
    {TIM4, TIM_CHANNEL_3, TIM_CHANNEL_4}   // Motor 4
};

void TIM3_PWMOut_Init( u16 arr, u16 psc, u16 ccp )
{
	GPIO_InitTypeDef GPIO_InitStructure={0};
	TIM_OCInitTypeDef TIM_OCInitStructure={0};
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure={0};

	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE );
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init( GPIOA, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
    GPIO_Init( GPIOB, &GPIO_InitStructure);

	TIM_TimeBaseInitStructure.TIM_Period = arr;
	TIM_TimeBaseInitStructure.TIM_Prescaler = psc;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit( TIM3, &TIM_TimeBaseInitStructure);

  	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;

	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = ccp;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

	TIM_OC1Init( TIM3, &TIM_OCInitStructure );
	TIM_OC2Init( TIM3, &TIM_OCInitStructure );
	TIM_OC3Init( TIM3, &TIM_OCInitStructure );
	TIM_OC4Init( TIM3, &TIM_OCInitStructure );

	TIM_OC1PreloadConfig( TIM3, TIM_OCPreload_Enable );
	TIM_OC2PreloadConfig( TIM3, TIM_OCPreload_Enable );
	TIM_OC3PreloadConfig( TIM3, TIM_OCPreload_Enable );
	TIM_OC4PreloadConfig( TIM3, TIM_OCPreload_Enable );

	TIM_CtrlPWMOutputs(TIM3, ENABLE );
	TIM_ARRPreloadConfig( TIM3, ENABLE );
	TIM_Cmd( TIM3, ENABLE );
}

void TIM4_PWMOut_Init( u16 arr, u16 psc, u16 ccp )
{
	GPIO_InitTypeDef GPIO_InitStructure={0};
	TIM_OCInitTypeDef TIM_OCInitStructure={0};
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure={0};

	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE );
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init( GPIOB, &GPIO_InitStructure);

	TIM_TimeBaseInitStructure.TIM_Period = arr;
	TIM_TimeBaseInitStructure.TIM_Prescaler = psc;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit( TIM4, &TIM_TimeBaseInitStructure);

  	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;

	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = ccp;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

	TIM_OC1Init( TIM4, &TIM_OCInitStructure );
	TIM_OC2Init( TIM4, &TIM_OCInitStructure );
	TIM_OC3Init( TIM4, &TIM_OCInitStructure );
	TIM_OC4Init( TIM4, &TIM_OCInitStructure );

	TIM_OC1PreloadConfig( TIM4, TIM_OCPreload_Enable );
	TIM_OC2PreloadConfig( TIM4, TIM_OCPreload_Enable );
	TIM_OC3PreloadConfig( TIM4, TIM_OCPreload_Enable );
	TIM_OC4PreloadConfig( TIM4, TIM_OCPreload_Enable );

	TIM_CtrlPWMOutputs(TIM4, ENABLE );
	TIM_ARRPreloadConfig( TIM4, ENABLE );
	TIM_Cmd( TIM4, ENABLE );
}

void MotorInit()
{
    TIM3_PWMOut_Init(100-1,960-1,50);
    TIM4_PWMOut_Init(100-1,960-1,50);
}

void setSpeed(uint16_t motor, int16_t speed)
{

    if (motor < 1 || motor > 4) return;
    speed = (speed < -100) ? -100 : (speed > 100) ? 100 : speed;

    // 获取电机配置
    const MotorConfig* cfg = &config[motor-1];
    
    // 设置PWM占空比
    if (speed > 0) {
        TIM_SetCompareX(cfg->timer, cfg->forward_ch, speed);
        TIM_SetCompareX(cfg->timer, cfg->reverse_ch, 0);
    } else if (speed < 0) {
        TIM_SetCompareX(cfg->timer, cfg->forward_ch, 0);
        TIM_SetCompareX(cfg->timer, cfg->reverse_ch, -speed);
    } else {
        TIM_SetCompareX(cfg->timer, cfg->forward_ch, 0);
        TIM_SetCompareX(cfg->timer, cfg->reverse_ch, 0);
    }
}

void Motor_Advanced(void)
{
	setSpeed(1,100);
	setSpeed(2,-100);
	setSpeed(3,-100);
	setSpeed(4,-100);
}

void Motor_Back(void)
{
	setSpeed(1,-100);
	setSpeed(2,100);
	setSpeed(3,100);
	setSpeed(4,100);
}

void Motor_Stop(void)
{
	setSpeed(1,0);
	setSpeed(2,0);
	setSpeed(3,0);
	setSpeed(4,0);
}
