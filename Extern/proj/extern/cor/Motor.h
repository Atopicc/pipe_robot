#ifndef __MOTOR_H
#define __MOTOR_H

#include "debug.h"

void Motor_Init( u16 arr, u16 psc, u16 ccp );
void mo_init(void);
void Motor_Control(uint8_t state);

#endif