/*
 * CANlibF4.c
 *
 *  Created on: 03.12.2018
 *      Author: Adam
 */
#include "CANlibF4.h"


void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{

	 HAL_CAN_GetRxMessage(&hcan1, CAN_RX_FIFO0  , &CAN_RxHeader, CAN_RxMsg);
	 COM_RunCanAction();
	 GPIO_LEDToggle(LED_STATUS);
	 GPIO_LEDToggle(LED_ERROR);
}

void HAL_CAN_RxFifo1MsgPendingCallback(CAN_HandleTypeDef *hcan)
{

	 HAL_CAN_GetRxMessage(&hcan1,  CAN_RX_FIFO1, &CAN_RxHeader, CAN_RxMsg);
	//GPIO_LEDWrite(LED_ERROR);
}

void CAN_Init()
{


	  CAN_FilterTypeDef  sFilterConfig;

	  hcan1.Instance = CAN1;
	  hcan1.Init.Prescaler = 5;
	  hcan1.Init.Mode = CAN_MODE_NORMAL;
	  hcan1.Init.SyncJumpWidth = CAN_SJW_1TQ;
	  hcan1.Init.TimeSeg1 = CAN_BS1_9TQ;
	  hcan1.Init.TimeSeg2 = CAN_BS2_8TQ;
	  hcan1.Init.TimeTriggeredMode = DISABLE;
	  hcan1.Init.AutoBusOff = DISABLE;
	  hcan1.Init.AutoWakeUp = DISABLE;
	  hcan1.Init.AutoRetransmission =DISABLE;
	  hcan1.Init.ReceiveFifoLocked = DISABLE;
	  hcan1.Init.TransmitFifoPriority = DISABLE;
	  if (HAL_CAN_Init(&hcan1) != HAL_OK)
	  {
	    _Error_Handler(__FILE__, __LINE__);
	  }

	  sFilterConfig.FilterBank = 0;
	    sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
	    sFilterConfig.FilterScale = CAN_FILTERSCALE_16BIT;
	    sFilterConfig.FilterIdHigh = 0x0000;
	    sFilterConfig.FilterIdLow = 0x0000;
	    sFilterConfig.FilterMaskIdHigh = 0x0000;
	    sFilterConfig.FilterMaskIdLow = 0x0000;
	    sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;
	    sFilterConfig.FilterActivation = ENABLE;
	    sFilterConfig.SlaveStartFilterBank = 0;

	    if (HAL_CAN_ConfigFilter(&hcan1, &sFilterConfig) != HAL_OK)
	    {
	      /* Filter configuration Error */
	      Error_Handler();
	    }


	  HAL_CAN_Start(&hcan1);


	if (HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING)!=HAL_OK)
	  {
		  Error_Handler();
	  }
	  if (HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO1_MSG_PENDING)!=HAL_OK)
		  {
			  Error_Handler();
		  }
	 /* HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_FULL);
	  HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO1_FULL);*/


	  dane[0]=15;
	  dane[1]=14;
	   canmsg.StdId=50;
	   canmsg.ExtId=50;
	   canmsg.IDE=CAN_ID_STD;
	   canmsg.RTR=CAN_RTR_DATA;
	   canmsg.DLC=2;
	   if (HAL_CAN_AddTxMessage(&hcan1, &canmsg, dane, &txmailbox)!=HAL_OK)
	   {
		   Error_Handler();
	   }

}
void HAL_CAN_MspInit(CAN_HandleTypeDef* hcan)
{

  GPIO_InitTypeDef GPIO_InitStruct;
  if(hcan->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspInit 0 */

  /* USER CODE END CAN1_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_CAN1_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    /**CAN1 GPIO Configuration
    PB8     ------> CAN1_RX
    PB9     ------> CAN1_TX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_CAN1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* CAN1 interrupt Init */
    HAL_NVIC_SetPriority(CAN1_RX0_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(CAN1_RX0_IRQn);
  HAL_NVIC_SetPriority(CAN1_RX1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(CAN1_RX1_IRQn);
  /* USER CODE BEGIN CAN1_MspInit 1 */

  /* USER CODE END CAN1_MspInit 1 */
  }

}

void HAL_CAN_MspDeInit(CAN_HandleTypeDef* hcan)
{

  if(hcan->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspDeInit 0 */

  /* USER CODE END CAN1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_CAN1_CLK_DISABLE();

    /**CAN1 GPIO Configuration
    PB8     ------> CAN1_RX
    PB9     ------> CAN1_TX
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_8|GPIO_PIN_9);

    /* CAN1 interrupt DeInit */
    HAL_NVIC_DisableIRQ(CAN1_RX0_IRQn);
    HAL_NVIC_DisableIRQ(CAN1_RX1_IRQn);
  /* USER CODE BEGIN CAN1_MspDeInit 1 */

  /* USER CODE END CAN1_MspDeInit 1 */
  }

}

