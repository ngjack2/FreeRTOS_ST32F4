/*
 * ErrorsDB.c
 *
 *  Created on: Feb 28, 2021
 *      Author: 1000086162
 */
#include "systemTypes.h"
#include "ErrorsDB.h"

//
//
//
__externC tErrorCodeStruct errorCodeTable[] =
{
	{ ER_NO_ERROR,            "NO_ERROR\r\n" },
	{ ER_UART6_TIMEOUT_RX,    "ERROR_UART_TIMEOUT_RECEIVED\r\n" },
	{ ER_CHKSUM_ERROR,        "ERROR_RECEIVED_DATA_CHECKSUM\r\n" },
};


