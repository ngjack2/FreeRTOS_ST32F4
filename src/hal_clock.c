/*
 * hal_clock.c
 *
 *  Created on: 3 Mar 2020
 *      Author: yaphan.ng
 */
#include <stdbool.h>
#include "systemTypes.h"
#include "asic.h"
#include "hal_clock.h"
#include "hal_flash.h"

//
// Setup PLL to 100MHz
//
struct sPllParam sPll100MHzParam =
{
	200, // N scale
	16,  // M scale
	0,   // P scale
	4,   // Q scale
};

/**
 * Software delay
 *
 */
void software_delay(void)
{
	for (UINT32 loop = 0; loop <= 0xFFFFUL; loop++);
}

/**
 * Initialize the M4 to clock 100MHz
 *
 */
__externC void hal_clock_init(void)
{

	// APB1 Power Enable
	sRCC->RCC_APB1ENR.bits.PWREN = 1;
	software_delay();

	// Enable the power consumption to max for max PLL clock
	sPWR->PWR_CR.bits.VOS = 0x3;
	software_delay();

	// Enable data cache control
	hal_data_cache_control(true);

	// Enable instruction cache control
	hal_instruction_cache_control(true);

	// Enable prefetch feature
	hal_prefetch_cache_control(true);

	//sRCC->RCC_CFGR.bits.MCO1 = 0x03;
	sRCC->RCC_CFGR.bits.MCO2 = 0x03;

	sRCC->RCC_CR.bits.HSICAL = 0x10;

	// N-scale multiplication
	sRCC->RCC_PLLCFGR.bits.PLLN   = sPll100MHzParam.PLLN;

	// PLL clock input scale for HSI
	sRCC->RCC_PLLCFGR.bits.PLLM   = sPll100MHzParam.PLLM;

	// M-scale division of main PLL
	sRCC->RCC_PLLCFGR.bits.PLLP   = sPll100MHzParam.PLLP;

	// Q-scale division of USB-OTG
	sRCC->RCC_PLLCFGR.bits.PLLQ   = sPll100MHzParam.PLLQ;

	// Select HSI as PLL and PLLI2S as clock input
	sRCC->RCC_PLLCFGR.bits.PLLSRC = 0;
	software_delay();

	// Turn on the PLL
	sRCC->RCC_CR.bits.PLLON = 1;

	// Wait for PLL to be lock
	while(!sRCC->RCC_CR.bits.PLLRDY);

	// change latency for flash due to clock frequency
	hal_flash_latency(3);
	software_delay();

	// Switch to PLL clock source
	sRCC->RCC_CFGR.bits.SW = 0x02;
	software_delay();

	// Set prescale for APB1 clock divide by 2
	sRCC->RCC_CFGR.bits.PPRE1 = 0x4;

	// Set prescale for APB2 clock divide by 1
	sRCC->RCC_CFGR.bits.PPRE2 = 0;

	// Set prescale for AHB clock divide by 1
	sRCC->RCC_CFGR.bits.HPRE = 0;

}

