/*
 * HostTask.c
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
#include "queue.h"

#include "eventsFlag.h"
#include "HostTask.h"
#include "UartAPI.h"
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
			CommandQ.fields.param1 = Cdb.field.param1;
			CommandQ.fields.param2 = Cdb.field.param2;
			CommandQ.fields.param3 = Cdb.field.param3;
			CommandQ.fields.rc = ER_NO_ERROR;
		}
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
	return(waitForCommand());
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
	UINT8 usr_msg[100];

	sprintf(usr_msg, "AppsResult=%d\r\n", CommandQ.fields.rc);

	hal_gpioA_pin5_toggle();

	UartSendMessage(usr_msg, sizeof(usr_msg));
}

/**
 * Queue command to execute task
 *
 */
static void HostSendCmdApp(void)
{

	pCommand->cmdId = CommandQ.opCode;

	pCommand->parameterBlockAddr = &CommandQ.words[0];

	pCommand->resultBlockAddr = &CommandQ.fields.rc;

	xQueueSend(xTaskQueue, (void *)&pCommand, portMAX_DELAY);

}
