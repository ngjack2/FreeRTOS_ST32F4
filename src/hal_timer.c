/*
 * hal_timer.c
 *
 *  Created on: 4 Mar 2020
 *      Author: yaphan.ng
 */
#include "systemTypes.h"
#include "asic.h"
#include "hal_timer.h"
#include "stm32f4xx_tim.h"

//
// Function prototype declaration
//
static void hal_timer1_init(void);
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
	hal_timer1_init();

	hal_timer2_init();

	hal_timer3_init();
}

/**
 * Create a PWM counter with 1 tick is 1us
 *
 */
static void hal_timer1_init(void)
{
    // Enable clock for TIM1
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

    // Configure TIM1 as PWM
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;

    TIM_TimeBaseStruct.TIM_Prescaler     = 0; // No prescaler
    TIM_TimeBaseStruct.TIM_CounterMode   = TIM_CounterMode_Up;
    TIM_TimeBaseStruct.TIM_Period        = 1000; // PWM period (adjust as needed)
    TIM_TimeBaseStruct.TIM_ClockDivision = 0;
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStruct);

    //
    TIM_OCInitTypeDef TIM_OCInitStruct;

    TIM_OCInitStruct.TIM_OCMode      = TIM_OCMode_PWM1;
    TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStruct.TIM_Pulse       = 500; // Initial duty cycle (adjust as needed)
    TIM_OCInitStruct.TIM_OCPolarity  = TIM_OCPolarity_High; // Active high output
    TIM_OC1Init(TIM1, &TIM_OCInitStruct);

    // Enable TIM1 peripheral and PWM output
    TIM_Cmd(TIM1, ENABLE);
    TIM_CtrlPWMOutputs(TIM1, ENABLE);

}

/**
 * Create a general counter with 1 tick is 1us
 *
 */
static void hal_timer2_init(void)
{
	/*
	// Enable timer 2
	sRCC->RCC_APB1ENR.bits.TIM2EN = 1;

	// Load 0 into auto reload register
	sTIM2->TIMx_ARR.all32 = 0;

	//
	sTIM2->TIMx_CNT.all32 = 0;

	// prescale 50000 (0x) ticks of 20ns is 1ms
	sTIM3->TIMx_PSC.all32 = 0xC350;

	// Timer counter enable
	sTIM2->TIMx_CR1.bits.CEN = 1;
    */
	// Enable TIM2 clock
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	// Initialize TIM2
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_Prescaler = 99; // Prescaler value to achieve 1us resolution
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = 19; // Period value to achieve 1ms interrupt
	TIM_TimeBaseInitStruct.TIM_ClockDivision = 0;
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);

    // Enable TIM2 interrupt
    //TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

	// Enable TIM2
	TIM_Cmd(TIM2, ENABLE);

	//NVIC_SetPriority(TIM2_IRQn, );
	//NVIC_EnableIRQ(TIM2_IRQn);
}

/**
 * Create a general counter with 1 tick is 1ms
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

	// prescale 50000 (0x) ticks of 20ns is 1ms
	sTIM3->TIMx_PSC.all32 = 0xC350;

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

