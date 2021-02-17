/*
 * hal_timer.c
 *
 *  Created on: 4 Mar 2020
 *      Author: yaphan.ng
 */
#include "systemTypes.h"
#include "asic.h"
#include "hal_timer.h"

//
// Function prototype declaration
//
static void hal_timer2_init(void);
static void hal_timer3_init(void);
//static UINT32 hal_get_timer2_counter(void);
static UINT32 hal_get_timer3_counter(void);

/**
 * Initialize all the necessary timer
 *
 */
__externC void hal_timer_init(void)
{
	//hal_timer2_init();

	hal_timer3_init();
}

/**
 * Create a general counter with 1 tick is 1us
 *
 */
static void hal_timer2_init(void)
{
	// Enable timer 2
	sRCC->RCC_APB1ENR.bits.TIM2EN = 1;

	// Load 0 into auto reload register
	sTIM2->TIMx_ARR.all32 = 0;

	//
	sTIM2->TIMx_CNT.all32 = 0;

	// divide 50 for current clk speed
	sTIM2->TIMx_PSC.all32 = 51;

	// Timer counter enable
	sTIM2->TIMx_CR1.bits.CEN = 1;

}

/**
 * Create a general counter with 1 tick is 1us
 *
 */
static void hal_timer3_init(void)
{
	// Enable timer 2
	sRCC->RCC_APB1ENR.bits.TIM3EN = 1;

	// Load 0 into auto reload register
	sTIM3->TIMx_ARR.all32 = 0;

	//
	sTIM3->TIMx_CNT.all32 = 0;

	// divide 50 for current clk speed
	sTIM3->TIMx_PSC.all32 = 0;

	// Timer counter enable
	sTIM3->TIMx_CR1.bits.CEN = 1;

}

/**
 * Get free running timer2 counter value
 *
 */
__externC UINT32 hal_get_timer2_counter(void)
{

	UINT32 value = sTIM2->TIMx_CNT.all32;

	return (value);
}

/**
 * Get free running timer3 counter value
 *
 */
static UINT32 hal_get_timer3_counter(void)
{

	UINT32 value = sTIM3->TIMx_CNT.all32;

	return (value);
}

/**
 * Function that delay 1 ms
 *
 */
__externC void hal_delay_ms(UINT32 value)
{
	for (UINT32 i = value; i > 0; i--)
	{
		// loop for 1us for 1000 times equal to 1ms
		for (UINT32 j = 0; j < 10; j++)
			hal_delay_20ns(5000);
	}
}

/**
 * Function that delay 20 ns
 * *APB1 max clk is 50MHz is 20ns/cycle
 *
 */
__externC UINT32 hal_delay_20ns(UINT32 value)
{
	volatile UINT32 startTime = hal_get_timer3_counter();

	return ((startTime - hal_get_timer3_counter()) <= value);
}

