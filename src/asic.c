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
// for APB1 Base Address
//
#define APB1_BASE_ADDR 0x40000000UL

// for TIMx base address
volatile tTIMx* sTIM2   = (volatile tTIMx*)(APB1_BASE_ADDR);
volatile tTIMx* sTIM3   = (volatile tTIMx*)(APB1_BASE_ADDR + 0x0400UL);
volatile tTIMx* sTIM4   = (volatile tTIMx*)(APB1_BASE_ADDR + 0x0800UL);
volatile tTIMx* sTIM5   = (volatile tTIMx*)(APB1_BASE_ADDR + 0x0C00UL);
volatile tTIMx* sTIM6   = (volatile tTIMx*)(APB1_BASE_ADDR + 0x1000UL);
volatile tTIMx* sTIM7   = (volatile tTIMx*)(APB1_BASE_ADDR + 0x1400UL);
volatile tTIMx* sTIM12  = (volatile tTIMx*)(APB1_BASE_ADDR + 0x1800UL);
volatile tTIMx* sTIM13  = (volatile tTIMx*)(APB1_BASE_ADDR + 0x1C00UL);
volatile tTIMx* sTIM14  = (volatile tTIMx*)(APB1_BASE_ADDR + 0x2000UL);


//
// for APB2 Base Address
//
#define APB2_BASE_ADDR 0x40010000UL

volatile tTIMx* sTIM1   = (volatile tTIMx*)(APB2_BASE_ADDR);
volatile tTIMx* sTIM8   = (volatile tTIMx*)(APB2_BASE_ADDR + 0x0400UL);


//
// for AHB1 Base Address
//
#define AHB1_BASE_ADDR 0x40020000UL

// for GPIOx base address
volatile tGPIO* sGPIOA = (volatile tGPIO*)(AHB1_BASE_ADDR);
volatile tGPIO* sGPIOB = (volatile tGPIO*)(AHB1_BASE_ADDR + 0x0400UL);
volatile tGPIO* sGPIOC = (volatile tGPIO*)(AHB1_BASE_ADDR + 0x0800UL);
volatile tGPIO* sGPIOD = (volatile tGPIO*)(AHB1_BASE_ADDR + 0x0C00UL);
volatile tGPIO* sGPIOE = (volatile tGPIO*)(AHB1_BASE_ADDR + 0x1000UL);
volatile tGPIO* sGPIOF = (volatile tGPIO*)(AHB1_BASE_ADDR + 0x1400UL);
volatile tGPIO* sGPIOG = (volatile tGPIO*)(AHB1_BASE_ADDR + 0x1800UL);
volatile tGPIO* sGPIOH = (volatile tGPIO*)(AHB1_BASE_ADDR + 0x1C00UL);


//
// for RCC
//
#define RCC_BASE_ADDR 0x40023800UL

volatile tRCC*  sRCC   = (volatile tRCC*) RCC_BASE_ADDR;


