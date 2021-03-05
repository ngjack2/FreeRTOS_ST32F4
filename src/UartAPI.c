/*
 * UartAPI.c
 *
 *  Created on: Jan 30, 2021
 *      Author: 1000086162
 */
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "systemTypes.h"
#include "ErrorsDB.h"
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
 *
 */
UINT32 calculateXferTime(UINT16 transferByteCount)
{
    UINT32 baudrateVal;
    UINT32 byteTime, waitTime;

    //
    // Get current baud rate for calculation
    //
    baudrateVal = BAUDRATE;

    //
    // byteTime = uS/byte
    //
    byteTime = (BITS_PER_BYTE * 1000000) / baudrateVal;

    //
    // waitTime in OS Ticks = (transferByteCount * byteTime * 4) / OS mS per tick * 1000 us/mS
    // Note: Multiply byteTime by 4 for slow hosts
    //
    waitTime = (transferByteCount * byteTime * 4) / (portTICK_RATE_MS  * 1000);;

    //
    // extend the wait time 150mS for slow host
    // Programmers Note: For debug change 150mS to 10mS to capture timeout on emulator (1 tick handles 115,200 and above).
    //
    waitTime = waitTime + (150 / portTICK_RATE_MS);

    //
    // check for overflows, set to max - 1 in case max is used as wait-forever
    //
    if (waitTime & 0xFFFF0000)
    {
        waitTime = 0xFFFE;
    }
    return waitTime;
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

	UINT32 waitTimeInTicks = calculateXferTime(UartReceiver.packetSize);

	EventBits_t eventBit = xEventGroupWaitBits(xEventFlag, UART_1ST_BYTE_RX_EVENT, FALSE, FALSE, portMAX_DELAY);
	if (eventBit & UART_1ST_BYTE_RX_EVENT)
	{
		eventBit = xEventGroupWaitBits(xEventFlag, UART_RX_EVENT, FALSE, FALSE, waitTimeInTicks);
		if (!(eventBit & UART_RX_EVENT))
		{
			UartReceiver.Flags.bit.timedout = TRUE;
			rc = ER_UART6_TIMEOUT_RX;
		}
		xEventGroupClearBits(xEventFlag, UART_1ST_BYTE_RX_EVENT | UART_RX_EVENT);
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
