/*
 * hal_clock.h
 *
 *  Created on: 3 Mar 2020
 *      Author: yaphan.ng
 */

#ifndef HAL_CLOCK_H_
#define HAL_CLOCK_H_

//
// 100 MHz setting PLL clock
//
struct sPllParam
{
	UINT32 PLLN;
	UINT32 PLLM;
	UINT32 PLLP;
	UINT32 PLLQ;
};

__externC void hal_clock_init(void);

#endif /* HAL_CLOCK_H_ */
