/*
 * PWM_LIB.h
 *
 *  Created on: 20.11.2018
 *      Author: grzec
 */

#ifndef PWM_LIB_H_
#define PWM_LIB_H_

#include "stm32f3xx_hal.h"
#include "stm32f3xx_hal_tim.h"

#include "TIMlibF3.h"


//void initTIM2();
void PWM_Init();
void StartMotors();
void StopMotors();
void PWM_Set(int16_t counter);
void PWM_Calcluate(uint8_t vx, uint8_t vy);
#endif /* PWM_LIB_H_ */
