/*
 * AppCommands.h
 *
 *  Created on: Feb 6, 2021
 *      Author: 1000086162
 */

#ifndef INC_APPCOMMANDS_H_
#define INC_APPCOMMANDS_H_

//
//
//
enum eExecFunctionList
{
	NULL_FUNCTION = 0,
	CMD_DRIVE_FORWARD,
	CMD_DRIVE_LEFT,
	CMD_DRIVE_RIGHT,
	CMD_DRIVE_BACKWARD,
	FUNCTION_END = 0xFFFF,
};

//
// Execution function type
//
typedef void(*ExecFunction)(void *);

//
// Execute function enum and handler pair
//
typedef struct
{
	enum eExecFunctionList functionNumber;
    ExecFunction pFunction;
} tExecFunction;

typedef struct
{
    UINT16 cmdId;
    void * parameterBlockAddr;
    void * resultBlockAddr;
} tAppCommand;

//
//
//
extern QueueHandle_t xTaskQueue;

extern void ExecuteHandler(void *params);
extern void cmdDriveForward(tAppCommand *pAppCommand);

#endif /* INC_APPCOMMANDS_H_ */
