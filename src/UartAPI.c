/*
 * UartAPI.c
 *
 *  Created on: Jan 30, 2021
 *      Author: 1000086162
 */
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "ErrorsDB.h"
#include "systemTypes.h"
#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "event_groups.h"

#include "hal_clock.h"
#include "hal_timer.h"
#include "hal_gpio.h"
#include "hal_interrupt.h"
#include "hal_uart.h"
#include "distanceMeasure.h"
#include "HostTask.h"
#include "eventsFlag.h"
#include "main.h"

/**
 *
 */
UINT32 calculateCmdByteChecksum(UINT8 *pBuf, UINT8 byteCnt)
{
	UINT32 checksum = 0;

	for (UINT8 i = 0; i < byteCnt; i++)
	{
		checksum += pBuf[i];
	}

	return checksum;
}

/**
 * UART Receive Message API
 *
 * @pBuf - pointer to user message buffer
 * @byteCnt - number of bytes contain in the message buffer
 *
 * @return - UART Receive Error Code
 */
UINT32 UartSerialReceived(UINT8 *pBuf, UINT8 byteCnt)
{
	UINT32 rc = ER_NO_ERROR;

	// Initialize Uart Rx structure
	memset(&UartReceiver, 0, sizeof(UartReceiver));
	UartReceiver.pRxBuf          = pBuf;
	UartReceiver.packetByteCount = 0;
	UartReceiver.packetSize      = byteCnt;

	//if (xSemaphoreTake(xSemaphore, portMAX_DELAY))
	EventBits_t eventBit = xEventGroupWaitBits(xEventFlag, UART_1ST_BYTE_RX_EVENT, FALSE, FALSE, portMAX_DELAY);
	if (eventBit & UART_1ST_BYTE_RX_EVENT)
	{
		eventBit = xEventGroupWaitBits(xEventFlag, UART_RX_EVENT, FALSE, FALSE, portMAX_DELAY);
		if (eventBit & UART_RX_EVENT)
		{
			UINT32 rxChecksum;

			// Clear the waiting bit
			xEventGroupClearBits(xEventFlag, UART_1ST_BYTE_RX_EVENT | UART_RX_EVENT);
			//if (UartReceiver.Flags.bit.timedout == TRUE)
			//{
			//	rc = ER_UART6_TIMEOUT_RX;
			//}
		}
	}

	return rc;
}

/**
 * UART API Send Message For User
 *
 * @param pBuf - pointer to the message input
 * @param byeCnt - total bytes contain in the message
 *
 * @return - UART Error Code
 */
void UartSendMessage(UINT8 *pBuf, UINT8 byteCnt)
{
	Uart6SendMsg(pBuf, byteCnt);
}
