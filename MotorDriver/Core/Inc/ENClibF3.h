/*
 * ENClibF3.h
 *
 *  Created on: 10.01.2019
 *      Author: Adam
 */

#ifndef SRC_ENCLIBF3_H_
#define SRC_ENCLIBF3_H_

#include "stm32f3xx_hal.h"
#include "stm32f3xx_hal_tim.h"

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
void ENC_Init();
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim);
void frequency_ret(int32_t abs_period1,int32_t abs_period2, int32_t abs_period3);
void ENK_TIM_Init();

/*volatile uint32_t period;
volatile int32_t abs_period;
volatile int32_t f_obr;
volatile int32_t pres;
volatile int32_t freq;*/




#endif /* SRC_ENCLIBF3_H_ */
