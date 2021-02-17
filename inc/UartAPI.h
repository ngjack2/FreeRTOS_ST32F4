/*
 * UartAPI.h
 *
 *  Created on: Jan 30, 2021
 *      Author: 1000086162
 */

#ifndef INC_UARTAPI_H_
#define INC_UARTAPI_H_

extern void UartSendMessage(UINT8 *pBuf, UINT8 byteCnt);
extern UINT32 UartSerialReceived(UINT8 *pBuf, UINT8 byteCnt);

#endif /* INC_UARTAPI_H_ */
