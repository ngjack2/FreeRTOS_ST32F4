/*
 * hal_interrupt.h
 *
 *  Created on: Nov 25, 2020
 *      Author: 1000086162
 */

#ifndef INC_HAL_INTERRUPT_H_
#define INC_HAL_INTERRUPT_H_

__externC void hal_setup_interrupt_PC13(void);
__externC void hal_setup_interrupt_timer2(void);

// Interrupt handlers implemented in CMeasureDistance.cpp
__externC void IrqPC13Handler(void);
__externC void IrqTimer2Handler(void);

#endif /* INC_HAL_INTERRUPT_H_ */
