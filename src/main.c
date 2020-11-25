/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "systemTypes.h"
#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "task.h"

#include "hal_clock.h"
#include "hal_timer.h"
#include "hal_gpio.h"
#include "hal_interrupt.h"
#include "distanceMeasure.h"
#include "UartDevice.h"


//extern void initialise_monitor_handles();

TaskHandle_t xTaskHandler[2] = {NULL, NULL};
void printMsg(UINT8 *msg);
void vTask1_Handler(void *params);
void vTask2_Handler(void *params);

//Global Variable
bool UartFree = true;
UINT8 objDistance;

/**
 * Main Loop for the device
 *
 */
INT32 main(void)
{

	// Semi hosting
	//initialise_monitor_handles();

	//printf("Testing \n");
	DWT->CTRL |= (1 << 0); // Enable CYNNT

	// HSI On, PLL Off, HSE OFF, System Clock = 16MHz, cpu_clock = 16MHz
    //RCC_DeInit();


	// Initialize clock speed to 100MHz
	// HSI On, PLL On, HSE OFF, System Clock = 16MHz, cpu_clock = 100MHz
	SystemInit();

	// Update the SystemCoreClock variable
	SystemCoreClockUpdate();

	// Init all Uart ports
	InitializeUartPorts();

	// Init general purpose timer
	hal_timer_init();

	// Init the interrupt for user switch PC13
	hal_setup_interrupt_PC13();

	// Configure and start Segger
	SEGGER_SYSVIEW_Conf();
	SEGGER_SYSVIEW_Start();

	xTaskCreate(vTask1_Handler, "Task-1", configMINIMAL_STACK_SIZE, NULL, 2, &xTaskHandler[0]);

	xTaskCreate(vTask2_Handler, "Task-2", configMINIMAL_STACK_SIZE, NULL, 2, &xTaskHandler[1]);

	vTaskStartScheduler();

	return 0;
}

/**
 * Start Task handing
 *
 */
void vTask1_Handler(void *params)
{
	hal_gpioA_init();

	while(1)
	{
		hal_gpioA_pin5_toggle();
		//GPIO_WriteBit(GPIOC, GPIO_Pin_7, Bit_SET);
		vTaskDelay(pdMS_TO_TICKS(1000));
	}
}

/**
 *
 */
void vTask2_Handler(void *params)
{
    while(1)
    {
		UINT8 usr_msg[250];

		sprintf(usr_msg, "Distance (cm) = %d\n\r", objDistance);
		Uart2SendMsg(usr_msg);

		taskYIELD();
    }
}

/**
 * Interrupt handler for EXTI 13 (User Switch)
 */
void EXTI15_10_IRQHandler(void)
{
	traceISR_ENTER();

	//1. clear the interrupt pending bit of the EXTI line (13)
	EXTI_ClearITPendingBit(EXTI_Line13);

	objDistance = MeasureDistance();

	traceISR_EXIT();

}


