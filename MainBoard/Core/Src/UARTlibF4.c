/*
 * UARTlibF4.c
 *
 *  Created on: 25.11.2018
 *      Author: Adam
 */


/* Private includes----------------------------------------------------*/
#include "UARTlibF4.h"

typedef enum
{
	DOLLAR=0,	//czeka na poczatek ramki
	FRAMETYPE,
	DATA

}GPS_StateTypedef;

GPS_StateTypedef GPS_State=0;
/* Private function prototypes-----------------------------------------*/
void UART_Encode(uint8_t rawdata[], uint8_t encodeddata[], uint8_t lenght);
void UART_Decode();
void UART2_DMAInit(void);
void UART1_DMAInit(void);
void UART_TransmitFoo();
void GPSFoo();




/* Private variables---------------------------------------------------*/
uint8_t UART_ReceivedRaw[19];
uint8_t Tx_IndexSend=0;
uint8_t Tx_IndexWrite=0;
uint8_t GPS_Odbior[120];
int kurdeweszlo = 0;
/* Exported funcions---------------------------------------------------*/

void UART2_Init(void)
{
  UART2_DMAInit();
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }
  //__HAL_UART_ENABLE_IT(&huart2, UART_IT_RXNE);
 // HAL_UART_Receive_IT(&huart2, UART_ReceivedRaw, 19);
  //HAL_UART_Receive_DMA(&huart2, UART_ReceivedRaw, 19);

}

void UART1_Init(void)
{

	  huart1.Instance = USART1;
	  huart1.Init.BaudRate = 9600;
	  huart1.Init.WordLength = UART_WORDLENGTH_8B;
	  huart1.Init.StopBits = UART_STOPBITS_1;
	  huart1.Init.Parity = UART_PARITY_NONE;
	  huart1.Init.Mode = UART_MODE_TX_RX;
	  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
	  if (HAL_UART_Init(&huart1) != HAL_OK)
	  {
	    _Error_Handler(__FILE__, __LINE__);
	  }
	  //HAL_UART_Receive_IT(&huart1,GPS_Odbior,120);
	  __HAL_UART_ENABLE_IT(&huart1, UART_IT_RXNE);
	    HAL_UART_Receive_IT(&huart1, UART_ReceivedRaw, 19);
}

Mailbox_StatusTypeDef UART2_Send(UART_MessageTypeDef msg)
{
	if (msg.lenght>ROZMIAR_RAMKI) return Mailbox_ERROR;		/*sory, max 8 znakow*/
	static uint8_t temp[16];				//miejsce na 8 znakow
	if ((Tx_IndexWrite!=MAILBOX_SIZE-1 && UART_TxMailbox[Tx_IndexWrite+1].filled!=0) || (Tx_IndexWrite==MAILBOX_SIZE-1 && UART_TxMailbox[0].filled!=0)) return Mailbox_FULL;
	if (Tx_IndexWrite==MAILBOX_SIZE-1) Tx_IndexWrite=0;
	else Tx_IndexWrite++;

	int i = Tx_IndexWrite; 		//zeby bylo latwiej
	/*# na dobry poczatek*/

	UART_TxMailbox[i].sendBuffor[0] = '#';

	/*kodowanie ID*/
	UART_Encode(&msg.ID, temp,1);
	UART_TxMailbox[i].sendBuffor[1] = temp[0];
	UART_TxMailbox[i].sendBuffor[2] = temp[1];

	/*kodowanie wiadomosci*/
	UART_Encode(msg.data, temp, msg.lenght);

	/*wazne, kopiownie, zeby nie przekazac wskaznika,
     * aby niechachy nie nadpisywac zmiennych*/
	for (int j=3;j<2*msg.lenght+3;j++)
	{
		UART_TxMailbox[i].sendBuffor[j] = temp[j-3];
	}
	for (int j=2*msg.lenght+3; j<2*ROZMIAR_RAMKI+3;j++)
	{
		UART_TxMailbox[i].sendBuffor[j] = (uint8_t) 'x';
	}
	UART_TxMailbox[i].filled=~0;
	if (huart1.gState== HAL_UART_STATE_READY)	UART_TransmitFoo();
	return Mailbox_OK;

/*	for (int i=0;i<MAILBOX_SIZE;i++)
	{
		if (UART_TxMailbox[i].filled==0)
		{


		}
	}*/

}
void UART_TransmitFoo()
{
	if (((Tx_IndexSend!=MAILBOX_SIZE-1) && UART_TxMailbox[Tx_IndexSend+1].filled!=0) || ((Tx_IndexSend==MAILBOX_SIZE-1) && UART_TxMailbox[0].filled!=0))
		{
			if (Tx_IndexSend==MAILBOX_SIZE-1) Tx_IndexSend=0;
			else Tx_IndexSend++;
			HAL_UART_Transmit_IT(&huart1,UART_TxMailbox[Tx_IndexSend].sendBuffor,19);
			UART_TxMailbox[Tx_IndexSend].filled=0;
		}
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef  *huart)
{

	if (huart->Instance==USART1)
	{
		kurdeweszlo = 1;
		GPIO_LEDWrite(LED_STATUS, GPIO_PIN_SET);
		UART_Decode();
		COM_RunUartAction();
		//HAL_UART_Receive_DMA(&huart2, UART_ReceivedRaw, 19);
		HAL_UART_Receive_IT(&huart1, UART_ReceivedRaw, 19);
	}

}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{

	if (huart->Instance==USART1)
	{
		UART_TransmitFoo();
	}

}

/*lenght odnosi sie do dlugosci rawdata*/
void UART_Encode(uint8_t rawdata[], uint8_t encodeddata[], uint8_t lenght)
{
	uint8_t temp1, temp2;
	for (int i=0;i<lenght;i++)
	{
		temp1 = rawdata[i];
		temp2 = (temp1 % 0x10);
		temp1 -= temp2;
		if (temp2 <10)
			encodeddata[2*i+1] = temp2+48;
		else
			encodeddata[2*i +1] = temp2+55;

		temp2=temp1/0x10;
		if (temp2 <10)
			encodeddata[2*i] = temp2+48;
		else
			encodeddata[2*i] = temp2+55;


	}
}
void UART_Decode()
{
	/*Test czy pierwszy jest # by sie przydal*/
	kurdeweszlo = 2;
	UART_MessageRecieved.ID = 0;

	/*Zamiana hex w ACSII na liczbe*/

	if (UART_ReceivedRaw[1]>=65)
		UART_MessageRecieved.ID += (UART_ReceivedRaw[1]-55)*0x10;
	else
		UART_MessageRecieved.ID += (UART_ReceivedRaw[1]-48)*0x10;

	if (UART_ReceivedRaw[2]>=65)
		UART_MessageRecieved.ID += (UART_ReceivedRaw[2]-55);
	else
		UART_MessageRecieved.ID += (UART_ReceivedRaw[2]-48);

	uint8_t i=3;
	uint8_t index=0;
	while (i<19 && UART_ReceivedRaw[i]!=120)			//4 - end of transmission
	{
		UART_MessageRecieved.data[index]=0;
		if (UART_ReceivedRaw[i]>=65)
			UART_MessageRecieved.data[index] += (UART_ReceivedRaw[i]-55)*0x10;
		else
			UART_MessageRecieved.data[index] += (UART_ReceivedRaw[i]-48)*0x10;
		i++;
		if (UART_ReceivedRaw[i]>=65)
			UART_MessageRecieved.data[index] += (UART_ReceivedRaw[i]-55);
		else
			UART_MessageRecieved.data[index] += (UART_ReceivedRaw[i]-48);
		i++;
		index++;
	}
	UART_MessageRecieved.lenght=index;




}
void HAL_UART_MspInit(UART_HandleTypeDef* huart)
{

  GPIO_InitTypeDef GPIO_InitStruct;
  if(huart->Instance==USART2)
  {
  /* USER CODE BEGIN USART2_MspInit 0 */

  /* USER CODE END USART2_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_USART2_CLK_ENABLE();

    /**USART2 GPIO Configuration
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

 /*    USART2 DMA Init
     USART2_RX Init*/
    hdma_usart2_rx.Instance = DMA1_Stream5;
    hdma_usart2_rx.Init.Channel = DMA_CHANNEL_4;
    hdma_usart2_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_usart2_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart2_rx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart2_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart2_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart2_rx.Init.Mode = DMA_NORMAL;
    hdma_usart2_rx.Init.Priority = DMA_PRIORITY_LOW;
    hdma_usart2_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_usart2_rx) != HAL_OK)
    {
      _Error_Handler(__FILE__, __LINE__);
    }

    __HAL_LINKDMA(huart,hdmarx,hdma_usart2_rx);

    /* USART2_TX Init*/
    hdma_usart2_tx.Instance = DMA1_Stream6;
    hdma_usart2_tx.Init.Channel = DMA_CHANNEL_4;
    hdma_usart2_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_usart2_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart2_tx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart2_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart2_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart2_tx.Init.Mode = DMA_NORMAL;
    hdma_usart2_tx.Init.Priority = DMA_PRIORITY_LOW;
    hdma_usart2_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_usart2_tx) != HAL_OK)
    {
      _Error_Handler(__FILE__, __LINE__);
    }

    __HAL_LINKDMA(huart,hdmatx,hdma_usart2_tx);

    /* USART2 interrupt Init */
    HAL_NVIC_SetPriority(USART2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART2_IRQn);

  }
    if(huart->Instance==USART1)
      {
      /* USER CODE BEGIN USART1_MspInit 0 */

      /* USER CODE END USART1_MspInit 0 */
        /* Peripheral clock enable */
        __HAL_RCC_USART1_CLK_ENABLE();

        /**USART1 GPIO Configuration
        PA9     ------> USART1_TX
        PA10     ------> USART1_RX
        */
        GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_PULLUP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        /* USART1 interrupt Init */
        HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(USART1_IRQn);
      /* USER CODE BEGIN USART1_MspInit 1 */

      /* USER CODE END USART1_MspInit 1 */
      }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* huart)
{

  if(huart->Instance==USART2)
  {
  /* USER CODE BEGIN USART2_MspDeInit 0 */

  /* USER CODE END USART2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART2_CLK_DISABLE();

    /**USART2 GPIO Configuration
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2|GPIO_PIN_3);

    /* USART2 DMA DeInit */
    HAL_DMA_DeInit(huart->hdmarx);
    HAL_DMA_DeInit(huart->hdmatx);

    /* USART2 interrupt DeInit */
    HAL_NVIC_DisableIRQ(USART2_IRQn);
  /* USER CODE BEGIN USART2_MspDeInit 1 */

  /* USER CODE END USART2_MspDeInit 1 */
  }


}
void UART2_DMAInit(void)
{
	  /* DMA controller clock enable */
	  __HAL_RCC_DMA1_CLK_ENABLE();

	  /* DMA interrupt init */
	  /* DMA1_Stream5_IRQn interrupt configuration */
	  HAL_NVIC_SetPriority(DMA1_Stream5_IRQn, 0, 0);
	  //HAL_NVIC_EnableIRQ(DMA1_Stream5_IRQn);
	  /* DMA1_Stream6_IRQn interrupt configuration */
	  HAL_NVIC_SetPriority(DMA1_Stream6_IRQn, 0, 0);
	  //HAL_NVIC_EnableIRQ(DMA1_Stream6_IRQn);
}
void UART1_DMAInit(void)
{
	  /* DMA controller clock enable */
	  __HAL_RCC_DMA2_CLK_ENABLE();

	  /* DMA interrupt init */
	  /* DMA1_Stream5_IRQn interrupt configuration */
	  HAL_NVIC_SetPriority(DMA2_Stream2_IRQn, 0, 0);
	  //HAL_NVIC_EnableIRQ(DMA2_Stream7_IRQn);
	  /* DMA1_Stream6_IRQn interrupt configuration */
	  HAL_NVIC_SetPriority(DMA2_Stream2_IRQn, 0, 0);
	  //HAL_NVIC_EnableIRQ(DMA2_Stream2_IRQn);
}

