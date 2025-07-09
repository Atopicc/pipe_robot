#ifndef __PWM_H_
#define __PWM_H_

#include "debug.h"
#include <stdint.h>

typedef struct
{
    TIM_TypeDef *timer;
    void (*setCompare)(TIM_TypeDef* TIMx, uint16_t Compare);
} ServerData_t;

typedef enum 
{
    SERVER6,
    SERVER7,
    SERVER8,
    SERVER9,
    SERVER10,
    SERVER11,
    SERVER_COUNT
} ServerEnum;

extern const ServerData_t Servers[SERVER_COUNT];

void SetServerAngle(ServerEnum server, int16_t angle);
void PWMOutputInit();
void Servo_Reset(void);



#endif
