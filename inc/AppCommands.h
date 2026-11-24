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
	CMD_DRIVE_MOTOR,
	CMD_MEASURE_DISTANCE,
	FUNCTION_END = 0xFFFF,
};

typedef struct
{
    UINT16 cmdId;
    void * parameterBlockAddr;
    void * resultBlockAddr;
} tAppCommand;

//
// Execution function type
//
typedef void(*ExecFunction)(tAppCommand *);

//
// Execute function enum and handler pair
//
typedef struct
{
	enum eExecFunctionList functionNumber;
    ExecFunction pFunction;
} tExecFunction;

//
//
//
extern void ExecuteHandler(void *params);

//
// Application command handlers (implemented in C++ modules)
//
__externC void cmdDriveMotor(tAppCommand *pAppCommand);
__externC void cmdMeasureDistance(tAppCommand *pAppCommand);

#endif /* INC_APPCOMMANDS_H_ */
