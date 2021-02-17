/*
 * hal_timer.h
 *
 *  Created on: Mar 5, 2020
 *      Author: yaphan.ng
 */

#ifndef HAL_TIMER_H_
#define HAL_TIMER_H_


__externC void hal_timer_init(void);
__externC void hal_delay_ms(UINT32 value);

__externC UINT32 hal_delay_20ns(UINT32 value);
__externC UINT32 hal_get_timer2_counter(void);


#endif /* HAL_TIMER_H_ */
