/*
 * ErrorsDB.h
 *
 *  Created on: Jan 30, 2021
 *      Author: 1000086162
 */

#ifndef INC_ERRORSDB_H_
#define INC_ERRORSDB_H_

#define BASE_ERROR_ADDR 0x5000

#define ER_NO_ERROR            BASE_ERROR_ADDR + 1
#define ER_UART6_TIMEOUT_RX    BASE_ERROR_ADDR + 2
#define ER_CHKSUM_ERROR        BASE_ERROR_ADDR + 3

#endif /* INC_ERRORSDB_H_ */
