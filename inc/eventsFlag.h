/*
 * eventsFlag.h
 *
 *  Created on: Feb 2, 2021
 *      Author: 1000086162
 */

#ifndef INC_EVENTSFLAG_H_
#define INC_EVENTSFLAG_H_

typedef enum
{
    NO_EVENT                        = M(0),
    SUPER_RESET_EVENT               = M(1),
	UART_1ST_BYTE_RX_EVENT          = M(2),
    UART_RX_EVENT                   = M(3),
    UART_TX_EVENT                   = M(4),

} eEventId;

__externC SemaphoreHandle_t xSemaphore;
__externC EventGroupHandle_t xEventFlag;

#endif /* INC_EVENTSFLAG_H_ */
