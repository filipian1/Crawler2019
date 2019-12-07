/*
 * UARTlibF4.h
 *
 *  Created on: 25.11.2018
 *      Author: Adam
 */

#ifndef INC_UARTLIBF4_H_
#define INC_UARTLIBF4_H_

/* Includes-----------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_dma.h"
#include "stm32f4xx_hal_uart.h"

/* Defines------------------------------------------------------------*/
#define ROZMIAR_RAMKI 8
#define MAILBOX_SIZE 15

/* Typedefs-----------------------------------------------------------*/
typedef struct
{
	uint8_t ID;
	uint8_t lenght;
	uint8_t data[8];
}UART_MessageTypeDef;

typedef enum{
	Mailbox_OK = 0,
	Mailbox_ERROR = 1,
	Mailbox_FULL = 2,


}Mailbox_StatusTypeDef;

typedef struct {
	volatile uint8_t sendBuffor[2*ROZMIAR_RAMKI + 3];
	volatile uint8_t filled;
} UART_MailboxTypeDef;


/* Exported functions prototypes---------------------------------------*/
void UART2_Init(void);
void UART1_Init(void);
Mailbox_StatusTypeDef UART2_Send(UART_MessageTypeDef msg);

/* Exported variables--------------------------------------------------*/
volatile UART_MailboxTypeDef UART_TxMailbox[MAILBOX_SIZE];

volatile UART_MessageTypeDef UART_MessageRecieved;

UART_HandleTypeDef huart2;
UART_HandleTypeDef huart1;
DMA_HandleTypeDef hdma_usart2_rx;
DMA_HandleTypeDef hdma_usart2_tx;
DMA_HandleTypeDef hdma_usart1_rx;
DMA_HandleTypeDef hdma_usart1_tx;

#endif /* INC_UARTLIBF4_H_ */
