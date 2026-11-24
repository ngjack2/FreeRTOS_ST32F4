/*
 * UartAPI.h
 *
 *  Created on: Jan 30, 2021
 *      Author: 1000086162
 */

#ifndef INC_UARTAPI_H_
#define INC_UARTAPI_H_

extern UINT32 calculateCmdByteChecksum(UINT8 *pBuf, UINT8 byteCnt);
extern UINT32 calculateXferTime(UINT16 transferByteCount);
extern void UartSendMessage(UINT8 *pBuf, UINT8 byteCnt);
extern UINT32 UartSerialReceived(UINT8 *pBuf, UINT8 byteCnt);
extern void UartStartReceiver(void);

#endif /* INC_UARTAPI_H_ */
