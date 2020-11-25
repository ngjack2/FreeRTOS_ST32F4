/*
 * hal_flash.h
 *
 *  Created on: Mar 12, 2020
 *      Author: yaphan.ng
 */

#ifndef HAL_FLASH_H_
#define HAL_FLASH_H_

__externC void hal_flash_latency(UINT32 latency);
__externC void hal_data_cache_control(bool enable);
__externC void hal_instruction_cache_control(bool enable);
__externC void hal_prefetch_cache_control(bool enable);

#endif /* HAL_FLASH_H_ */
