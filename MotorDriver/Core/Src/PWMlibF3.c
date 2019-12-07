#include <PWMlibF3.h>
#include "CANlibF3.h"

void PWM_Init()
{
	 /* GPIO Ports Clock Enable */
	  __HAL_RCC_GPIOF_CLK_ENABLE();
	  __HAL_RCC_GPIOC_CLK_ENABLE();
	  __HAL_RCC_GPIOB_CLK_ENABLE();
	  __HAL_RCC_GPIOA_CLK_ENABLE();

	  /*GPIO ENABLE PIN CONFIG*/

	  GPIO_InitTypeDef GPIO_InitStruct;


   /*Configure GPIO pin Output Level */
	   HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14|GPIO_PIN_15|GPIO_PIN_6|GPIO_PIN_7, GPIO_PIN_RESET);

	   /*Configure GPIO pin Output Level */
	   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10|GPIO_PIN_11, GPIO_PIN_RESET);

	   /*Configure GPIO pins : PC14 PC15 PC6 PC7 */
	   GPIO_InitStruct.Pin = GPIO_PIN_14|GPIO_PIN_15|GPIO_PIN_6|GPIO_PIN_7;
	   GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	   GPIO_InitStruct.Pull = GPIO_NOPULL;
	   GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	   HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	   /*Configure GPIO pins : PB10 PB11 */
	   GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11;
	   GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	   GPIO_InitStruct.Pull = GPIO_NOPULL;
	   GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	   HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);


	   /*Stop Motors*/

	   HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14 | GPIO_PIN_6, GPIO_PIN_RESET);
	   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_SET);

	   HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15 | GPIO_PIN_7, GPIO_PIN_RESET);
	   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_SET);
	   /*Timers*/


	   HAL_TIM_PWM_Start(&htim15, TIM_CHANNEL_1);
	   HAL_TIM_PWM_Start(&htim15, TIM_CHANNEL_2);

	   HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	   HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
	   HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
	   HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);

}

void StartMotors(){ // Okre

	  	   HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14 | GPIO_PIN_6, GPIO_PIN_RESET);
		   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_RESET);

		   HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15 | GPIO_PIN_7, GPIO_PIN_SET);
		   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_SET);
}
void StopMotors(){
	   HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14 | GPIO_PIN_6, GPIO_PIN_SET);
	   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_SET);

	   HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15 | GPIO_PIN_7, GPIO_PIN_RESET);
	   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_RESET);
}
/*
 *
 *
 */

void PWM_Set(int16_t counter){

#ifdef LEFT_MOTORS
	if (counter>0)
	{
	TIM1->CCR3 = counter;
	TIM1->CCR4 = 0;       //motor3

	TIM1->CCR1 = 0;
	TIM1->CCR2 = counter;       //motor2

	TIM15->CCR1 = 0;
	TIM15->CCR2 = counter;			//motor1
	}
	else
	{
	TIM1->CCR3= 0;
	TIM1->CCR4 = -counter; 		//motor3

	TIM1->CCR1 = -counter;
	TIM1->CCR2 = 0;		//motor2

	TIM15->CCR1 = -counter;
	TIM15->CCR2 = 0;	//motor1
	}
#endif //LEFT_MOTORS

#ifdef RIGHT_MOTORS
	if (counter>0)
	{
	TIM1->CCR3 = counter;
	TIM1->CCR4 = 0;       //motor3

	TIM1->CCR1 = counter;
	TIM1->CCR2 = 0;       //motor2

	TIM15->CCR1 = counter;
	TIM15->CCR2 = 0;			//motor1
	}
	else
	{
	TIM1->CCR3= 0;
	TIM1->CCR4 = -counter; 		//motor3

	TIM1->CCR1 = 0;
	TIM1->CCR2 = -counter;		//motor2

	TIM15->CCR1 = 0;
	TIM15->CCR2 = -counter;	//motor1
	}
#endif //RIGHT_MOTORS
}
PWM_Calcluate(uint8_t vx, uint8_t vy){


}



/*
 * PWM_LIB.c
 *
 *  Created on: 20.11.2018
 *      Author: grzec
 */


