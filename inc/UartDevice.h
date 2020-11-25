/*
 * UartDevice.h
 *
 *  Created on: Nov 24, 2020
 *      Author: 1000086162
 */

#ifndef INC_UARTDEVICE_H_
#define INC_UARTDEVICE_H_

__externC void InitializeUartPorts(void);
__externC void Uart2SendMsg(UINT8* msg);

#endif /* INC_UARTDEVICE_H_ */
