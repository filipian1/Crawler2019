/*
 * REGlibF3.h
 *
 *  Created on: 17.03.2019
 *      Author: Adam
 */

#ifndef INC_REGLIBF3_H_
#define INC_REGLIBF3_H_

#include "stm32f3xx_hal.h"
#include "TIMlibF3.h"
#include "PWMlibF3.h"

void REG_MainFunction();
void REG_SetReference(int16_t speed);
void frequency_ret();


#endif /* INC_REGLIBF3_H_ */
