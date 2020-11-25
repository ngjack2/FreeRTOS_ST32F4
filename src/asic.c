/*
 * asic.c
 *
 *  Created on: Feb 28, 2020
 *      Author: yaphan.ng
 */

#include "asic.h"

//
// Flash register base address
//
#define FLASH_BASE_ADDR 0x40023C00UL

volatile tFLASH* sFLASH = (volatile tFLASH*)(FLASH_BASE_ADDR);

//
// Power register base address
//
#define PWR_BASE_ADDR 0x40007000UL

volatile tPWR* sPWR = (volatile tPWR*)(PWR_BASE_ADDR);

//
// for TIMx base address
//
#define TIM2_BASE_ADDR 0x40000000UL

volatile tTIMx* sTIM2  = (volatile tTIMx*)(TIM2_BASE_ADDR);
volatile tTIMx* sTIM3  = (volatile tTIMx*)(TIM2_BASE_ADDR + 0x400UL);
volatile tTIMx* sTIM4  = (volatile tTIMx*)(TIM2_BASE_ADDR + 0x800UL);
volatile tTIMx* sTIM5  = (volatile tTIMx*)(TIM2_BASE_ADDR + 0xC00UL);

//
// for GPIOx
//
#define GPIO_BASE_ADDR 0x40020000UL

volatile tGPIO* sGPIOA = (volatile tGPIO*)(GPIO_BASE_ADDR);
volatile tGPIO* sGPIOB = (volatile tGPIO*)(GPIO_BASE_ADDR + 0x400);
volatile tGPIO* sGPIOC = (volatile tGPIO*)(GPIO_BASE_ADDR + 0x800);

//
// for RCC
//
#define RCC_BASE_ADDR 0x40023800UL

volatile tRCC*  sRCC   = (volatile tRCC*) RCC_BASE_ADDR;


