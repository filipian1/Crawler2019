#ifndef SRC_ADCLIBF4_H_
#define SRC_ADCLIBF4_H_


#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_adc.h"
#include "stm32f4xx_hal_dma.h"
ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;

void  ADC_Initialisation();

#endif /* SRC_ADCLIBF4_H_ */
