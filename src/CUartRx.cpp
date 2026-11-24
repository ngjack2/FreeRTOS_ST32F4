/*
 * CUartRx.cpp
 *
 *  Interrupt driven UART receiver (see CUartRx.hpp).
 */
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "systemTypes.h"
#include "ErrorsDB.h"
#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "task.h"

#include "hal_uart.h"
#include "CUartRx.hpp"

//
// Receiver instances, one per UART port
//
static CUartRx s_uart2Rx(USART2, USART2_IRQn);
static CUartRx s_uart6Rx(USART6, USART6_IRQn);

/**
 * Flush any stale data / error flags, then enable the RX interrupt in the
 * USART and NVIC. Must only be called once the scheduler is running.
 *
 * @param preemptPriority - NVIC preemption priority, must be numerically
 *                          >= configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY
 *                          because the ISR calls FreeRTOS "FromISR" APIs.
 */
void CUartRx::EnableRxInterrupt(UINT8 preemptPriority)
{
	configASSERT(preemptPriority >= configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);

	// SR read followed by DR read clears RXNE / ORE / NE / FE left over from boot
	(void)USART_GetFlagStatus(m_pPort, USART_FLAG_ORE);
	(void)USART_ReceiveData(m_pPort);

	NVIC_InitTypeDef nvicInit;
	memset(&nvicInit, 0, sizeof(nvicInit));
	nvicInit.NVIC_IRQChannel                   = m_irq;
	nvicInit.NVIC_IRQChannelPreemptionPriority = preemptPriority;
	nvicInit.NVIC_IRQChannelSubPriority        = 0;
	nvicInit.NVIC_IRQChannelCmd                = ENABLE;
	NVIC_Init(&nvicInit);

	// RXNEIE also enables the overrun (ORE) interrupt
	USART_ITConfig(m_pPort, USART_IT_RXNE, ENABLE);
}

/**
 * Receive a packet of "size" bytes into pBuf.
 * Blocks forever for the first byte, then up to completeTimeout ticks for
 * the rest of the packet.
 *
 * @return - ER_NO_ERROR, ER_UART6_TIMEOUT_RX or ER_UART_RX_ERROR
 */
UINT32 CUartRx::Receive(UINT8 *pBuf, UINT32 size, TickType_t completeTimeout)
{
	if ((pBuf == nullptr) || (size == 0))
	{
		return ER_UART_RX_ERROR;
	}

	// Discard any stale notification from a previous packet. The ISR is
	// disarmed here, so no new notification can arrive before we arm it.
	(void)xTaskNotifyWait(0, RX_ALL_BITS, nullptr, 0);

	taskENTER_CRITICAL();
	m_pRxBuf      = pBuf;
	m_packetSize  = size;
	m_byteCount   = 0;
	m_packetError = false;
	m_waitingTask = xTaskGetCurrentTaskHandle();
	m_armed       = true;
	taskEXIT_CRITICAL();

	uint32_t bits = 0;

	// Wait for the start of a new command
	while ((bits & (RX_FIRST_BYTE_BIT | RX_DONE_BIT)) == 0)
	{
		uint32_t value = 0;
		if (xTaskNotifyWait(0, RX_ALL_BITS, &value, portMAX_DELAY) == pdTRUE)
		{
			bits |= value;
		}
	}

	// Wait for the remaining bytes of the packet
	TimeOut_t  timeOut;
	TickType_t remaining = completeTimeout;
	vTaskSetTimeOutState(&timeOut);
	while ((bits & RX_DONE_BIT) == 0)
	{
		uint32_t value = 0;
		if (xTaskNotifyWait(0, RX_ALL_BITS, &value, remaining) == pdTRUE)
		{
			bits |= value;
		}

		if (((bits & RX_DONE_BIT) == 0) && (xTaskCheckForTimeOut(&timeOut, &remaining) != pdFALSE))
		{
			break;
		}
	}

	// Disarm so the ISR never writes into the caller's buffer after we return
	taskENTER_CRITICAL();
	m_armed       = false;
	m_pRxBuf      = nullptr;
	m_waitingTask = nullptr;
	const bool complete    = (m_byteCount >= m_packetSize);
	const bool packetError = m_packetError;
	taskEXIT_CRITICAL();

	if (!complete)
	{
		return ER_UART6_TIMEOUT_RX;
	}

	return packetError ? ER_UART_RX_ERROR : ER_NO_ERROR;
}

/**
 * UART RX interrupt service routine body.
 */
void CUartRx::IrqHandler(void)
{
	// Reading SR (USART_GetFlagStatus) followed by DR (USART_ReceiveData)
	// clears RXNE and the ORE / NE / FE error flags.
	const bool rxReady = (USART_GetFlagStatus(m_pPort, USART_FLAG_RXNE) == SET);
	const bool rxError = (USART_GetFlagStatus(m_pPort, USART_FLAG_ORE) == SET) ||
	                     (USART_GetFlagStatus(m_pPort, USART_FLAG_NE)  == SET) ||
	                     (USART_GetFlagStatus(m_pPort, USART_FLAG_FE)  == SET);

	if (!rxReady && !rxError)
	{
		return;
	}

	const UINT8 data = static_cast<UINT8>(USART_ReceiveData(m_pPort));

	if (rxError)
	{
		m_errorCount = m_errorCount + 1;
	}

	const UINT32 count = m_byteCount;
	if (!m_armed || (m_pRxBuf == nullptr) || (count >= m_packetSize))
	{
		// Nobody is waiting for data: drop it
		m_droppedCount = m_droppedCount + 1;
		return;
	}

	m_pRxBuf[count]  = data;
	m_byteCount      = count + 1;
	if (rxError)
	{
		m_packetError = true;
	}

	uint32_t bits = 0;
	if (count == 0)
	{
		bits |= RX_FIRST_BYTE_BIT;
	}
	if ((count + 1) >= m_packetSize)
	{
		m_armed = false;
		bits |= RX_DONE_BIT;
	}

	if ((bits != 0) && (m_waitingTask != nullptr))
	{
		BaseType_t higherPriorityTaskWoken = pdFALSE;
		xTaskNotifyFromISR(m_waitingTask, bits, eSetBits, &higherPriorityTaskWoken);
		portYIELD_FROM_ISR(higherPriorityTaskWoken);
	}
}

//
// C interface used by the C modules
//
__externC void Uart2IrqHandler(void)
{
	s_uart2Rx.IrqHandler();
}

__externC void Uart6IrqHandler(void)
{
	s_uart6Rx.IrqHandler();
}

__externC void UartEnableRxInterrupts(void)
{
	s_uart2Rx.EnableRxInterrupt();
	s_uart6Rx.EnableRxInterrupt();
}

__externC UINT32 Uart6Receive(UINT8 *pBuf, UINT32 size, UINT32 timeoutTicks)
{
	return s_uart6Rx.Receive(pBuf, size, static_cast<TickType_t>(timeoutTicks));
}
