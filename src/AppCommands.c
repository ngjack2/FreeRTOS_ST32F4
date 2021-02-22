/*
 * AppCommands.c
 *
 *  Created on: Feb 6, 2021
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
#include "AppCommands.h"
#include "UartApi.h"
#include "MotorControl.h"

extern const tExecFunction ExecFunctionTable[] =
{
	{ NULL_FUNCTION, NULL},
	{ CMD_DRIVE_MOTOR, cmdDriveMotor },
	{ CMD_MEASURE_DISTANCE, cmdMeasureDistance },
	{ FUNCTION_END, NULL}
};

/**
 * Task handler
 */
void ExecuteHandler(void *params)
{
    while(1)
    {
    	tAppCommand *pParam;

    	//if(xTaskNotifyWait(0, 0, NULL, portMAX_DELAY) == true)
    	if (xQueueReceive(xTaskQueue, &(pParam), portMAX_DELAY))
    	{
    		UINT16 opCode = pParam->cmdId;

    		ExecFunctionTable[opCode].pFunction(pParam);

			taskYIELD();
    	}
    }
}

/**
 *
 *
 */
void cmdDriveMotor(tAppCommand *pAppCommand)
{
	UINT16 direction = ((UINT16*)(pAppCommand->parameterBlockAddr))[0];
	UINT16 speed     = ((UINT16*)(pAppCommand->parameterBlockAddr))[1];

	UINT16 rc = MotorControl((eMotorDirection)direction, speed);

	if (pAppCommand->resultBlockAddr != NULL)
	{
		UINT16 *pData = (UINT32 *)pAppCommand->resultBlockAddr;
		*pData = rc;
	}
}

/**
 *
 */
void cmdMeasureDistance(tAppCommand *pAppCommand)
{
	UINT16 rc = MeasureDistance();
}

