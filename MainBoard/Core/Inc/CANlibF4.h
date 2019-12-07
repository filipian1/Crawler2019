/*
 * CANlibF4.h
 *
 *  Created on: 03.12.2018
 *      Author: Adam
 */

#ifndef INC_CANLIBF4_H_
#define INC_CANLIBF4_H_

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_can.h"
#include "COMlibF4.h"

CAN_HandleTypeDef hcan1;
CAN_RxHeaderTypeDef CAN_RxHeader;
uint8_t CAN_RxMsg[8];

uint32_t CAN_TxMailbox;
CAN_TxHeaderTypeDef CAN_TxHeader;
uint8_t CAN_TxData[8];

uint8_t dane[8];
uint32_t txmailbox;
CAN_TxHeaderTypeDef canmsg;
void CAN_Init();
#endif /* INC_CANLIBF4_H_ */
