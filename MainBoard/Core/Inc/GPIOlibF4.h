/*
 * GPIOlibF4.h
 *
 *  Created on: 25.11.2018
 *      Author: Adam
 */

#ifndef INC_GPIOLIBF4_H_
#define INC_GPIOLIBF4_H_

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_tim.h"

TIM_HandleTypeDef htim6;

typedef enum {
	LED_STATUS = 1,
	LED_ERROR,
	LED_NUCLEO
}LED_TypeDef;


void GPIO_LEDInit(void);
void GPIO_PushButtonInit(void);
void GPIO_LEDWrite(LED_TypeDef, GPIO_PinState);
void GPIO_LEDToggle(LED_TypeDef);
void GPIO_BuzzerBeep(void);
void GPIO_BuzzerInit(void);
void GPIO_BuzzFun();

#endif /* INC_GPIOLIBF4_H_ */
