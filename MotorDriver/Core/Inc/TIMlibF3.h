/*
 * TIMlibF3.h
 *
 *  Created on: 11.01.2019
 *      Author: Adam
 */

#ifndef SRC_TIMLIBF3_H_
#define SRC_TIMLIBF3_H_

#include "stm32f3xx_hal.h"
#include "ENClibF3.h"
#include "stm32f3xx_hal_tim.h"


extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim15;
extern TIM_HandleTypeDef htim16;
extern TIM_HandleTypeDef htim17;

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

extern void _Error_Handler(char *, int);

float ENK_MotorSpeed[3];

void MX_TIM1_Init(void);
void MX_TIM2_Init(void);
void MX_TIM15_Init(void);
void MX_TIM16_Init(void);
void MX_TIM17_Init(void);

void ENK_TIM_Init();

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

#endif /* SRC_TIMLIBF3_H_ */
