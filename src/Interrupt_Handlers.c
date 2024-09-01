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


/**
 *
 */
void USART2_IRQHandler(void)
{
	//NVIC_DisableIRQ(USART2_IRQn);

	if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
	{
		Uart2ReceivedByte();

		USART_ClearITPendingBit(USART2, USART_IT_RXNE);
	}

	//NVIC_EnableIRQ(USART2_IRQn);
}

/**
 *
 */
void USART6_IRQHandler(void)
{
	//NVIC_DisableIRQ(USART6_IRQn);
	if (USART_GetITStatus(USART6, USART_IT_RXNE) != RESET)
	{
		Uart6ReceivedByte();

		USART_ClearITPendingBit(USART6, USART_IT_RXNE);
	}
	//NVIC_EnableIRQ(USART6_IRQn);
}

/**
 * Interrupt handler for EXTI 13 (User Switch)
 */
void EXTI15_10_IRQHandler(void)
{
	IrqPC13Handler();
}

/**
 * Interrupt handler for TIM2 Every 1ms
 */
void TIM2_IRQHandler(void)
{
	//NVIC_DisableIRQ(TIM2_IRQn);

	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
	{
		IrqTimer2Handler();

		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}

	//NVIC_EnableIRQ(TIM2_IRQn);
}
