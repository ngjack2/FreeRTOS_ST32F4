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
#include "semphr.h"
#include "event_groups.h"
#include "queue.h"

#include "hal_clock.h"
#include "hal_timer.h"
#include "hal_gpio.h"
#include "hal_interrupt.h"
#include "HostTask.h"
#include "eventsFlag.h"
#include "AppCommands.h"

//extern void initialise_monitor_handles();

//
// FreeRtos handlers declaration
//
TaskHandle_t xTaskHandler[2] = {NULL, NULL};
//SemaphoreHandle_t xSemaphore;
EventGroupHandle_t xEventFlag;
QueueHandle_t xTaskQueue;

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

	// Initialize the ports for the sensors, and motors
	// Initialize the port A
	hal_gpioA_init();

	// Initialize the port B
	hal_gpioB_init();

	// Initialize the port C
	hal_gpioC_init();

	// Configure and start Segger
	SEGGER_SYSVIEW_Conf();
	SEGGER_SYSVIEW_Start();

	//xSemaphore = xSemaphoreCreateBinary();

	xEventFlag = xEventGroupCreate();

	xTaskQueue = xQueueCreate(TOTAL_TASKS_IN_Q, sizeof(tAppCommand*));
	//xTaskQueue = xQueueCreate(1, sizeof(tCommandQ));
	if (xEventFlag == NULL || xTaskQueue == NULL)
	{
		return 1;
	}

	//xSemaphoreTake(xSemaphore, 0);

	xTaskCreate(HostTask, "Host-Task", configMINIMAL_STACK_SIZE, NULL, 3, &xTaskHandler[0]);

	xTaskCreate(ExecuteHandler, "Execute-Task", configMINIMAL_STACK_SIZE, NULL, 2, &xTaskHandler[1]);

	vTaskStartScheduler();

	return 0;
}


/**
 *
 */
void RtosDelay(UINT32 delayMs)
{
	UINT32 tickCountLocal;

	UINT32 delayInTicks = (delayMs * configTICK_RATE_HZ) / 1000;

	tickCountLocal = xTaskGetTickCount();

	while(xTaskGetTickCount() < (tickCountLocal + delayInTicks));
}


