/*
 * COMMlibF3.h
 *
 *  Created on: 17.03.2019
 *      Author: Adam
 */

#ifndef INC_COMMLIBF3_H_
#define INC_COMMLIBF3_H_

#include "stm32f3xx_hal.h"
#include "CANlibF3.h"

void COM_LoadCommandList(void);

void COM_RunCanAction();
void COM_RunUartAction();

typedef struct command{
	uint8_t ID;
	uint8_t length;
	void (*reciveUartAction) ();
	void (*reciveCanAction) ();
}command;

command commandList[150];


#endif /* INC_COMMLIBF3_H_ */
