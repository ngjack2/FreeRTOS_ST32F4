/*
 * hal_flash.c
 *
 *  Created on: Mar 12, 2020
 *      Author: yaphan.ng
 */
#include <stdbool.h>
#include "systemTypes.h"
#include "asic.h"
#include "hal_flash.h"


/**
 * Set the latency wait state for flash due to clock difference
 *
 */
__externC void hal_flash_latency(UINT32 latency)
{
	sFLASH->FLASH_ACR.bits.LATENCY = latency;
}

/**
 * Data cache system control
 *
 */
__externC void hal_data_cache_control(bool enable)
{
	sFLASH->FLASH_ACR.bits.DCEN = enable ? 1 : 0;
}

/**
 * Instruction cache system control
 */
__externC void hal_instruction_cache_control(bool enable)
{
	sFLASH->FLASH_ACR.bits.ICEN = enable ? 1 : 0;
}

/**
 * Prefetch feature control
 *
 */
__externC void hal_prefetch_cache_control(bool enable)
{
	sFLASH->FLASH_ACR.bits.PRFTEN = enable ? 1 : 0;
}
