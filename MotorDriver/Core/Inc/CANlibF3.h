/*
 * CAN_libF3.h
 *
 *  Created on: 01.12.2018
 *      Author: Adam
 */

#ifndef INC_CANLIBF3_H_
#define INC_CANLIBF3_H_

#include "stm32f3xx_hal.h"
#include "stm32f3xx_hal_can.h"

#define LEFT_MOTORS
//#define RIGHT_MOTORS

void CAN_Init(void);
CAN_HandleTypeDef hcan;

CAN_TxHeaderTypeDef CAN_Header;
uint32_t CAN_TxMailbox;

#endif /* INC_CANLIBF3_H_ */
