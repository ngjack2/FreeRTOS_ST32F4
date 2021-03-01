/*
 * CMotorControl.cpp
 *
 *  Created on: Feb 27, 2021
 *      Author: 1000086162
 */
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "systemTypes.h"
#include "ErrorsDB.h"
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "hal_gpio.h"

#include "AppCommands.h"
#include "CMotorControl.hpp"

//
const BitAction bMotorState[MOTOR_END_STATE][4] =
{
	{ Bit_RESET, Bit_RESET, Bit_RESET, Bit_RESET }, // idle
	{ Bit_SET, Bit_RESET, Bit_SET, Bit_RESET },     // forward
	{ Bit_RESET, Bit_SET, Bit_RESET, Bit_SET },     // backward
	{ Bit_RESET, Bit_RESET, Bit_SET, Bit_RESET },   // right
	{ Bit_SET, Bit_RESET, Bit_RESET, Bit_RESET }    // left
};

/**
 *
 *
 */
__externC void cmdDriveMotor(tAppCommand *pAppCommand)
{

	UINT16 rc        = ER_NO_ERROR;
	UINT16 direction = ((UINT16*)(pAppCommand->parameterBlockAddr))[0];
	UINT16 speed     = ((UINT16*)(pAppCommand->parameterBlockAddr))[1];

	CMotorControl *p = new CMotorControl();

	p->RunMotorControl((eMotorDirection)direction, speed);

	if (pAppCommand->resultBlockAddr != NULL)
	{
		UINT16 *pData = (UINT16 *)pAppCommand->resultBlockAddr;
		*pData = rc;
	}

	delete(p);
}

/**
 *
 */
void CMotorControl::InitMotorDriverPort(void)
{
	// Enable Port B pin for Trigger pin
	hal_gpioB_init();
}

/**
 *
 */
UINT16 CMotorControl::RunMotorControl(eMotorDirection direction, UINT16 speed)
{
	UINT16 rc = ER_NO_ERROR;

	// Motor 1 control pin 1
	GPIO_WriteBit(GPIOB, GPIO_Pin_1, bMotorState[direction][0]);

	// Motor 1 control pin 2
	GPIO_WriteBit(GPIOB, GPIO_Pin_2, bMotorState[direction][1]);

	// Motor 2 control pin 1
	GPIO_WriteBit(GPIOC, GPIO_Pin_5, bMotorState[direction][2]);

	// Motor 2 control pin 2
	GPIO_WriteBit(GPIOC, GPIO_Pin_6, bMotorState[direction][3]);

	return rc;
}




