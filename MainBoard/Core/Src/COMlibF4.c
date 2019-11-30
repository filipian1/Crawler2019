/*

 * COMMlibF4.c
 *
 *  Created on: 06.01.2019
 *      Author: Adam

       */



#include "COMlibF4.h"

void ignoreUART();
void ignoreCAN();
void transferToUart();
void transferToCan();
void SendSpeed();

uint8_t CommandListLenght;

void COM_LoadCommandList(void) {
	int i = 0;
	//Sterowanie X,Y
	commandList[i].ID = 100;
	commandList[i].length = 2;
	commandList[i].reciveCanAction = ignoreCAN;
	commandList[i].reciveUartAction = SendSpeed;
	i++;
	//Sterowanie start,stop
	commandList[i].ID = 101;
	commandList[i].length = 1;
	commandList[i].reciveCanAction = ignoreCAN;
	commandList[i].reciveUartAction = transferToCan;
	i++;
	//Zadana predkosc silników prawa
	commandList[i].ID = 102;
	commandList[i].length = 1;
	commandList[i].reciveCanAction = ignoreCAN;
	commandList[i].reciveUartAction = transferToCan;
	i++;
	//Zadana predkosc silinków lewa
	commandList[i].ID = 103;
	commandList[i].length = 1;
	commandList[i].reciveCanAction = ignoreCAN;
	commandList[i].reciveUartAction = ignoreUART;
	i++;
	//Pr silinków prawa
	commandList[i].ID = 104;
	commandList[i].length = 6;
	commandList[i].reciveCanAction = transferToUart;
	commandList[i].reciveUartAction = ignoreUART;
	i++;
	//Pr¹d silinków lewa
	commandList[i].ID = 105;
	commandList[i].length = 6;
	commandList[i].reciveCanAction = transferToUart;
	commandList[i].reciveUartAction = ignoreUART;
	i++;
	//Prêdkoœci silinków prawa
	commandList[i].ID = 106;
	commandList[i].length = 6;
	commandList[i].reciveCanAction = transferToUart;
	commandList[i].reciveUartAction = ignoreUART;
	i++;
	//Prêdkoœci silinków lewa
	commandList[i].ID = 107;
	commandList[i].length = 6;
	commandList[i].reciveCanAction = transferToUart;
	commandList[i].reciveUartAction = ignoreUART;
	i++;

	// komendy kompatybilne z ³azikiem i aplikacj¹
	// start stop
	//Sterowanie start,stop
	commandList[i].ID = 21;
	commandList[i].length = 1;
	commandList[i].reciveCanAction = ignoreCAN;
	commandList[i].reciveUartAction = transferToCan;
	i++;
	//reset silników
	commandList[i].ID = 28;
	commandList[i].length = 1;
	commandList[i].reciveCanAction = ignoreCAN;
	commandList[i].reciveUartAction = transferToCan;
	i++;
	//Sterowanie Predkosci referencyjne
	commandList[i].ID = 20;
	commandList[i].length = 6;
	commandList[i].reciveCanAction = ignoreCAN;
	commandList[i].reciveUartAction = transferToCan;
	i++;
	CommandListLenght=i;

}

void COM_RunUartAction()
{
	for (int i = 0; i < 150; i++) {
			if (commandList[i].ID == UART_MessageRecieved.ID) {
				commandList[i].reciveUartAction();
				return;
			}
		}
}
void COM_RunCanAction()
{
	for (int i=0;i<CommandListLenght;i++)
	{
		if (commandList[i].ID == CAN_RxHeader.StdId)
		{
			commandList[i].reciveCanAction();
			return;
		}
	}

}
void SendSpeed()
{
	uint16_t speedprawa, speedlewa;
	speedprawa=	-1*UART_MessageRecieved.data[0] -UART_MessageRecieved.data[1];
	speedlewa= UART_MessageRecieved.data[1]-UART_MessageRecieved.data[0];
	CAN_TxHeader.StdId=102;
	CAN_TxHeader.ExtId=102;
	CAN_TxHeader.DLC=1;
	CAN_TxData[0]=speedprawa;
	HAL_CAN_AddTxMessage(&hcan1,&CAN_TxHeader,CAN_TxData,&CAN_TxMailbox);
	CAN_TxHeader.StdId=103;
	CAN_TxHeader.ExtId=103;
	CAN_TxData[0]=speedlewa;
	HAL_CAN_AddTxMessage(&hcan1,&CAN_TxHeader,CAN_TxData,&CAN_TxMailbox);

}
void transferToUart()
{
	UART_MessageTypeDef msg;
	msg.ID=CAN_RxHeader.StdId;
	for (int i=0;i<8;i++)
	{
		msg.data[i]= CAN_RxMsg[i];
	}
	msg.lenght=CAN_RxHeader.DLC;
	UART2_Send(msg);
}
void transferToCan()
{
	CAN_TxHeader.StdId=UART_MessageRecieved.ID;
	CAN_TxHeader.ExtId=UART_MessageRecieved.ID;
	CAN_TxHeader.IDE=CAN_ID_STD;
	CAN_TxHeader.RTR=CAN_RTR_DATA;
	CAN_TxHeader.DLC=UART_MessageRecieved.lenght;
	HAL_CAN_AddTxMessage(&hcan1,&CAN_TxHeader,UART_MessageRecieved.data,&CAN_TxMailbox);
}
void ignoreCAN()
{
	return;
}
void ignoreUART()
{
	return;
}
