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
typedef struct
{
    unsigned char   *pRxBuf;         // receive buffer pointer
    UINT32          packetByteCount;                // byte couting during receiving a packet.
    UINT32          packetSize;
    UINT16          waitTime;
    union
    {
        UINT8       all8;
        struct
        {
            UINT8   packetError:            1;
            UINT8   dataPacket:             1;
            UINT8   timedout:               1;
            UINT8   reserves:               5;
        } bit;
    } Flags;
    UINT8           pad;

}UartRx;

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
extern UartRx        UartReceiver;                // receiver parameters

//
// Extern functions
//
__externC void InitializeUartPorts(void);
__externC void Uart2SendMsg(UINT8 *pBuf, UINT8 byteCnt);
__externC void Uart6SendMsg(UINT8 *pBuf, UINT8 byteCnt);
__externC void Uart2ReceivedByte(void);
__externC void Uart6ReceivedByte(void);

#endif /* INC_HAL_UART_H_ */
