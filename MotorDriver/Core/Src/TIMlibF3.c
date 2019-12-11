/*

 * TIMlibF3.c
 *
 *  Created on: 11.01.2019
 *      Author: Adam

#include "TIMlibF3.h"

Do enkoderow

void ENK_TIM_Init()
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
	  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
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


	  tim16


	  htim16.Instance = TIM16;
	  htim16.Init.Prescaler = 10;
	  htim16.Init.CounterMode = TIM_COUNTERMODE_UP;
	  htim16.Init.Period = 0xFFFF;
	  htim16.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	  htim16.Init.RepetitionCounter = 0;
	  htim16.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	  if (HAL_TIM_Base_Init(&htim16) != HAL_OK)
	  {
	    _Error_Handler(__FILE__, __LINE__);
	  }

	  if (HAL_TIM_IC_Init(&htim16) != HAL_OK)
	  {
	    _Error_Handler(__FILE__, __LINE__);
	  }

	  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
	  sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
	  sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
	  sConfigIC.ICFilter = 0;
	  if (HAL_TIM_IC_ConfigChannel(&htim16, &sConfigIC, TIM_CHANNEL_1) != HAL_OK)
	  {
	    _Error_Handler(__FILE__, __LINE__);
	  }



	  htim17.Instance = TIM17;
	    htim17.Init.Prescaler = 10;
	    htim17.Init.CounterMode = TIM_COUNTERMODE_UP;
	    htim17.Init.Period = 0xFFFF;
	    htim17.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	    htim17.Init.RepetitionCounter = 0;
	    htim17.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	    if (HAL_TIM_Base_Init(&htim17) != HAL_OK)
	    {
	      _Error_Handler(__FILE__, __LINE__);
	    }

	    if (HAL_TIM_IC_Init(&htim17) != HAL_OK)
	    {
	      _Error_Handler(__FILE__, __LINE__);
	    }

	    sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
	    sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
	    sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
	    sConfigIC.ICFilter = 0;
	    if (HAL_TIM_IC_ConfigChannel(&htim17, &sConfigIC, TIM_CHANNEL_1) != HAL_OK)
	    {
	      _Error_Handler(__FILE__, __LINE__);
	    }


	   //ENK TIMERS START
	    	HAL_TIM_Base_Start(&htim2);
	    	HAL_TIM_Base_Start(&htim16);
	    	HAL_TIM_Base_Start(&htim17);
	    	HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_2);
	    	HAL_TIM_IC_Start_IT(&htim16, TIM_CHANNEL_1);
	    	HAL_TIM_IC_Start_IT(&htim17, TIM_CHANNEL_1);
	    	__HAL_TIM_ENABLE_IT(&htim2, TIM_IT_UPDATE);
	    	__HAL_TIM_ENABLE_IT(&htim16, TIM_IT_UPDATE);
	    	__HAL_TIM_ENABLE_IT(&htim17, TIM_IT_UPDATE);



}
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{

	 if (htim->Instance==TIM2)
		  {
			 if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15) == GPIO_PIN_SET)
			 {
				 abs_period_motor_1 = period_motor_1;
			 }
			 else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15) == RESET)
			 {
				 abs_period_motor_1 = - period_motor_1;
			 }
			 __HAL_TIM_SET_COUNTER(&htim2, 0);
			 period_motor_1 = HAL_TIM_ReadCapturedValue(&htim2, TIM_CHANNEL_2);

		  }

		 if (htim->Instance==TIM16)
			  {
				 if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_10) == SET)
				 {
					 abs_period_motor_2 = period_motor_2;
				 }
				 else if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_10) == RESET)
				 {
					 abs_period_motor_2 = - period_motor_2;
				 }
				 __HAL_TIM_SET_COUNTER(&htim16, 0);
				 period_motor_2 = HAL_TIM_ReadCapturedValue(&htim16, TIM_CHANNEL_1);

			  }

		 if (htim->Instance==TIM17)
			  {
				 if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_11) == SET)
				 {
					 abs_period_motor_3 = period_motor_3;
				 }
				 else if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_11) == RESET)
				 {
					 abs_period_motor_3 = - period_motor_3;
				 }
				 __HAL_TIM_SET_COUNTER(&htim17, 0);
				 period_motor_3 = HAL_TIM_ReadCapturedValue(&htim17, TIM_CHANNEL_1);

			  }
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
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
}

void frequency_ret(int32_t abs_period1,int32_t abs_period2, int32_t abs_period3){
	int32_t pres = 10;
	int32_t freq = 8000000;
	f_obr_motor_1 = freq*50/(abs_period1*pres*64);
	f_obr_motor_2 = freq*50/(abs_period2*pres*64);
	f_obr_motor_3 = freq*50/(abs_period3*pres*64);
}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* htim_base)
{

	 GPIO_InitTypeDef GPIO_InitStruct;
	  if(htim_base->Instance==TIM1)
	  {
	   USER CODE BEGIN TIM1_MspInit 0

	   USER CODE END TIM1_MspInit 0
	     Peripheral clock enable
	    __HAL_RCC_TIM1_CLK_ENABLE();
	     TIM1 interrupt Init
	    HAL_NVIC_SetPriority(TIM1_UP_TIM16_IRQn, 0, 0);
	    HAL_NVIC_EnableIRQ(TIM1_UP_TIM16_IRQn);
	    HAL_NVIC_SetPriority(TIM1_TRG_COM_TIM17_IRQn, 0, 0);
	    HAL_NVIC_EnableIRQ(TIM1_TRG_COM_TIM17_IRQn);
	   USER CODE BEGIN TIM1_MspInit 1

	   USER CODE END TIM1_MspInit 1
	  }
	  else if(htim_base->Instance==TIM2)
	  {
	   USER CODE BEGIN TIM2_MspInit 0

	   USER CODE END TIM2_MspInit 0
	     Peripheral clock enable
	    __HAL_RCC_TIM2_CLK_ENABLE();

	    *TIM2 GPIO Configuration
	    PB3     ------> TIM2_CH2

	    GPIO_InitStruct.Pin = GPIO_PIN_3;
	    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	    GPIO_InitStruct.Pull = GPIO_NOPULL;
	    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	    GPIO_InitStruct.Alternate = GPIO_AF1_TIM2;
	    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	     TIM2 interrupt Init
	    HAL_NVIC_SetPriority(TIM2_IRQn, 0, 0);
	    HAL_NVIC_EnableIRQ(TIM2_IRQn);
	   USER CODE BEGIN TIM2_MspInit 1

	   USER CODE END TIM2_MspInit 1
	  }
	  else if(htim_base->Instance==TIM16)
	  {
	   USER CODE BEGIN TIM16_MspInit 0

	   USER CODE END TIM16_MspInit 0
	     Peripheral clock enable
	    __HAL_RCC_TIM16_CLK_ENABLE();

	    *TIM16 GPIO Configuration
	    PB4     ------> TIM16_CH1

	    GPIO_InitStruct.Pin = GPIO_PIN_4;
	    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	    GPIO_InitStruct.Pull = GPIO_NOPULL;
	    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	    GPIO_InitStruct.Alternate = GPIO_AF1_TIM16;
	    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	     TIM16 interrupt Init
	    HAL_NVIC_SetPriority(TIM1_UP_TIM16_IRQn, 0, 0);
	    HAL_NVIC_EnableIRQ(TIM1_UP_TIM16_IRQn);
	   USER CODE BEGIN TIM16_MspInit 1

	   USER CODE END TIM16_MspInit 1
	  }
	  else if(htim_base->Instance==TIM17)
	  {
	   USER CODE BEGIN TIM17_MspInit 0

	   USER CODE END TIM17_MspInit 0
	     Peripheral clock enable
	    __HAL_RCC_TIM17_CLK_ENABLE();

	    *TIM17 GPIO Configuration
	    PB5     ------> TIM17_CH1

	    GPIO_InitStruct.Pin = GPIO_PIN_5;
	    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	    GPIO_InitStruct.Pull = GPIO_NOPULL;
	    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	    GPIO_InitStruct.Alternate = GPIO_AF10_TIM17;
	    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	     TIM17 interrupt Init
	    HAL_NVIC_SetPriority(TIM1_TRG_COM_TIM17_IRQn, 0, 0);
	    HAL_NVIC_EnableIRQ(TIM1_TRG_COM_TIM17_IRQn);
	   USER CODE BEGIN TIM17_MspInit 1

	   USER CODE END TIM17_MspInit 1
	  }
}

void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef* htim_pwm)
{

  if(htim_pwm->Instance==TIM15)
  {
   USER CODE BEGIN TIM15_MspInit 0

   USER CODE END TIM15_MspInit 0
     Peripheral clock enable
    __HAL_RCC_TIM15_CLK_ENABLE();
   USER CODE BEGIN TIM15_MspInit 1

   USER CODE END TIM15_MspInit 1
  }

}

void HAL_TIM_MspPostInit(TIM_HandleTypeDef* htim)
{

  GPIO_InitTypeDef GPIO_InitStruct;
  if(htim->Instance==TIM1)
  {
   USER CODE BEGIN TIM1_MspPostInit 0

   USER CODE END TIM1_MspPostInit 0
    *TIM1 GPIO Configuration
    PC2     ------> TIM1_CH3
    PC3     ------> TIM1_CH4
    PA8     ------> TIM1_CH1
    PA9     ------> TIM1_CH2

    GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF2_TIM1;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF6_TIM1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

   USER CODE BEGIN TIM1_MspPostInit 1

   USER CODE END TIM1_MspPostInit 1
  }
  else if(htim->Instance==TIM15)
  {
   USER CODE BEGIN TIM15_MspPostInit 0

   USER CODE END TIM15_MspPostInit 0

    *TIM15 GPIO Configuration
    PA2     ------> TIM15_CH1
    PA3     ------> TIM15_CH2

    GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF9_TIM15;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

   USER CODE BEGIN TIM15_MspPostInit 1

   USER CODE END TIM15_MspPostInit 1
  }

}

void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* htim_base)
{

	 if(htim_base->Instance==TIM1)
	  {
	   USER CODE BEGIN TIM1_MspDeInit 0

	   USER CODE END TIM1_MspDeInit 0
	     Peripheral clock disable
	    __HAL_RCC_TIM1_CLK_DISABLE();

	     TIM1 interrupt DeInit
	   USER CODE BEGIN TIM1:TIM1_UP_TIM16_IRQn disable
	    *
	    * Uncomment the line below to disable the "TIM1_UP_TIM16_IRQn" interrupt
	    * Be aware, disabling shared interrupt may affect other IPs

	     HAL_NVIC_DisableIRQ(TIM1_UP_TIM16_IRQn);
	   USER CODE END TIM1:TIM1_UP_TIM16_IRQn disable

	   USER CODE BEGIN TIM1:TIM1_TRG_COM_TIM17_IRQn disable
	    *
	    * Uncomment the line below to disable the "TIM1_TRG_COM_TIM17_IRQn" interrupt
	    * Be aware, disabling shared interrupt may affect other IPs

	     HAL_NVIC_DisableIRQ(TIM1_TRG_COM_TIM17_IRQn);
	   USER CODE END TIM1:TIM1_TRG_COM_TIM17_IRQn disable

	   USER CODE BEGIN TIM1_MspDeInit 1

	   USER CODE END TIM1_MspDeInit 1
	  }
	  else if(htim_base->Instance==TIM2)
	  {
	   USER CODE BEGIN TIM2_MspDeInit 0

	   USER CODE END TIM2_MspDeInit 0
	     Peripheral clock disable
	    __HAL_RCC_TIM2_CLK_DISABLE();

	    *TIM2 GPIO Configuration
	    PB3     ------> TIM2_CH2

	    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_3);

	     TIM2 interrupt DeInit
	    HAL_NVIC_DisableIRQ(TIM2_IRQn);
	   USER CODE BEGIN TIM2_MspDeInit 1

	   USER CODE END TIM2_MspDeInit 1
	  }
	  else if(htim_base->Instance==TIM16)
	  {
	   USER CODE BEGIN TIM16_MspDeInit 0

	   USER CODE END TIM16_MspDeInit 0
	     Peripheral clock disable
	    __HAL_RCC_TIM16_CLK_DISABLE();

	    *TIM16 GPIO Configuration
	    PB4     ------> TIM16_CH1

	    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_4);

	     TIM16 interrupt DeInit
	   USER CODE BEGIN TIM16:TIM1_UP_TIM16_IRQn disable
	    *
	    * Uncomment the line below to disable the "TIM1_UP_TIM16_IRQn" interrupt
	    * Be aware, disabling shared interrupt may affect other IPs

	     HAL_NVIC_DisableIRQ(TIM1_UP_TIM16_IRQn);
	   USER CODE END TIM16:TIM1_UP_TIM16_IRQn disable

	   USER CODE BEGIN TIM16_MspDeInit 1

	   USER CODE END TIM16_MspDeInit 1
	  }
	  else if(htim_base->Instance==TIM17)
	  {
	   USER CODE BEGIN TIM17_MspDeInit 0

	   USER CODE END TIM17_MspDeInit 0
	     Peripheral clock disable
	    __HAL_RCC_TIM17_CLK_DISABLE();

	    *TIM17 GPIO Configuration
	    PB5     ------> TIM17_CH1

	    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_5);

	     TIM17 interrupt DeInit
	   USER CODE BEGIN TIM17:TIM1_TRG_COM_TIM17_IRQn disable
	    *
	    * Uncomment the line below to disable the "TIM1_TRG_COM_TIM17_IRQn" interrupt
	    * Be aware, disabling shared interrupt may affect other IPs

	     HAL_NVIC_DisableIRQ(TIM1_TRG_COM_TIM17_IRQn);
	   USER CODE END TIM17:TIM1_TRG_COM_TIM17_IRQn disable

	   USER CODE BEGIN TIM17_MspDeInit 1

	   USER CODE END TIM17_MspDeInit 1
	  }
}

void HAL_TIM_PWM_MspDeInit(TIM_HandleTypeDef* htim_pwm)
{

  if(htim_pwm->Instance==TIM15)
  {
   USER CODE BEGIN TIM15_MspDeInit 0

   USER CODE END TIM15_MspDeInit 0
     Peripheral clock disable
    __HAL_RCC_TIM15_CLK_DISABLE();
   USER CODE BEGIN TIM15_MspDeInit 1

   USER CODE END TIM15_MspDeInit 1
  }

}
*/

#include "TIMlibF3.h"

/*volatile uint32_t period_motor_1;
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


/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim15;
TIM_HandleTypeDef htim16;
TIM_HandleTypeDef htim17;

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
}

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

void frequency_ret(int32_t abs_period1,int32_t abs_period2, int32_t abs_period3){
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

   //ENK TIMERS START

  	HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_2);
   	HAL_TIM_IC_Start_IT(&htim16, TIM_CHANNEL_1);
   	HAL_TIM_IC_Start_IT(&htim17, TIM_CHANNEL_1);
   	__HAL_TIM_ENABLE_IT(&htim2, TIM_IT_UPDATE);
   	__HAL_TIM_ENABLE_IT(&htim16, TIM_IT_UPDATE);
   	__HAL_TIM_ENABLE_IT(&htim17, TIM_IT_UPDATE);



}*/
void MX_TIM1_Init(void)
{
  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;
  TIM_OC_InitTypeDef sConfigOC;
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig;

  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 71;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 999;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  if (HAL_TIM_PWM_Init(&htim1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.BreakFilter = 0;
  sBreakDeadTimeConfig.Break2State = TIM_BREAK2_DISABLE;
  sBreakDeadTimeConfig.Break2Polarity = TIM_BREAK2POLARITY_HIGH;
  sBreakDeadTimeConfig.Break2Filter = 0;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  HAL_TIM_MspPostInit(&htim1);

}
/* TIM2 init function */
void MX_TIM2_Init(void)
{
  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;
  TIM_IC_InitTypeDef sConfigIC;

  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 10;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 65535;
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
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
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

}
/* TIM15 init function */
void MX_TIM15_Init(void)
{
  TIM_MasterConfigTypeDef sMasterConfig;
  TIM_OC_InitTypeDef sConfigOC;
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig;

  htim15.Instance = TIM15;
  htim15.Init.Prescaler = 71;
  htim15.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim15.Init.Period = 999;
  htim15.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim15.Init.RepetitionCounter = 0;
  htim15.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim15) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim15, &sMasterConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_PWM_ConfigChannel(&htim15, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  if (HAL_TIM_PWM_ConfigChannel(&htim15, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.BreakFilter = 0;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim15, &sBreakDeadTimeConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  HAL_TIM_MspPostInit(&htim15);

}
/* TIM16 init function */

void MX_TIM16_Init(void)
{

  TIM_IC_InitTypeDef sConfigIC;

  htim16.Instance = TIM16;
  htim16.Init.Prescaler = 10;
  htim16.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim16.Init.Period = 0xFFFF;
  htim16.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim16.Init.RepetitionCounter = 0;
  htim16.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim16) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  if (HAL_TIM_IC_Init(&htim16) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
  sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
  sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
  sConfigIC.ICFilter = 0;
  if (HAL_TIM_IC_ConfigChannel(&htim16, &sConfigIC, TIM_CHANNEL_1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* TIM17 init function */
void MX_TIM17_Init(void)
{

  TIM_IC_InitTypeDef sConfigIC;

  htim17.Instance = TIM17;
  htim17.Init.Prescaler = 10;
  htim17.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim17.Init.Period = 0xFFFF;
  htim17.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim17.Init.RepetitionCounter = 0;
  htim17.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim17) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  if (HAL_TIM_IC_Init(&htim17) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
  sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
  sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
  sConfigIC.ICFilter = 0;
  if (HAL_TIM_IC_ConfigChannel(&htim17, &sConfigIC, TIM_CHANNEL_1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}


void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* htim_base)
{

  GPIO_InitTypeDef GPIO_InitStruct;
  if(htim_base->Instance==TIM1)
  {
  /* USER CODE BEGIN TIM1_MspInit 0 */

  /* USER CODE END TIM1_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_TIM1_CLK_ENABLE();
    /* TIM1 interrupt Init */
    HAL_NVIC_SetPriority(TIM1_UP_TIM16_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(TIM1_UP_TIM16_IRQn);
    HAL_NVIC_SetPriority(TIM1_TRG_COM_TIM17_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(TIM1_TRG_COM_TIM17_IRQn);
  /* USER CODE BEGIN TIM1_MspInit 1 */

  /* USER CODE END TIM1_MspInit 1 */
  }
  else if(htim_base->Instance==TIM2)
  {
  /* USER CODE BEGIN TIM2_MspInit 0 */

  /* USER CODE END TIM2_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_TIM2_CLK_ENABLE();

    /**TIM2 GPIO Configuration
    PB3     ------> TIM2_CH2
    */
    GPIO_InitStruct.Pin = GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF1_TIM2;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* TIM2 interrupt Init */
    HAL_NVIC_SetPriority(TIM2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(TIM2_IRQn);
  /* USER CODE BEGIN TIM2_MspInit 1 */

  /* USER CODE END TIM2_MspInit 1 */
  }
  else if(htim_base->Instance==TIM16)
  {
  /* USER CODE BEGIN TIM16_MspInit 0 */

  /* USER CODE END TIM16_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_TIM16_CLK_ENABLE();

    /**TIM16 GPIO Configuration
    PB4     ------> TIM16_CH1
    */
    GPIO_InitStruct.Pin = GPIO_PIN_4;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF1_TIM16;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* TIM16 interrupt Init */
    HAL_NVIC_SetPriority(TIM1_UP_TIM16_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(TIM1_UP_TIM16_IRQn);
  /* USER CODE BEGIN TIM16_MspInit 1 */

  /* USER CODE END TIM16_MspInit 1 */
  }
  else if(htim_base->Instance==TIM17)
  {
  /* USER CODE BEGIN TIM17_MspInit 0 */

  /* USER CODE END TIM17_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_TIM17_CLK_ENABLE();

    /**TIM17 GPIO Configuration
    PB5     ------> TIM17_CH1
    */
    GPIO_InitStruct.Pin = GPIO_PIN_5;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF10_TIM17;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* TIM17 interrupt Init */
    HAL_NVIC_SetPriority(TIM1_TRG_COM_TIM17_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(TIM1_TRG_COM_TIM17_IRQn);
  /* USER CODE BEGIN TIM17_MspInit 1 */

  /* USER CODE END TIM17_MspInit 1 */
  }

}

void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef* htim_pwm)
{

  if(htim_pwm->Instance==TIM15)
  {
  /* USER CODE BEGIN TIM15_MspInit 0 */

  /* USER CODE END TIM15_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_TIM15_CLK_ENABLE();
  /* USER CODE BEGIN TIM15_MspInit 1 */

  /* USER CODE END TIM15_MspInit 1 */
  }

}

void HAL_TIM_MspPostInit(TIM_HandleTypeDef* htim)
{

  GPIO_InitTypeDef GPIO_InitStruct;
  if(htim->Instance==TIM1)
  {
  /* USER CODE BEGIN TIM1_MspPostInit 0 */

  /* USER CODE END TIM1_MspPostInit 0 */
    /**TIM1 GPIO Configuration
    PC2     ------> TIM1_CH3
    PC3     ------> TIM1_CH4
    PA8     ------> TIM1_CH1
    PA9     ------> TIM1_CH2
    */
    GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF2_TIM1;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF6_TIM1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN TIM1_MspPostInit 1 */

  /* USER CODE END TIM1_MspPostInit 1 */
  }
  else if(htim->Instance==TIM15)
  {
  /* USER CODE BEGIN TIM15_MspPostInit 0 */

  /* USER CODE END TIM15_MspPostInit 0 */

    /**TIM15 GPIO Configuration
    PA2     ------> TIM15_CH1
    PA3     ------> TIM15_CH2
    */
    GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF9_TIM15;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN TIM15_MspPostInit 1 */

  /* USER CODE END TIM15_MspPostInit 1 */
  }

}

void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* htim_base)
{

  if(htim_base->Instance==TIM1)
  {
  /* USER CODE BEGIN TIM1_MspDeInit 0 */

  /* USER CODE END TIM1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM1_CLK_DISABLE();

    /* TIM1 interrupt DeInit */
  /* USER CODE BEGIN TIM1:TIM1_UP_TIM16_IRQn disable */
    /**
    * Uncomment the line below to disable the "TIM1_UP_TIM16_IRQn" interrupt
    * Be aware, disabling shared interrupt may affect other IPs
    */
    /* HAL_NVIC_DisableIRQ(TIM1_UP_TIM16_IRQn); */
  /* USER CODE END TIM1:TIM1_UP_TIM16_IRQn disable */

  /* USER CODE BEGIN TIM1:TIM1_TRG_COM_TIM17_IRQn disable */
    /**
    * Uncomment the line below to disable the "TIM1_TRG_COM_TIM17_IRQn" interrupt
    * Be aware, disabling shared interrupt may affect other IPs
    */
    /* HAL_NVIC_DisableIRQ(TIM1_TRG_COM_TIM17_IRQn); */
  /* USER CODE END TIM1:TIM1_TRG_COM_TIM17_IRQn disable */

  /* USER CODE BEGIN TIM1_MspDeInit 1 */

  /* USER CODE END TIM1_MspDeInit 1 */
  }
  else if(htim_base->Instance==TIM2)
  {
  /* USER CODE BEGIN TIM2_MspDeInit 0 */

  /* USER CODE END TIM2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM2_CLK_DISABLE();

    /**TIM2 GPIO Configuration
    PB3     ------> TIM2_CH2
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_3);

    /* TIM2 interrupt DeInit */
    HAL_NVIC_DisableIRQ(TIM2_IRQn);
  /* USER CODE BEGIN TIM2_MspDeInit 1 */

  /* USER CODE END TIM2_MspDeInit 1 */
  }
  else if(htim_base->Instance==TIM16)
  {
  /* USER CODE BEGIN TIM16_MspDeInit 0 */

  /* USER CODE END TIM16_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM16_CLK_DISABLE();

    /**TIM16 GPIO Configuration
    PB4     ------> TIM16_CH1
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_4);

    /* TIM16 interrupt DeInit */
  /* USER CODE BEGIN TIM16:TIM1_UP_TIM16_IRQn disable */
    /**
    * Uncomment the line below to disable the "TIM1_UP_TIM16_IRQn" interrupt
    * Be aware, disabling shared interrupt may affect other IPs
    */
    /* HAL_NVIC_DisableIRQ(TIM1_UP_TIM16_IRQn); */
  /* USER CODE END TIM16:TIM1_UP_TIM16_IRQn disable */

  /* USER CODE BEGIN TIM16_MspDeInit 1 */

  /* USER CODE END TIM16_MspDeInit 1 */
  }
  else if(htim_base->Instance==TIM17)
  {
  /* USER CODE BEGIN TIM17_MspDeInit 0 */

  /* USER CODE END TIM17_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM17_CLK_DISABLE();

    /**TIM17 GPIO Configuration
    PB5     ------> TIM17_CH1
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_5);

    /* TIM17 interrupt DeInit */
  /* USER CODE BEGIN TIM17:TIM1_TRG_COM_TIM17_IRQn disable */
    /**
    * Uncomment the line below to disable the "TIM1_TRG_COM_TIM17_IRQn" interrupt
    * Be aware, disabling shared interrupt may affect other IPs
    */
    /* HAL_NVIC_DisableIRQ(TIM1_TRG_COM_TIM17_IRQn); */
  /* USER CODE END TIM17:TIM1_TRG_COM_TIM17_IRQn disable */

  /* USER CODE BEGIN TIM17_MspDeInit 1 */

  /* USER CODE END TIM17_MspDeInit 1 */
  }

}

void HAL_TIM_PWM_MspDeInit(TIM_HandleTypeDef* htim_pwm)
{

  if(htim_pwm->Instance==TIM15)
  {
  /* USER CODE BEGIN TIM15_MspDeInit 0 */

  /* USER CODE END TIM15_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM15_CLK_DISABLE();
  /* USER CODE BEGIN TIM15_MspDeInit 1 */

  /* USER CODE END TIM15_MspDeInit 1 */
  }

}
