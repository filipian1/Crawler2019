/*
 * GPIOlibF4.c
 *
 *  Created on: 25.11.2018
 *      Author: Adam
 */

#include "GPIOlibF4.h"

float  BPM=120.0;


float nuty[50][2];
void Nuty_Init();
uint8_t music=0;

void GPIO_BuzzFun()
{
/*
	volatile static int currentNote=0;
	volatile static int timer=0;
	volatile int target_time=0;
	if (timer>)
	{
		if (nuty[currentNote][1]==0)
		TIM6->ARR=(uint32_t)((2.0/nuty[currentNote][1])*100000.0);
		target_time=(uint32_t)(nuty[currentNote][0]*240.0/BPM);
		timer=0;
	}
*/


}
void Nuty_Init()
{
	nuty[0][0]=0.125;
	nuty[0][1]=659.25;
	nuty[1][0]=0.125;
	nuty[1][1]=659.25;
	nuty[2][0]=0.125;
	nuty[2][1]=0;
	nuty[3][0]=0.125;
	nuty[3][1]=659.25;
	nuty[4][0]=0.125;
	nuty[4][1]=0;
	nuty[5][0]=0.125;
	nuty[5][1]=523.25;
	nuty[5][0]=0.25;
	nuty[5][1]=629.25;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (music==0)
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, GPIO_PIN_RESET);
	}
	else 	HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_11);
}
void GPIO_LEDInit(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */

  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13|GPIO_PIN_14, GPIO_PIN_RESET);


  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB13 PB14 */
  GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_14;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}
void GPIO_BuzzerInit(void)
{
	  GPIO_InitTypeDef GPIO_InitStruct;

	  /* GPIO Ports Clock Enable */


	  __HAL_RCC_GPIOC_CLK_ENABLE();
	  Nuty_Init();
	  /*Configure GPIO pin Output Level */
	  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, GPIO_PIN_RESET);


	  /*Configure GPIO pin : LD2_Pin */
	  GPIO_InitStruct.Pin = GPIO_PIN_11;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);


	  TIM_MasterConfigTypeDef sMasterConfig;

	   htim6.Instance = TIM6;
	   htim6.Init.Prescaler = 450;
	   htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
	   htim6.Init.Period = 20;
	   if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
	   {
	     _Error_Handler(__FILE__, __LINE__);
	   }
	   HAL_TIM_Base_Start_IT(&htim6);

	 //  __HAL_TIM_ENABLE_IT()
	   sMasterConfig.MasterOutputTrigger =TIM_TRGO_UPDATE;
	   sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	   if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig) != HAL_OK)
	   {
	     _Error_Handler(__FILE__, __LINE__);
	   }




}
void GPIO_BuzzerBeep(void)
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, GPIO_PIN_SET);
	HAL_Delay(500);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, GPIO_PIN_RESET);
	HAL_Delay(500);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, GPIO_PIN_SET);
	HAL_Delay(500);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, GPIO_PIN_RESET);
}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* htim_base)
{

  if(htim_base->Instance==TIM6)
  {
  /* USER CODE BEGIN TIM6_MspInit 0 */

  /* USER CODE END TIM6_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_TIM6_CLK_ENABLE();
    /* TIM6 interrupt Init */
    HAL_NVIC_SetPriority(TIM6_DAC_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn);
  /* USER CODE BEGIN TIM6_MspInit 1 */

  /* USER CODE END TIM6_MspInit 1 */
  }

}

void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* htim_base)
{

  if(htim_base->Instance==TIM6)
  {
  /* USER CODE BEGIN TIM6_MspDeInit 0 */

  /* USER CODE END TIM6_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM6_CLK_DISABLE();

    /* TIM6 interrupt DeInit */
    HAL_NVIC_DisableIRQ(TIM6_DAC_IRQn);
  /* USER CODE BEGIN TIM6_MspDeInit 1 */

  /* USER CODE END TIM6_MspDeInit 1 */
  }

}
void GPIO_PushButtonInit(void)
{
	  GPIO_InitTypeDef GPIO_InitStruct;
	  /* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOC_CLK_ENABLE();


	  /*Configure GPIO pin : B1_Pin */
	  GPIO_InitStruct.Pin = GPIO_PIN_13;
	  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}
void GPIO_LEDWrite(LED_TypeDef led, GPIO_PinState state)
{
	switch (led)
	{
	case LED_STATUS:
		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, state);
		break;
	case LED_ERROR:
		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, state);
		break;
	case LED_NUCLEO:
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, state);
		break;
	}
}

void GPIO_LEDToggle(LED_TypeDef led)
{
	switch (led)
	{
	case LED_STATUS:
		  HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14);
		break;
	case LED_ERROR:
		  HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_13);
		break;
	case LED_NUCLEO:
		  HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
		break;
	}
}

