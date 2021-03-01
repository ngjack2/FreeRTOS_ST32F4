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
#include "main.h"
#include "HostTask.h"
#include "AppCommands.h"
#include "UartApi.h"

void cmdDriveMotor(tAppCommand *pAppCommand);
void cmdMeasureDistance(tAppCommand *pAppCommand);

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


