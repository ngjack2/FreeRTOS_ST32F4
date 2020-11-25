/*
 * hal_interrupt.c
 *
 *  Created on: Nov 25, 2020
 *      Author: 1000086162
 */
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "systemTypes.h"
#include "asic.h"
#include "hal_interrupt.h"
#include "stm32f4xx_gpio.h"

__externC void hal_setup_interrupt_PC13(void)
{
	//
	// Configure up for Port C pin 13 User Switch
	//
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	GPIO_InitTypeDef gpioPinC13;
	memset(&gpioPinC13, 0, sizeof(gpioPinC13));

	gpioPinC13.GPIO_Pin   = GPIO_Pin_13;
	gpioPinC13.GPIO_Mode  = GPIO_Mode_IN;
	gpioPinC13.GPIO_OType = GPIO_OType_PP;
	gpioPinC13.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	gpioPinC13.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOC, &gpioPinC13);

	// Setup interrupt trigger for Port C Pin 13
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource13);

	EXTI_InitTypeDef exti_init;
	exti_init.EXTI_Line    = EXTI_Line13;
	exti_init.EXTI_Mode    = EXTI_Mode_Interrupt;
	exti_init.EXTI_Trigger = EXTI_Trigger_Falling;
	exti_init.EXTI_LineCmd = ENABLE;

	EXTI_Init(&exti_init);

	// setting NVIC for Line 13
	NVIC_SetPriority(EXTI15_10_IRQn, 5);
	NVIC_EnableIRQ(EXTI15_10_IRQn);
}
