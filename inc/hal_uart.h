/*
 * UartDevice.h
 *
 *  Created on: Nov 24, 2020
 *      Author: 1000086162
 */

#ifndef INC_HAL_UART_H_
#define INC_HAL_UART_H_

//
// Type definition and structures
//
#define SIZE_RX_BUFFER 12
#define BITS_PER_BYTE 10 //8 bits data + 1 start + 1 stop
#define BAUDRATE 9600

typedef struct
{
    unsigned char   *pBuffer;
    UINT32          bytesTransfered;
    UINT32          packetSize;                     // packet size
}UartTx;

//
// Data variables
//
extern UartTx        UartTransmitter;             // transmitter parameters

//
// Extern functions
//
__externC void InitializeUartPorts(void);
__externC void Uart2SendMsg(UINT8 *pBuf, UINT8 byteCnt);
__externC void Uart6SendMsg(UINT8 *pBuf, UINT8 byteCnt);

//
// UART receiver (implemented by CUartRx in CUartRx.cpp)
//
__externC void   Uart2IrqHandler(void);
__externC void   Uart6IrqHandler(void);
__externC void   UartEnableRxInterrupts(void);
__externC UINT32 Uart6Receive(UINT8 *pBuf, UINT32 size, UINT32 timeoutTicks);

#endif /* INC_HAL_UART_H_ */
