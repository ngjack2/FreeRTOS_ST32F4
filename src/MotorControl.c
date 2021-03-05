/*
 * MotorControl.c
 *
 *  Created on: Feb 17, 2021
 *      Author: 1000086162
 */
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "systemTypes.h"
#include "ErrorsDB.h"
#include "stm32f4xx.h"

#include "MotorControl.h"

//
const BitAction bMotorState[MOTOR_END_STATE][4] =
{
	{ RESET, RESET, RESET, RESET }, // idle
	{ SET, RESET, SET, RESET },     // forward
	{ RESET, SET, RESET, SET },     // backward
	{ RESET, RESET, SET, RESET },   // right
	{ SET, RESET, RESET, RESET }    // left
};

/**
 *
 */
void InitMotorDriverPort(void)
{
	// Enable Port B pin for Trigger pin
	hal_gpioB_init();
}

/**
 *
 */
UINT16 MotorControl(eMotorDirection direction, UINT16 speed)
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
