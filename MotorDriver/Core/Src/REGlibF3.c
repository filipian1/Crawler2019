/*
 * REGlibF3.c
 *
 *  Created on: 17.03.2019
 *      Author: Adam
 */

#include "REGlibF3.h"

#define REFERENCE_MULTIPILER 10

int16_t ReferencePulse=0;
int16_t CurrentPulse=0;
float CurrentPulseFloat=0.0;
volatile float InertialGain=0.003;

void SetInertial();


void REG_MainFunction()
{
	SetInertial();
	PWM_Set(CurrentPulse);

}

void REG_SetReference(int16_t speed)
{
	ReferencePulse=speed*REFERENCE_MULTIPILER;
}
void SetInertial()
{
	CurrentPulseFloat += (InertialGain*((float)(ReferencePulse)-(float)(CurrentPulse)));
	CurrentPulse = (int16_t) CurrentPulseFloat;
}
