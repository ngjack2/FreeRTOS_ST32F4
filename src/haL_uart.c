/*
 * UartDevice.c
 *
 *  Created on: Nov 24, 2020
 *      Author: 1000086162
 */
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "systemTypes.h"
#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "event_groups.h"
#include "hal_gpio.h"
#include "hal_uart.h"
#include "hal_timer.h"
#include "eventsFlag.h"
#include "timers.h"
//
// function prototype
//
static void InitializeUart2Device(void);
static void InitializeUart6Device(void);

//
// Define structures for Uart transmit interrutps
// (RX state is owned by CUartRx, see CUartRx.cpp)
//
UartTx UartTransmitter;

/**
 * Initialize all the UART ports
 * Note: RX interrupts are enabled later by UartEnableRxInterrupts(),
 *       once the scheduler is running.
 */
__externC void InitializeUartPorts(void)
{
	InitializeUart2Device();

	InitializeUart6Device();
}

/**
 * Setup for UART 2
 *
 */
static void InitializeUart2Device(void)
{
	GPIO_InitTypeDef gpio_uart_pins;
	USART_InitTypeDef uart2_init;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	memset(&gpio_uart_pins, 0, sizeof(gpio_uart_pins));
	gpio_uart_pins.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
	gpio_uart_pins.GPIO_Mode = GPIO_Mode_AF;
	gpio_uart_pins.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &gpio_uart_pins);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);

	memset(&uart2_init, 0, sizeof(uart2_init));
	uart2_init.USART_BaudRate = 115200;
	uart2_init.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	uart2_init.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	uart2_init.USART_Parity = USART_Parity_No;
	uart2_init.USART_StopBits = USART_StopBits_1;
	uart2_init.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART2, &uart2_init);

	USART_Cmd(USART2, ENABLE);
}

/**
 * Setup for UART 6
 *
 */
static void InitializeUart6Device(void)
{
	GPIO_InitTypeDef gpio_uart_pins;
	USART_InitTypeDef uart6_init;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	memset(&gpio_uart_pins, 0, sizeof(gpio_uart_pins));
	gpio_uart_pins.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
	gpio_uart_pins.GPIO_Mode = GPIO_Mode_AF;
	gpio_uart_pins.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &gpio_uart_pins);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource11, GPIO_AF_USART6);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource12, GPIO_AF_USART6);

	memset(&uart6_init, 0, sizeof(uart6_init));
	uart6_init.USART_BaudRate = BAUDRATE;
	uart6_init.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	uart6_init.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	uart6_init.USART_Parity = USART_Parity_No;
	uart6_init.USART_StopBits = USART_StopBits_1;
	uart6_init.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART6, &uart6_init);

	USART_Cmd(USART6, ENABLE);
}

/**
 * UART2 send message out
 */
__externC void Uart2SendMsg(UINT8* pBuf, UINT8 byteCnt)
{
	for (UINT32 i = 0; i < byteCnt; i++)
	{
		while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) != SET);
		USART_SendData(USART2, pBuf[i]);
		if (pBuf[i] == '\n')
			break;
	}
}

/**
 * UART6 Tx Abraction Layer
 *
 * @param -
 */
__externC void Uart6SendMsg(UINT8 *pBuf, UINT8 byteCnt)
{
	for (UINT32 i = 0; i < byteCnt; i++)
	{
		while(USART_GetFlagStatus(USART6, USART_FLAG_TXE) != SET);
		USART_SendData(USART6, pBuf[i]);

		if (pBuf[i] == '\n')
			break;
	}
}

