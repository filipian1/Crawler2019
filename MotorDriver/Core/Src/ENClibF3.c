#include "ENClibF3.h"

volatile uint32_t period_motor_1;
volatile int32_t abs_period_motor_1;
volatile int32_t f_obr_motor_1;

volatile uint32_t period_motor_2;
volatile int32_t abs_period_motor_2;
volatile int32_t f_obr_motor_2;

volatile uint32_t period_motor_3;
volatile int32_t abs_period_motor_3;
volatile int32_t f_obr_motor_3;

volatile uint32_t AbsEnkPeriod[3];
volatile int32_t EnkPeriod[3];

/*void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	 if (htim->Instance==TIM2)
	  {
		 period_motor_1 = 0;
		 abs_period_motor_1 = 0;
	  }
	 if (htim->Instance==TIM16)
	  {
		 period_motor_2 = 0;
		 abs_period_motor_2 = 0;
	  }
	 if (htim->Instance==TIM17)
	  {
		 period_motor_3 = 0;
		 abs_period_motor_3 = 0;
	  }
}*/
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{


	 if (htim->Instance==TIM2)
		  {
		 	 AbsEnkPeriod[0]=HAL_TIM_ReadCapturedValue(&htim2, TIM_CHANNEL_2);
			 __HAL_TIM_SET_COUNTER(&htim2, 0);
			 if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15) == GPIO_PIN_SET)
			 {
				EnkPeriod[0]= AbsEnkPeriod[0];
			 }
			 else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15) == GPIO_PIN_RESET)
			 {
				 EnkPeriod[0]= (-1)*AbsEnkPeriod[0];
			 }

			 //period_motor_1 = HAL_TIM_ReadCapturedValue(&htim2, TIM_CHANNEL_2);

		  }

		 if (htim->Instance==TIM16)
			  {
			 AbsEnkPeriod[1]=HAL_TIM_ReadCapturedValue(&htim16, TIM_CHANNEL_1);
			 __HAL_TIM_SET_COUNTER(&htim16, 0);
				 if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_10) == GPIO_PIN_SET)
				 {
					 EnkPeriod[1]= AbsEnkPeriod[1];
				 }
				 else if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_10) == GPIO_PIN_RESET)
				 {
					 EnkPeriod[1] = (-1)*AbsEnkPeriod[1];
				 }

			  }

		 if (htim->Instance==TIM17)
			  {
			 AbsEnkPeriod[1]=HAL_TIM_ReadCapturedValue(&htim17, TIM_CHANNEL_1);
			 __HAL_TIM_SET_COUNTER(&htim17, 0);
				 if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_11) == GPIO_PIN_SET)
				 {
					 EnkPeriod[2]= AbsEnkPeriod[2];
				 }
				 else if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_11) == GPIO_PIN_RESET)
				 {
					 EnkPeriod[2]= (-1)*AbsEnkPeriod[2];
				 }
			  }
}

void frequency_ret(int32_t abs_period1, int32_t abs_period2, int32_t abs_period3){
	int32_t pres = 10;
	int32_t freq = 8000000;
	f_obr_motor_1 = freq*50/(abs_period1*pres*64);
	f_obr_motor_2 = freq*50/(abs_period2*pres*64);
	f_obr_motor_3 = freq*50/(abs_period3*pres*64);
}

void ENK_TIM_Init()
{
	 __HAL_RCC_GPIOF_CLK_ENABLE();
	 __HAL_RCC_GPIOC_CLK_ENABLE();
	 __HAL_RCC_GPIOB_CLK_ENABLE();
	 __HAL_RCC_GPIOA_CLK_ENABLE();

	  GPIO_InitTypeDef GPIO_InitStruct;

	   HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11|GPIO_PIN_10, GPIO_PIN_RESET);

	   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);

	   GPIO_InitStruct.Pin = GPIO_PIN_11|GPIO_PIN_10;
	   GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	   GPIO_InitStruct.Pull = GPIO_NOPULL;
	   GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	   HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	   GPIO_InitStruct.Pin = GPIO_PIN_15;
	   GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	   GPIO_InitStruct.Pull = GPIO_NOPULL;
	   GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	   HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  	HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_2);
   	HAL_TIM_IC_Start_IT(&htim16, TIM_CHANNEL_1);
   	HAL_TIM_IC_Start_IT(&htim17, TIM_CHANNEL_1);
   	__HAL_TIM_ENABLE_IT(&htim2, TIM_IT_UPDATE);
   	__HAL_TIM_ENABLE_IT(&htim16, TIM_IT_UPDATE);
   	__HAL_TIM_ENABLE_IT(&htim17, TIM_IT_UPDATE);
}

/*
void ENC_Init()
{
	  TIM_ClockConfigTypeDef sClockSourceConfig;
	  TIM_MasterConfigTypeDef sMasterConfig;
	  TIM_IC_InitTypeDef sConfigIC;

	  htim2.Instance = TIM2;
	  htim2.Init.Prescaler = 10;
	  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
	  htim2.Init.Period = 0xFFFF;
	  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
	  {
	    _Error_Handler(__FILE__, __LINE__);
	  }

	  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
	  {
	    _Error_Handler(__FILE__, __LINE__);
	  }

	  if (HAL_TIM_IC_Init(&htim2) != HAL_OK)
	  {
	    _Error_Handler(__FILE__, __LINE__);
	  }

	  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_ENABLE;
	  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
	  {
	    _Error_Handler(__FILE__, __LINE__);
	  }

	  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
	  sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
	  sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
	  sConfigIC.ICFilter = 15;
	  if (HAL_TIM_IC_ConfigChannel(&htim2, &sConfigIC, TIM_CHANNEL_2) != HAL_OK)
	  {
	    _Error_Handler(__FILE__, __LINE__);
	  }


	  GPIO_InitTypeDef GPIO_InitStruct;

	   //GPIO Ports Clock Enable
	 __HAL_RCC_GPIOB_CLK_ENABLE();
	  __HAL_RCC_GPIOA_CLK_ENABLE();

	//  Configure GPIO pin Output Level
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);

	  //Configure GPIO pin : PB13
	  GPIO_InitStruct.Pin = GPIO_PIN_13;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	  //Configure GPIO pin : PA15
	  GPIO_InitStruct.Pin = GPIO_PIN_15;
	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	  HAL_TIM_Base_Start_IT(&htim2);
	  HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_1);
	  HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_2);
	  __HAL_TIM_ENABLE_IT(&htim2, TIM_IT_UPDATE);
}

*/
