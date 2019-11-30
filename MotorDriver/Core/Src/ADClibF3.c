#include "ADClibF3.h"

//parametry pomiarow

//sample rate, przy systick 1kHz to jest okres probkowania w ms

uint16_t ADC_SampleRate=200;

void SendADCData();

void ADC_Function()
{
	static uint16_t meas_timer=0;
	if (meas_timer==0)
	{
		SendADCData();
	}
	meas_timer++;
	if (meas_timer==ADC_SampleRate) meas_timer=0;
}

void SendADCData()
{
	uint8_t buff[8];
	buff [0] = ADC_MeasRaw[0] & 0xFF;
	buff [1] = (ADC_MeasRaw[0] >> 8) & 0xFF;
	buff [2] = ADC_MeasRaw[1] & 0xFF;
	buff [3] = (ADC_MeasRaw[1] >> 8) & 0xFF;
	buff [4] = ADC_MeasRaw[2] & 0xFF;
	buff [5] = (ADC_MeasRaw[2] >> 8) & 0xFF;
	CAN_Header.StdId=100;//trzeba zmienic adresy ramek
	CAN_Header.DLC=6;
	//HAL_CAN_AddTxMessage(&hcan,&CAN_Header,buff,&CAN_TxMailbox);

	buff [0] = ADC_MeasRaw[3] & 0xFF;
	buff [1] = (ADC_MeasRaw[3] >> 8) & 0xFF;
	buff [2] = ADC_MeasRaw[4] & 0xFF;
	buff [3] = (ADC_MeasRaw[4] >> 8) & 0xFF;
	buff [4] = ADC_MeasRaw[5] & 0xFF;
	buff [5] = (ADC_MeasRaw[5] >> 8) & 0xFF;
	CAN_Header.StdId=101;//trzeba znalezc adresy ramek
	//HAL_CAN_AddTxMessage(&hcan,&CAN_Header,buff,&CAN_TxMailbox);

}
void ADC_DMAInitialisation(void)
{
  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel1_IRQn interrupt configuration */
 //HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 0, 0);
 // HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);

}

void ADC_Initialisation()
{

	ADC_DMAInitialisation();

	 ADC_ChannelConfTypeDef sConfig;

	    /**Common config
	    */
	  hadc1.Instance = ADC1;
	  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
	  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
	  hadc1.Init.ScanConvMode = ADC_SCAN_ENABLE;
	  hadc1.Init.ContinuousConvMode = ENABLE;
	  hadc1.Init.DiscontinuousConvMode = DISABLE;
	  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	  hadc1.Init.NbrOfConversion = 6;
	  hadc1.Init.DMAContinuousRequests = ENABLE;
	  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
	  hadc1.Init.LowPowerAutoWait = DISABLE;
	  hadc1.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;
	  if (HAL_ADC_Init(&hadc1) != HAL_OK)
	  {
	    _Error_Handler(__FILE__, __LINE__);
	  }

	    /** Motor1_Temperature - Configure ADC channel ,rank and SAMPLETIME */
	  sConfig.Channel = ADC_CHANNEL_10;
	  sConfig.Rank = ADC_REGULAR_RANK_1;
	  sConfig.SingleDiff = ADC_SINGLE_ENDED;
	  sConfig.SamplingTime = ADC_SAMPLETIME_4CYCLES_5;
	  sConfig.OffsetNumber = ADC_OFFSET_NONE;
	  sConfig.Offset = 0;
	  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
	  {
	    _Error_Handler(__FILE__, __LINE__);
	  }

	  /** Motor2_Temperature - Configure ADC channel ,rank and SAMPLETIME */
	  sConfig.Channel = ADC_CHANNEL_11;
	  sConfig.Rank = ADC_REGULAR_RANK_2;
	  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
	  {
	    _Error_Handler(__FILE__, __LINE__);
	  }

	  /** Motor3_Temperature - Configure ADC channel ,rank and SAMPLETIME */
	  sConfig.Channel = ADC_CHANNEL_12;
	  sConfig.Rank = ADC_REGULAR_RANK_3;
	  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
	  {
	    _Error_Handler(__FILE__, __LINE__);
	  }
	  /** Motor3_Temperature - Configure ADC channel ,rank and SAMPLETIME */
	  	  sConfig.Channel = ADC_CHANNEL_5;
	  	  sConfig.Rank = ADC_REGULAR_RANK_4;
	  	  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
	  	  {
	  	    _Error_Handler(__FILE__, __LINE__);
	  	  }
	  	/** Motor3_Temperature - Configure ADC channel ,rank and SAMPLETIME */
	  		  sConfig.Channel = ADC_CHANNEL_13;
	  		  sConfig.Rank = ADC_REGULAR_RANK_5;
	  		  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
	  		  {
	  		    _Error_Handler(__FILE__, __LINE__);
	  		  }
	  		/** Motor3_Temperature - Configure ADC channel ,rank and SAMPLETIME */
	  			  sConfig.Channel = ADC_CHANNEL_6;
	  			  sConfig.Rank = ADC_REGULAR_RANK_6;
	  			  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
	  			  {
	  			    _Error_Handler(__FILE__, __LINE__);
	  			  }
	  			HAL_ADC_Start_DMA(&hadc1, ADC_MeasRaw, 6);// Temperature DMA_Stream[0-2] and Engine current feedback DMA_Stream[3-5]

}

void HAL_ADC_MspInit(ADC_HandleTypeDef* hadc)
{

  GPIO_InitTypeDef GPIO_InitStruct;
  if(hadc->Instance==ADC1)
  {
  /* USER CODE BEGIN ADC1_MspInit 0 */

  /* USER CODE END ADC1_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_ADC1_CLK_ENABLE();

    /**ADC1 GPIO Configuration
    PA6     ------> ADC1_IN10
    PB0     ------> ADC1_IN11
    PB1     ------> ADC1_IN12
    */
    GPIO_InitStruct.Pin = GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* ADC1 DMA Init */
    /* ADC1 Init */
    hdma_adc1.Instance = DMA1_Channel1;
    hdma_adc1.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_adc1.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_adc1.Init.MemInc = DMA_MINC_ENABLE;
    hdma_adc1.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    hdma_adc1.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
    hdma_adc1.Init.Mode = DMA_CIRCULAR;
    hdma_adc1.Init.Priority = DMA_PRIORITY_LOW;
    if (HAL_DMA_Init(&hdma_adc1) != HAL_OK)
    {
      _Error_Handler(__FILE__, __LINE__);
    }

    __HAL_LINKDMA(hadc,DMA_Handle,hdma_adc1);

  /* USER CODE BEGIN ADC1_MspInit 1 */

  /* USER CODE END ADC1_MspInit 1 */
  }

}

void HAL_ADC_MspDeInit(ADC_HandleTypeDef* hadc)
{

  if(hadc->Instance==ADC1)
  {
  /* USER CODE BEGIN ADC1_MspDeInit 0 */

  /* USER CODE END ADC1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_ADC1_CLK_DISABLE();

    /**ADC1 GPIO Configuration
    PA6     ------> ADC1_IN10
    PB0     ------> ADC1_IN11
    PB1     ------> ADC1_IN12
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_6);

    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_0|GPIO_PIN_1);

    /* ADC1 DMA DeInit */
    HAL_DMA_DeInit(hadc->DMA_Handle);
  /* USER CODE BEGIN ADC1_MspDeInit 1 */

  /* USER CODE END ADC1_MspDeInit 1 */
  }

}
