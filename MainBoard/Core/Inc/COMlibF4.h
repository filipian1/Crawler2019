/*

 * COMMlibF4.h
 *
 *  Created on: 06.01.2019
 *      Author: Adam
*/

#ifndef SRC_COMLIBF4_H_
#define SRC_COMLIBF4_H_

#include "stm32f4xx_hal.h"
#include "UARTlibF4.h"
#include "CANlibF4.h"

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



#endif  /*SRC_COMLIBF4_H_*/

