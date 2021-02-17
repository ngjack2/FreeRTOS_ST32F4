/*
 * Interrupt_Handlers.c
 *
 *  Created on: Jan 30, 2021
 *      Author: 1000086162
 */
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "systemTypes.h"
#include "asic.h"
#include "hal_interrupt.h"
#include "hal_uart.h"
#include "stm32f4xx_gpio.h"
#include "distanceMeasure.h"

/**
 *
 */
void USART2_IRQHandler(void)
{
	NVIC_DisableIRQ(USART2_IRQn);

	Uart2ReceivedByte();

	NVIC_EnableIRQ(USART2_IRQn);
}

/**
 *
 */
void USART6_IRQHandler(void)
{
	NVIC_DisableIRQ(USART6_IRQn);

	Uart6ReceivedByte();

	NVIC_EnableIRQ(USART6_IRQn);
}

/**
 * Interrupt handler for EXTI 13 (User Switch)
 */
void EXTI15_10_IRQHandler(void)
{
	IrqPC13Handler();
}
