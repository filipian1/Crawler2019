/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f3xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define MOTOR3_D1_Pin GPIO_PIN_14
#define MOTOR3_D1_GPIO_Port GPIOC
#define MOTOR3_EN_Pin GPIO_PIN_15
#define MOTOR3_EN_GPIO_Port GPIOC
#define MOTOR3_FB_Pin GPIO_PIN_0
#define MOTOR3_FB_GPIO_Port GPIOC
#define MOTOR3_SF_Pin GPIO_PIN_1
#define MOTOR3_SF_GPIO_Port GPIOC
#define MOTOR3_IN1_Pin GPIO_PIN_2
#define MOTOR3_IN1_GPIO_Port GPIOC
#define MOTOR3_IN2_Pin GPIO_PIN_3
#define MOTOR3_IN2_GPIO_Port GPIOC
#define MOTOR1_IN2_Pin GPIO_PIN_2
#define MOTOR1_IN2_GPIO_Port GPIOA
#define MOTOR1_IN1_Pin GPIO_PIN_3
#define MOTOR1_IN1_GPIO_Port GPIOA
#define MOTOR1_FB_Pin GPIO_PIN_4
#define MOTOR1_FB_GPIO_Port GPIOA
#define MOTOR1_SF_Pin GPIO_PIN_5
#define MOTOR1_SF_GPIO_Port GPIOA
#define MOTOR1_TEMP_Pin GPIO_PIN_6
#define MOTOR1_TEMP_GPIO_Port GPIOA
#define MOTOR2_TEMP_Pin GPIO_PIN_0
#define MOTOR2_TEMP_GPIO_Port GPIOB
#define MOTOR3_TEMP_Pin GPIO_PIN_1
#define MOTOR3_TEMP_GPIO_Port GPIOB
#define MOTOR1_D1_Pin GPIO_PIN_10
#define MOTOR1_D1_GPIO_Port GPIOB
#define MOTOR1_EN_Pin GPIO_PIN_11
#define MOTOR1_EN_GPIO_Port GPIOB
#define MOTOR2_FB_Pin GPIO_PIN_13
#define MOTOR2_FB_GPIO_Port GPIOB
#define MOTOR2_D1_Pin GPIO_PIN_6
#define MOTOR2_D1_GPIO_Port GPIOC
#define MOTOR2_EN_Pin GPIO_PIN_7
#define MOTOR2_EN_GPIO_Port GPIOC
#define MOTOR2_IN2_Pin GPIO_PIN_8
#define MOTOR2_IN2_GPIO_Port GPIOA
#define MOTOR2_IN1_Pin GPIO_PIN_9
#define MOTOR2_IN1_GPIO_Port GPIOA
#define MOTOR2_SF_Pin GPIO_PIN_10
#define MOTOR2_SF_GPIO_Port GPIOA
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
