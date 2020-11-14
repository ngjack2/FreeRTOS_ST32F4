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

//extern void initialise_monitor_handles();
static void prvSetupUart(void);
static void prvSetupHardware(void);

TaskHandle_t xTaskHandler[2] = {NULL, NULL};
void printMsg(char *msg);
void vTask1_Handler(void *params);
void vTask2_Handler(void *params);

//Global Variable
bool UartFree = true;


/**
 * Main Loop for the device
 *
 */
int main(void)
{

	// Semi hosting
	//initialise_monitor_handles();

	//printf("Testing \n");
	DWT->CTRL |= (1 << 0); // Enable CYNNT

	// HSI On, PLL Off, HSE OFF, System Clock = 16MHz, cpu_clock = 16MHz
    RCC_DeInit();

	// Update the SystemCoreClock variable
	SystemCoreClockUpdate();

	//printf("Testing 2\n");
	prvSetupHardware();

	// Configure and start Segger
	SEGGER_SYSVIEW_Conf();
	SEGGER_SYSVIEW_Start();

	xTaskCreate(vTask1_Handler, "Task-1", configMINIMAL_STACK_SIZE, NULL, 2, &xTaskHandler[0]);

	xTaskCreate(vTask2_Handler, "Task-2", configMINIMAL_STACK_SIZE, NULL, 2, &xTaskHandler[1]);

	vTaskStartScheduler();

}

void vTask1_Handler(void *params)
{
    while(1)
    {
    	if (UartFree == true)
    	{
    		UartFree = false;
			char usr_msg[250];
			sprintf(usr_msg, "This is task 1\n\r");
			printMsg(usr_msg);
			UartFree = true;
			taskYIELD();
    	}
    }
}

void vTask2_Handler(void *params)
{
    while(1)
    {
    	if (UartFree == true)
    	{
    		UartFree = false;
			char usr_msg[250];
			sprintf(usr_msg, "This is task 2\n\r");
			printMsg(usr_msg);
			UartFree = true;
			taskYIELD();
    	}
    }
}

static void prvSetupUart(void)
{
	GPIO_InitTypeDef gpio_uart_pins;
	USART_InitTypeDef uart2_init;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	memset(&gpio_uart_pins, 0, sizeof(gpio_uart_pins));
	gpio_uart_pins.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
	gpio_uart_pins.GPIO_Mode = GPIO_Mode_AF;
	gpio_uart_pins.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &gpio_uart_pins);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);

	memset(&uart2_init, 0, sizeof(uart2_init));
	uart2_init.USART_BaudRate = 115200;
	uart2_init.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	uart2_init.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	uart2_init.USART_Parity = USART_Parity_No;
	uart2_init.USART_StopBits = USART_StopBits_1;
	uart2_init.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART2, &uart2_init);

	USART_Cmd(USART2, ENABLE);
}

static void prvSetupHardware(void)
{
	prvSetupUart();
}

void printMsg(char* msg)
{
	for (UINT32 i = 0; i < strlen(msg); i++)
	{
		while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) != SET);
		USART_SendData(USART2, msg[i]);
	}
}
