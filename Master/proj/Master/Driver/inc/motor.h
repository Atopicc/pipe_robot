#ifndef __MOTOR_H_
#define __MOTOR_H_

#include "debug.h"

void MotorInit();
void setSpeed(uint16_t motor, int16_t speed);
void Motor_Advanced(void);
void Motor_Back(void);
void Motor_Stop(void);

#endif