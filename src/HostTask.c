/*
 * HostTask.c
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
#include "queue.h"

#include "eventsFlag.h"
#include "HostTask.h"
#include "UartAPI.h"
#include "main.h"
#include "AppCommands.h"

//
//
//
static void HostSendCmdApp(void);
static void HostGetAppResult(void);


//
//
//
static tCommandQ CommandQ;
static tAppCommand *pCommand;
tHostCommandTable HostCommandTable[] =
{
	{ HostGetAppResult, APP_INIT_BITS },
	{ HostSendCmdApp,   APP_INIT_BITS },
};

/**
 *
 */
UINT32 waitForCommand(void)
{
	tCDB Cdb;
	UINT32 rc = ER_NO_ERROR;

	rc = UartSerialReceived(&Cdb, sizeof(Cdb));
	if (rc == ER_NO_ERROR)
	{
		// Check the received packet checksum
		UINT8 rxChecksum = calculateCmdByteChecksum(&Cdb, sizeof(Cdb));
		if (0)//Cdb.field.checksum != rxChecksum)
		{
			rc = ER_CHKSUM_ERROR;
		}
		else
		{
			CommandQ.opCode        = Cdb.field.opCode;
			CommandQ.appOpCode     = Cdb.field.appOpCode;
			CommandQ.fields.param1 = Cdb.field.param1;
			CommandQ.fields.param2 = Cdb.field.param2;
			CommandQ.fields.rc     = ER_NO_ERROR;
		}
	}

	return rc;
}

/**
 * Check Opcode Command in the range
 *
 * @return - Error Code for Opcode Range
 */
UINT32 CheckCommandValid(void)
{
	UINT32 rc = ER_NO_ERROR;

	UINT32 totalOpcode = sizeof(HostCommandTable);
	UINT32 divider     = sizeof(tHostCommandTable);

	if(CommandQ.opCode > 2)
	{
		rc = ER_OPCODE_ERROR;
	}

	return rc;
}

/**
 * Get command from interface device bluetooth HC05
 *
 * @return - Error Code
 */
UINT32 GetCommandFromUart(void)
{
	UINT32 rc = ER_NO_ERROR;

	rc = waitForCommand();
	if (rc == ER_NO_ERROR)
	{
		rc = CheckCommandValid();
	}
}

/**
 * Start Task handing
 *
 */
void HostTask(void *params)
{
	UINT32 rc = ER_NO_ERROR;

	pCommand = (tAppCommand*)(pvPortMalloc(sizeof(tAppCommand)));

	while(1)
	{
		rc = GetCommandFromUart();
		if (rc == ER_NO_ERROR)
		{
			HostCommandTable[CommandQ.opCode].pFunc();
		}
		else
		{
			//UartSendMessage(errorCodeTable[rc].errorCodeMessage, sizeof(errorCodeTable[rc].errorCodeMessage));
			UINT8 usr_msg[] = "B\r\n";
			UartSendMessage(usr_msg, 5);
		}

		taskYIELD();
	}

	vPortFree(pCommand);
}

/**
 * Send application result back to host
 *
 */
static void HostGetAppResult(void)
{
	//UINT8 usr_msg[100];

	//sprintf(&usr_msg[0], "AppsResult=%d\r\n", CommandQ.fields.rc);

	//hal_gpioA_pin5_toggle();

	//UartSendMessage(usr_msg, sizeof(usr_msg));
	UINT8 usr_msg[] = "A\r\n";
	UartSendMessage(usr_msg, 5);

	//hal_gpioA_pin5_toggle();
}

/**
 * Queue command to execute task
 *
 */
static void HostSendCmdApp(void)
{

	pCommand->cmdId = CommandQ.appOpCode;

	pCommand->parameterBlockAddr = &CommandQ.words[0];

	pCommand->resultBlockAddr = &CommandQ.fields.rc;

	xQueueSend(xTaskQueue, (void *)&pCommand, portMAX_DELAY);

}
