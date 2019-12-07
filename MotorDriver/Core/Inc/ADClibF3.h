

#ifndef ADCLIBF3_H_
#define ADCLIBF3_H_
#include "stm32f3xx_hal.h"
#include "stm32f3xx_hal_adc.h"
#include "stm32f3xx_hal_dma.h"
#include "CANlibF3.h"

DMA_HandleTypeDef hdma_adc1;
ADC_HandleTypeDef hadc1;

void ADC_Initialisation();
void ADC_Function();

uint32_t ADC_MeasRaw[6];


#endif /* ADCLIBF3_H_ */
