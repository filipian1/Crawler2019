#include "TIMlibF3.h"

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


/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim15;
extern TIM_HandleTypeDef htim16;
extern TIM_HandleTypeDef htim17;

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

			 period_motor_1 = HAL_TIM_ReadCapturedValue(&htim2, TIM_CHANNEL_2);

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

void frequency_ret(){
	int32_t pres = 10;
	int32_t freq = 8000000;
	f_obr_motor_1 = freq*50/(EnkPeriod[0]*pres*64);
	f_obr_motor_2 = freq*50/(EnkPeriod[1]*pres*64);
	f_obr_motor_3 = freq*50/(EnkPeriod[2]*pres*64);
}

void ENK_TIM_Init()
{
	 __HAL_RCC_GPIOF_CLK_ENABLE();
	 __HAL_RCC_GPIOC_CLK_ENABLE();
	 __HAL_RCC_GPIOB_CLK_ENABLE();
	 __HAL_RCC_GPIOA_CLK_ENABLE();

	 /*GPIO ENABLE PIN CONFIG*/

	  GPIO_InitTypeDef GPIO_InitStruct;


	   /*Configure GPIO pin Output Level */
	   HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11|GPIO_PIN_10, GPIO_PIN_RESET);

	   /*Configure GPIO pin Output Level */
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



}
