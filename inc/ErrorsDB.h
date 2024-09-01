/*
 * ErrorsDB.h
 *
 *  Created on: Jan 30, 2021
 *      Author: 1000086162
 */

#ifndef INC_ERRORSDB_H_
#define INC_ERRORSDB_H_

//
//
//
enum eErrorCodeList
{
	ER_NO_ERROR = 0,
	ER_UART6_TIMEOUT_RX,
	ER_CHKSUM_ERROR,
	ER_OPCODE_ERROR,
	ER_END_LINE,
};

//
//
//
typedef struct
{
	enum eErrorCodeList eErrCodeList;
	UINT8 errorCodeMessage[200];
}tErrorCodeStruct;

__externC tErrorCodeStruct errorCodeTable[];

#endif /* INC_ERRORSDB_H_ */
