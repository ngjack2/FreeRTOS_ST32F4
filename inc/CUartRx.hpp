/*
 * CUartRx.hpp
 *
 *  Interrupt driven UART receiver.
 *  - ISR only stores bytes while a receive request is armed (no stray writes).
 *  - Overrun / noise / framing errors are always cleared (no IRQ storm).
 *  - The waiting task is woken directly with a task notification
 *    (no dependency on the FreeRTOS timer service task).
 */

#ifndef CUARTRX_HPP_
#define CUARTRX_HPP_

class CUartRx
{
public:
	CUartRx(USART_TypeDef *pPort, IRQn_Type irq) : m_pPort(pPort), m_irq(irq) {}
	~CUartRx() {}

	void   EnableRxInterrupt(UINT8 preemptPriority = configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);
	UINT32 Receive(UINT8 *pBuf, UINT32 size, TickType_t completeTimeout);
	void   IrqHandler(void);

	UINT32 GetErrorCount(void) const   { return m_errorCount; }
	UINT32 GetDroppedCount(void) const { return m_droppedCount; }

private:
	enum : UINT32
	{
		RX_FIRST_BYTE_BIT = M(0),
		RX_DONE_BIT       = M(1),
		RX_ALL_BITS       = 0xFFFFFFFFUL,
	};

	USART_TypeDef * const m_pPort;
	const IRQn_Type       m_irq;

	// Shared between task and ISR
	UINT8 * volatile      m_pRxBuf       = nullptr;
	volatile UINT32       m_byteCount    = 0;
	volatile UINT32       m_packetSize   = 0;
	volatile bool         m_armed        = false;
	volatile bool         m_packetError  = false;
	TaskHandle_t volatile m_waitingTask  = nullptr;

	// Diagnostics
	volatile UINT32       m_errorCount   = 0;
	volatile UINT32       m_droppedCount = 0;
};

#endif /* CUARTRX_HPP_ */
