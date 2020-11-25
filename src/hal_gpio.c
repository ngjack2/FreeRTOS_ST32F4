/*
 * hal_gpio.c
 *
 *  Created on: 2 Mar 2020
 *      Author: yaphan.ng
 */
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "systemTypes.h"
#include "asic.h"
#include "hal_gpio.h"
#include "stm32f4xx_gpio.h"

// function prototype


/**
 * Initialize all ports
 *
 */
__externC void hal_gpio_init(void)
{
	// Initialize the port A
	hal_gpioA_init();

	// Initialize the port B
	hal_gpioB_init();

	// Initialize the port C
	//hal_gpioC_init();

}

/**
 * Initialize the portA pin 5 as output
 *
 */
__externC void hal_gpioA_init(void)
{
	// Enable GPIO A
	sRCC->RCC_AHB1ENR.bits.GPIOAEN = 1;

	// Change the mode of GPIOA
	sGPIOA->GPIOx_MODER.bits.MODER5 = 0x01;

	// Change the output type to push-pull state GPIOA
	sGPIOA->GPIOx_OTYPER.bits.OT15 = 0;

	// Change the output speed to low
	sGPIOA->GPIOx_OSPEEDR.bits.OSPEEDR5 = 0x01;

	// Change the GPIOA-5 to no push-pull
	sGPIOA->GPIOx_PUPDR.bits.PUPDR5 = 0x0;
}

/**
 * Initialize port B
 */
__externC void hal_gpioB_init(void)
{
	GPIO_InitTypeDef gpioPinB6;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	memset(&gpioPinB6, 0, sizeof(gpioPinB6));

	gpioPinB6.GPIO_Pin   = GPIO_Pin_6;
	gpioPinB6.GPIO_Mode  = GPIO_Mode_IN;
	gpioPinB6.GPIO_OType = GPIO_OType_PP;
	gpioPinB6.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	gpioPinB6.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOB, &gpioPinB6);
}

/**
 * Initialize the portC pin 5 as input
 *
 */
__externC void hal_gpioC_init(void)
{
/*
	// Enable GPIO C
	sRCC->RCC_AHB1ENR.bits.GPIOCEN = 1;

	// Change the mode of GPIO C
	sGPIOC->GPIOx_MODER.bits.MODER13 = 0;
	sGPIOC->GPIOx_MODER.bits.MODER7  = 1;

	// Change the output type to push-pull state GPIO C
	sGPIOC->GPIOx_OTYPER.bits.OT13 = 0;
	sGPIOC->GPIOx_OTYPER.bits.OT7  = 0;

	// Change the output speed to low
	sGPIOC->GPIOx_OSPEEDR.bits.OSPEEDR13 = 0x01;
	sGPIOC->GPIOx_OSPEEDR.bits.OSPEEDR7  = 0x01;

	// Change the GPIOC-5 to pull-up
	sGPIOC->GPIOx_PUPDR.bits.PUPDR13 = 0x0;
	sGPIOC->GPIOx_PUPDR.bits.PUPDR7  = 0x0;
*/
	//
	// Configure Port C Pin 7 for LED
	//
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

	GPIO_InitTypeDef gpioPinC7;
	memset(&gpioPinC7, 0, sizeof(gpioPinC7));

	gpioPinC7.GPIO_Pin   = GPIO_Pin_7;
	gpioPinC7.GPIO_Mode  = GPIO_Mode_OUT;
	gpioPinC7.GPIO_OType = GPIO_OType_PP;
	gpioPinC7.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	gpioPinC7.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOC, &gpioPinC7);

}

/**
 * Toggle GPIO Port A pin 5
 *
 */
__externC void hal_gpioA_pin5_toggle(void)
{
	sGPIOA->GPIOx_ODR.bits.ODR5 ^= 1;
}

/**
 * Get value from port C pin 13
 *
 */
__externC UINT32 hal_get_gpioC_pin13(void)
{
	return (sGPIOC->GPIOx_IDR.bits.IDR13);
}

