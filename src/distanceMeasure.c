/*
 * distanceMeasure.c
 *
 *  Created on: Nov 20, 2020
 *      Author: 1000086162
 */
#include <stdbool.h>

#include "systemTypes.h"
#include "stm32f4xx.h"
#include "asic.h"
#include "hal_gpio.h"
#include "hal_timer.h"
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"

//
// Definition
//
#define SPEED_OF_SOUND_SCALED 5831
#define USE_SCALE 1000

//
// Global Variables
//
UINT8 objDistance;

//
// function prototype
//
static void initGPIOForUltraSonic(void);
static void startTriggerMode(void);
static UINT32 readBackEchoTiming(void);

/**
 *
 */
__externC void IrqPC13Handler(void)
{
	traceISR_ENTER();

	//1. clear the interrupt pending bit of the EXTI line (13)
	EXTI_ClearITPendingBit(EXTI_Line13);

	objDistance = 16;//MeasureDistance();

	// Start pull up trigger pin for 10us
	GPIO_ToggleBits(GPIOC, GPIO_Pin_5);

	//xTaskNotifyFromISR(xTaskHandler[1], 0, eNoAction, NULL);

	traceISR_EXIT();
}

/**
 * Initialize device GPIO for sensor
 *
 */
static void initGPIOForUltraSonic(void)
{
	// Enable Port B pin for Trigger pin
	hal_gpioB_init();

	// Enable Port C pin for Echo pin
	hal_gpioC_init();

}

/**
 * Start the trigger 10us for device
 */
static void startTriggerMode(void)
{
	// Start pull up trigger pin for 10us
	GPIO_WriteBit(GPIOC, GPIO_Pin_7, Bit_SET);

	// Delay 10us
	hal_delay_20ns(500);

	// Pull down the trigger pin
	GPIO_WriteBit(GPIOC, GPIO_Pin_7, Bit_RESET);

}

/**
 * Wait for Echo pin trigger and measure timing
 */
static UINT32 readBackEchoTiming(void)
{
	UINT32 numberOfTickUs = 0;

	while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6) != true);

	//hal_delay_20ns(5);

	while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6) == true)
	{
		hal_delay_20ns(5);
		numberOfTickUs++;
	}

	return numberOfTickUs;
}

/**
 * Start measure distance of object
 *
 */
UINT32 MeasureDistance(void)
{
	UINT32 distance = 0;
	UINT32 rawValue = 0;

	//taskENTER_CRITICAL();

	initGPIOForUltraSonic();

	startTriggerMode();

	rawValue = readBackEchoTiming();

	distance = (rawValue * USE_SCALE) / SPEED_OF_SOUND_SCALED;

	//taskEXIT_CRITICAL();

	return distance;
}
