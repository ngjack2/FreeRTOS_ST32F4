/*
 * asic.h
 *
 *  Created on: Feb 27, 2020
 *      Author: yaphan.ng
 */

#ifndef ASIC_H_
#define ASIC_H_

#include "systemTypes.h"

typedef struct
{
	union // FLASH_ACR
	{
		UINT32 all32;
		struct
		{
			UINT32 LATENCY : 4;
			UINT32 RSVD_4  : 4;
			UINT32 PRFTEN  : 1;
			UINT32 ICEN    : 1;
			UINT32 DCEN    : 1;
			UINT32 ICRST   : 1;
			UINT32 DCRST   : 1;
			UINT32 RSVD_13 : 19;
		}bits;

	}FLASH_ACR;

	union // FLASH_KEYR
	{
		UINT32 all32;
	}FLASH_KEYR;

	union // FLASH_OPTKEYR
	{
		UINT32 all32;
	}FLASH_OPTKEYR;

	union // FLASH_SR
	{
		UINT32 all32;
		struct
		{
			UINT32 EOP     : 1;
			UINT32 OPERR   : 4;
			UINT32 RSVD_2  : 2;
			UINT32 WRPERR  : 1;
			UINT32 PGAERR  : 1;
			UINT32 PGPERR  : 1;
			UINT32 PGSERR  : 1;
			UINT32 RDERR   : 1;
			UINT32 RSVD_9  : 7;
			UINT32 BSY     : 1;
			UINT32 RSVD_13 : 15;
		}bits;

	}FLASH_SR;

	union // FLASH_CR
	{
		UINT32 all32;
		struct
		{
			UINT32 PG      : 1;
			UINT32 SER     : 1;
			UINT32 MER     : 1;
			UINT32 SNB     : 4;
			UINT32 RSVD_7  : 1;
			UINT32 PSIZE   : 2;
			UINT32 RSVD_10 : 6;
			UINT32 STRT    : 1;
			UINT32 RSVD_17 : 7;
			UINT32 EOPIE   : 1;
			UINT32 ERRIE   : 1;
			UINT32 RSVD_13 : 5;
			UINT32 LOCK    : 1;
		}bits;

	}FLASH_CR;

	union //FLASH_OPTCR
	{
		UINT32 all32;
		struct
		{
			UINT32 OPTLO      : 1;
			UINT32 OPTST      : 1;
			UINT32 BOR_LEV    : 2;
			UINT32 RSVD_4     : 1;
			UINT32 WDG_SW     : 1;
			UINT32 nRST_STOP  : 1;
			UINT32 nRST_STDBY : 1;
			UINT32 RDP        : 8;
			UINT32 nWRP       : 8;
			UINT32 RSVD_24    : 7;
			UINT32 SPRMOD     : 1;
		}bits;

	}FLASH_OPTCR;

}tFLASH;

typedef struct
{
	union // PWR_CR
	{
		UINT32 all32;
		struct
		{
			UINT32 LPDS    : 1;
			UINT32 PDDS    : 1;
			UINT32 CWUF    : 1;
			UINT32 CSBF    : 1;
			UINT32 PVDE    : 1;
			UINT32 PLS     : 3;
			UINT32 DBP     : 1;
			UINT32 FPDS    : 1;
			UINT32 LPLVDS  : 1;
			UINT32 MRLVSD  : 1;
			UINT32 RSVD_12 : 1;
			UINT32 ADCDC1  : 1;
			UINT32 VOS     : 2;
			UINT32 RSVD_16 : 4;
			UINT32 FMSSR   : 1;
			UINT32 FISSR   : 1;
			UINT32 RSVD_22 : 10;
		}bits;

	}PWR_CR;

	union // PWR_CSR
	{
		UINT32 all32;
		struct
		{
			UINT32 WUF     : 1;
			UINT32 SBF     : 1;
			UINT32 PVDO    : 1;
			UINT32 BRR     : 1;
			UINT32 RSVD_4  : 4;
			UINT32 EWUP    : 1;
			UINT32 BRE     : 1;
			UINT32 RSVD_10 : 4;
			UINT32 VOSRDY  : 1;
			UINT32 RSVD_15 : 17;

		}bits;

	}PWR_CSR;
}tPWR;

typedef struct
{
	union //RCC_CR
	{
		UINT32 all32;
		struct
		{
			UINT32 HSION     : 1;
			UINT32 HSIRDY    : 1;
			UINT32 RES       : 1;
			UINT32 HSITRIM   : 5;
			UINT32 HSICAL    : 8;
			UINT32 HSE_ON    : 1;
			UINT32 HSERDY    : 1;
			UINT32 HSEBYP    : 1;
			UINT32 CSSON     : 1;
			UINT32 RSVD_20   : 4;
			UINT32 PLLON     : 1;
			UINT32 PLLRDY    : 1;
			UINT32 PLLI2SON  : 1;
			UINT32 PLLI2SRDY : 1;
			UINT32 RSVD_28   : 4;
		}bits;

	}RCC_CR;

	union //RCC_PLLCFGR
	{
		UINT32 all32;
		struct
		{
			UINT32 PLLM    : 6;
			UINT32 PLLN    : 9;
			UINT32 RSVD_15 : 1;
			UINT32 PLLP    : 2;
			UINT32 RSVD_18 : 4;
			UINT32 PLLSRC  : 1;
			UINT32 RSVD_23 : 1;
			UINT32 PLLQ    : 4;
			UINT32 RSVD_28 : 4;
		}bits;

	}RCC_PLLCFGR;

	union // RCC_CFGR
	{
		UINT32 all32;
		struct
		{
			UINT32 SW       : 2;
			UINT32 SWS0     : 1;
			UINT32 SWS1     : 1;
			UINT32 HPRE     : 4;
			UINT32 RSVD_8   : 2;
			UINT32 PPRE1    : 3;
			UINT32 PPRE2    : 3;
			UINT32 RTCPRE   : 5;
			UINT32 MCO1     : 2;
			UINT32 I2SSCR   : 1;
			UINT32 MCO1_PRE : 3;
			UINT32 MCO2_PRE : 3;
			UINT32 MCO2     : 2;
		}bits;

	}RCC_CFGR;

	union // RCC_CIR
	{
		UINT32 all32;
		struct
		{
			UINT32 LSIRDYF    : 1;
			UINT32 LSERDYF    : 1;
			UINT32 HSIRDYF    : 1;
			UINT32 HSERDYF    : 1;
			UINT32 PLLRDYF    : 1;
			UINT32 PLL2SRDYF  : 1;
			UINT32 RSVD_6     : 1;
			UINT32 CSSF       : 1;
			UINT32 LSIRDYIE   : 1;
			UINT32 LSERDYIE   : 1;
			UINT32 HSIRDYIE   : 1;
			UINT32 HSERDYIE   : 1;
			UINT32 PLLRDYIE   : 1;
			UINT32 PLL2SRDYIE : 1;
			UINT32 RSVD_14    : 2;
			UINT32 LSIRDYC    : 1;
			UINT32 LSERDYC    : 1;
			UINT32 HSIRDYC    : 1;
			UINT32 HSERDYC    : 1;
			UINT32 PLLRDYC    : 1;
			UINT32 PLL2SRDYC  : 1;
			UINT32 RSVD_22    : 1;
			UINT32 CSSC       : 1;
			UINT32 RSVD_24    : 8;
		}bits;

	}RCC_CIR;

	union // RCC_AHB1RSTR
	{
		UINT32 all32;
		struct
		{
			UINT32 GPIOARST : 1;
			UINT32 GPIOBRST : 1;
			UINT32 GPIOCRST : 1;
			UINT32 GPIODRST : 1;
			UINT32 GPIOERST : 1;
			UINT32 RSVD_5   : 2;
			UINT32 GPIOHRST : 1;
			UINT32 RSVD_8   : 4;
			UINT32 CRCRST   : 1;
			UINT32 RSVD_13  : 8;
			UINT32 DMA1RST  : 1;
			UINT32 DMA2RST  : 1;
			UINT32 RSVD_23  : 9;
		}bits;

	}RCC_AHB1RSTR;

	union // RCC_AHB2RSTR
	{
		UINT32 all32;
		struct
		{
			UINT32 RSVD_0   : 7;
			UINT32 OTGFSRST : 1;
			UINT32 RSVD_8   : 24;
		}bits;

	}RCC_AHB2RSTR;

	UINT32 AUTOPAD_R40023818_R4002381C[2];

	union // RCC_APB1RSTR
	{
		UINT32 all32;
		struct
		{
			UINT32 TIM2RST   : 1;
			UINT32 TIM3RST   : 1;
			UINT32 TIM4RST   : 1;
			UINT32 TIM5RST   : 1;
			UINT32 RSVD_4    : 7;
			UINT32 WWDGRST   : 1;
			UINT32 RSVD_12   : 2;
			UINT32 SPI2RST   : 1;
			UINT32 SPI3RST   : 1;
			UINT32 RSVD_16   : 1;
			UINT32 USART2RST : 1;
			UINT32 RSVD_18   : 3;
			UINT32 I2C1RST   : 1;
			UINT32 I2C2RST   : 1;
			UINT32 I2C3RST   : 1;
			UINT32 RSVD_24   : 4;
			UINT32 PWRRST    : 1;
			UINT32 RSVD_29   : 3;
		}bits;

	}RCC_APB1RSTR;

	union // RCC_APB2RSTR
	{
		UINT32 all32;
		struct
		{
			UINT32 TIM1RST   : 1;
			UINT32 RSVD_1    : 3;
			UINT32 USART1RST : 1;
			UINT32 USART6RST : 1;
			UINT32 RSVD_4    : 2;
			UINT32 ADC1RST   : 1;
			UINT32 RSVD_9    : 2;
			UINT32 SDIORST   : 1;
			UINT32 SPI1RST   : 1;
			UINT32 SPI4RST   : 1;
			UINT32 SYSCFGRST : 1;
			UINT32 RSVD_15   : 1;
			UINT32 TIM9RST   : 1;
			UINT32 TIM10RST  : 1;
			UINT32 TIM11RST  : 1;
			UINT32 RSVD_19   : 1;
			UINT32 SPI5RST   : 1;
			UINT32 RSVD_21   : 11;
		}bits;

	}RCC_APB2RSTR;

	UINT32 AUTOPAD_R40023828_R4002382C[2];

	union // RCC_AHB1ENR
	{
		UINT32 all32;
		struct
		{
			UINT32 GPIOAEN : 1;
			UINT32 GPIOBEN : 1;
			UINT32 GPIOCEN : 1;
			UINT32 GPIODEN : 1;
			UINT32 GPIOEEN : 1;
			UINT32 RSVD_5  : 2;
			UINT32 GPIOHEN : 1;
			UINT32 RSVD_6  : 4;
			UINT32 CRCEN   : 1;
			UINT32 RSVD_13 : 8;
			UINT32 DMA1EN  : 1;
			UINT32 DMA2EN  : 1;
			UINT32 RSVD_23 : 9;
		}bits;

	}RCC_AHB1ENR;

	union // RCC_AHB2ENR
	{
		UINT32 all32;
		struct
		{
			UINT32 RSVD_0  : 7;
			UINT32 OTGFSEN : 1;
			UINT32 RSVD_8  : 24;
		}bits;

	}RCC_AHB2ENR;

	UINT32 AUTOPAD_R40023838_R4002383C[2];

	union // RCC_APB1ENR
	{
		UINT32 all32;
		struct
		{
			UINT32 TIM2EN   : 1;
			UINT32 TIM3EN   : 1;
			UINT32 TIM4EN   : 1;
			UINT32 TIM5EN   : 1;
			UINT32 RSVD_4   : 7;
			UINT32 WWDGEN   : 1;
			UINT32 RSVD_12  : 2;
			UINT32 SPI2EN   : 1;
			UINT32 SPI3EN   : 1;
			UINT32 RSVD_16  : 1;
			UINT32 USART2EN : 1;
			UINT32 RSVD_18  : 3;
			UINT32 I2C1EN   : 1;
			UINT32 I2C2EN   : 1;
			UINT32 I2C3EN   : 1;
			UINT32 RSVD_24  : 4;
			UINT32 PWREN    : 1;
			UINT32 RSVD_29  : 3;
		}bits;

	}RCC_APB1ENR;

	union // RCC_APB2ENR
	{
		UINT32 all32;
		struct
		{
			UINT32 TIM1EN   : 1;
			UINT32 RSVD_1   : 3;
			UINT32 USART1EN : 1;
			UINT32 USART6EN : 1;
			UINT32 RSVD_6   : 2;
			UINT32 ADC1EN   : 1;
			UINT32 RSVD_9   : 2;
			UINT32 SDIOEN   : 1;
			UINT32 SPI1EN   : 1;
			UINT32 SPI4EN   : 1;
			UINT32 SYSCFGEN : 1;
			UINT32 RSVD_15  : 1;
			UINT32 TIM9EN   : 1;
			UINT32 TIM10EN  : 1;
			UINT32 TIM11EN  : 1;
			UINT32 RSVD_19  : 1;
			UINT32 SPI5EN   : 1;
			UINT32 RSVD_21  : 11;
		}bits;

	}RCC_APB2ENR;

	UINT32 AUTOPAD_R40023848_R4002384C[2];

	union // RCC_AHB1LPENR
	{
		UINT32 all32;
		struct
		{
			UINT32 GPIOALPEN : 1;
			UINT32 GPIOBLPEN : 1;
			UINT32 GPIOCLPEN : 1;
			UINT32 GPIODLPEN : 1;
			UINT32 GPIOELPEN : 1;
			UINT32 RSVD_9    : 2;
			UINT32 GPIOHLPEN : 1;
			UINT32 RSVD_8    : 4;
			UINT32 CRCLPEN   : 1;
			UINT32 RSVD_13   : 2;
			UINT32 FLITFLPEN : 1;
			UINT32 SRAM1LPEN : 1;
			UINT32 RSVD_17   : 4;
			UINT32 DMA1LPEN  : 1;
			UINT32 DMA2LPEN  : 1;
			UINT32 RSVD_23   : 9;
		}bits;

	}RCC_AHB1LPENR;

	union // RCC_AHB2LPENR
	{
		UINT32 all32;
		struct
		{
			UINT32 RSVD_0    : 7;
			UINT32 OTGFSLPEN : 1;
			UINT32 RSVD_8    : 24;
		}bits;

	}RCC_AHB2LPENR;

	UINT32 AUTOPAD_R40023858_R4002385C[2];

	union // RCC_APB1LPENR
	{
		UINT32 all32;
		struct
		{
			UINT32 TIM2LPEN   : 1;
			UINT32 TIM3LPEN   : 1;
			UINT32 TIM4LPEN   : 1;
			UINT32 TIM5LPEN   : 1;
			UINT32 RSVD_4     : 7;
			UINT32 WWDGLPEN   : 1;
			UINT32 RSVD_12    : 2;
			UINT32 SPI2LPEN   : 1;
			UINT32 SPI3LPEN   : 1;
			UINT32 RSVD_16    : 1;
			UINT32 USART2LPEN : 1;
			UINT32 RSVD_18    : 3;
			UINT32 I2C1LPEN   : 1;
			UINT32 I2C2LPEN   : 1;
			UINT32 I2C3LPEN   : 1;
			UINT32 RSVD_24    : 4;
			UINT32 PWRLPEN    : 1;
			UINT32 RSVD_29    : 3;
		}bits;

	}RCC_APB1LPENR;

	union // RCC_APB2LPENR
	{
		UINT32 all32;
		struct
		{
			UINT32 TIM1LPEN   : 1;
			UINT32 RSVD_1     : 3;
			UINT32 USART1LPEN : 1;
			UINT32 USART6LPEN : 1;
			UINT32 RSVD_6     : 2;
			UINT32 ADC1LPEN   : 1;
			UINT32 RSVD_9     : 2;
			UINT32 SDIOLPEN   : 1;
			UINT32 SPI1LPEN   : 1;
			UINT32 SPI4LPEN   : 1;
			UINT32 SYSCFGLPEN : 1;
			UINT32 RSVD_15    : 1;
			UINT32 TIM9LPEN   : 1;
			UINT32 TIM10LPEN  : 1;
			UINT32 TIM11LPEN  : 1;
			UINT32 RSVD_19    : 1;
			UINT32 SPI5LPEN   : 1;
			UINT32 RSVD_21    : 11;
		}bits;

	}RCC_APB2LPENR;

	UINT32 AUTOPAD_R40023868_R4002386C[2];

	union // RCC_BDCR
	{
		UINT32 all32;
		struct
		{
			UINT32 LSEON   : 1;
			UINT32 LSERDY  : 3;
			UINT32 LSEBYP  : 1;
			UINT32 LSEMOD  : 1;
			UINT32 RSVD_4  : 4;
			UINT32 RTCSEL  : 2;
			UINT32 RSVD_10 : 5;
			UINT32 RTCEN   : 1;
			UINT32 BDRST   : 1;
			UINT32 RSVD_17 : 15;
		}bits;

	}RCC_BDCR;

	union // RCC_CSR
	{
		UINT32 all32;
		struct
		{
			UINT32 LSION    : 1;
			UINT32 LSIRDY   : 1;
			UINT32 RSVD_2   : 22;
			UINT32 RMVF     : 1;
			UINT32 BORRSTF  : 1;
			UINT32 PINRSTF  : 1;
			UINT32 PORRSTF  : 1;
			UINT32 SFTRSTF  : 1;
			UINT32 IWDGRSTF : 1;
			UINT32 WWDGRSTF : 1;
			UINT32 LPWRRSTF : 1;
		}bits;

	}RCC_CSR;

	UINT32 AUTOPAD_R40023878_R4002387C[2];

	union //RCC_SCGR
	{
		UINT32 all32;
		struct
		{
			UINT32 MODPER    : 13;
			UINT32 INCSTEP   : 15;
			UINT32 RSVD_28   : 2;
			UINT32 SPREADSEL : 1;
			UINT32 SSCGEN    : 1;
		}bits;

	}RCC_SSCGR;

	union // RCC_PLLI2SCFGR
	{
		UINT32 all32;
		struct
		{
			UINT32 PLL2SM   : 6;
			UINT32 PLL2SN   : 9;
			UINT32 RSVD_15  : 13;
			UINT32 PLLI2SR0 : 1;
			UINT32 PLLI2SR1 : 1;
			UINT32 PLLI2SR2 : 1;
			UINT32 RSVD_31  : 1;
		}bits;

	}RCC_PLLI2SCFGR;

	UINT32 AUTOPAD_R40023888;

	union // RCC_DCKCFGR
	{
		UINT32 all32;
		struct
		{
			UINT32 RSVD_0   : 24;
			UINT32 TIMPRE   : 1;
			UINT32 RSVD_25  : 7;
		}bits;

	}RCC_DCKCFGR;

}tRCC;

typedef struct
{
	union // GPIOx_MODER
	{
		UINT32 all32;
		struct
		{
			UINT32 MODER0  : 2;
			UINT32 MODER1  : 2;
			UINT32 MODER2  : 2;
			UINT32 MODER3  : 2;
			UINT32 MODER4  : 2;
			UINT32 MODER5  : 2;
			UINT32 MODER6  : 2;
			UINT32 MODER7  : 2;
			UINT32 MODER8  : 2;
			UINT32 MODER9  : 2;
			UINT32 MODER10 : 2;
			UINT32 MODER11 : 2;
			UINT32 MODER12 : 2;
			UINT32 MODER13 : 2;
			UINT32 MODER14 : 2;
			UINT32 MODER15 : 2;
		}bits;

	}GPIOx_MODER;

	union // GPIOx_OTYPER
	{
		UINT32 all32;
		struct
		{
			UINT32 OT0     : 1;
			UINT32 OT1     : 1;
			UINT32 OT2     : 1;
			UINT32 OT3     : 1;
			UINT32 OT4     : 1;
			UINT32 OT5     : 1;
			UINT32 OT6     : 1;
			UINT32 OT7     : 1;
			UINT32 OT8     : 1;
			UINT32 OT9     : 1;
			UINT32 OT10    : 1;
			UINT32 OT11    : 1;
			UINT32 OT12    : 1;
			UINT32 OT13    : 1;
			UINT32 OT14    : 1;
			UINT32 OT15    : 1;
			UINT32 RSVD_16 : 16;
		}bits;

	}GPIOx_OTYPER;

	union // GPIOx_OSPEEDR
	{
		UINT32 all32;
		struct
		{
			UINT32 OSPEEDR0  : 2;
			UINT32 OSPEEDR1  : 2;
			UINT32 OSPEEDR2  : 2;
			UINT32 OSPEEDR3  : 2;
			UINT32 OSPEEDR4  : 2;
			UINT32 OSPEEDR5  : 2;
			UINT32 OSPEEDR6  : 2;
			UINT32 OSPEEDR7  : 2;
			UINT32 OSPEEDR8  : 2;
			UINT32 OSPEEDR9  : 2;
			UINT32 OSPEEDR10 : 2;
			UINT32 OSPEEDR11 : 2;
			UINT32 OSPEEDR12 : 2;
			UINT32 OSPEEDR13 : 2;
			UINT32 OSPEEDR14 : 2;
			UINT32 OSPEEDR15 : 2;
		}bits;

	}GPIOx_OSPEEDR;

	union // GPIOx_PUPDR
	{
		UINT32 all32;
		struct
		{
			UINT32 PUPDR0  : 2;
			UINT32 PUPDR1  : 2;
			UINT32 PUPDR2  : 2;
			UINT32 PUPDR3  : 2;
			UINT32 PUPDR4  : 2;
			UINT32 PUPDR5  : 2;
			UINT32 PUPDR6  : 2;
			UINT32 PUPDR7  : 2;
			UINT32 PUPDR8  : 2;
			UINT32 PUPDR9  : 2;
			UINT32 PUPDR10 : 2;
			UINT32 PUPDR11 : 2;
			UINT32 PUPDR12 : 2;
			UINT32 PUPDR13 : 2;
			UINT32 PUPDR14 : 2;
			UINT32 PUPDR15 : 2;
		}bits;

	}GPIOx_PUPDR;

	union // GPIOx_IDR
	{
		UINT32 all32;
		struct
		{
			UINT32 IDR0     : 1;
			UINT32 IDR1     : 1;
			UINT32 IDR2     : 1;
			UINT32 IDR3     : 1;
			UINT32 IDR4     : 1;
			UINT32 IDR5     : 1;
			UINT32 IDR6     : 1;
			UINT32 IDR7     : 1;
			UINT32 IDR8     : 1;
			UINT32 IDR9     : 1;
			UINT32 IDR10    : 1;
			UINT32 IDR11    : 1;
			UINT32 IDR12    : 1;
			UINT32 IDR13    : 1;
			UINT32 IDR14    : 1;
			UINT32 IDR15    : 1;
			UINT32 RSVD_16 : 16;
		}bits;

	}GPIOx_IDR;

	union // GPIOx_ODR
	{
		UINT32 all32;
		struct
		{
			UINT32 ODR0     : 1;
			UINT32 ODR1     : 1;
			UINT32 ODR2     : 1;
			UINT32 ODR3     : 1;
			UINT32 ODR4     : 1;
			UINT32 ODR5     : 1;
			UINT32 ODR6     : 1;
			UINT32 ODR7     : 1;
			UINT32 ODR8     : 1;
			UINT32 ODR9     : 1;
			UINT32 ODR10    : 1;
			UINT32 ODR11    : 1;
			UINT32 ODR12    : 1;
			UINT32 ODR13    : 1;
			UINT32 ODR14    : 1;
			UINT32 ODR15    : 1;
			UINT32 RSVD_16 : 16;
		}bits;

	}GPIOx_ODR;

	union // GPIOx_BSRR
	{
		UINT32 all32;
		struct
		{
			UINT32 BS0   : 1;
			UINT32 BS1   : 1;
			UINT32 BS2   : 1;
			UINT32 BS3   : 1;
			UINT32 BS4   : 1;
			UINT32 BS5   : 1;
			UINT32 BS6   : 1;
			UINT32 BS7   : 1;
			UINT32 BS8   : 1;
			UINT32 BS9   : 1;
			UINT32 BS10  : 1;
			UINT32 BS11  : 1;
			UINT32 BS12  : 1;
			UINT32 BS13  : 1;
			UINT32 BS14  : 1;
			UINT32 BS15  : 1;
			UINT32 BR0   : 1;
			UINT32 BR1   : 1;
			UINT32 BR2   : 1;
			UINT32 BR3   : 1;
			UINT32 BR4   : 1;
			UINT32 BR5   : 1;
			UINT32 BR6   : 1;
			UINT32 BR7   : 1;
			UINT32 BR8   : 1;
			UINT32 BR9   : 1;
			UINT32 BR10  : 1;
			UINT32 BR11  : 1;
			UINT32 BR12  : 1;
			UINT32 BR13  : 1;
			UINT32 BR14  : 1;
			UINT32 BR15  : 1;
		}bits;

	}GPIOx_BSRR;

	union // GPIOx_LCKR
	{
		UINT32 all32;
		struct
		{
			UINT32 LCK0    : 1;
			UINT32 LCK1    : 1;
			UINT32 LCK2    : 1;
			UINT32 LCK3    : 1;
			UINT32 LCK4    : 1;
			UINT32 LCK5    : 1;
			UINT32 LCK6    : 1;
			UINT32 LCK7     : 1;
			UINT32 LCK8    : 1;
			UINT32 LCK9    : 1;
			UINT32 LCK10   : 1;
			UINT32 LCK11   : 1;
			UINT32 LCK12   : 1;
			UINT32 LCK13   : 1;
			UINT32 LCK14   : 1;
			UINT32 LCK15   : 1;
			UINT32 LCK16   : 1;
			UINT32 RSVD_17 : 15;
		}bits;

	}GPIOx_LCKR;

	union // GPIOx_AFRL
	{
		UINT32 all32;
		struct
		{
			UINT32 AFRL0 : 3;
			UINT32 AFRL1 : 3;
			UINT32 AFRL2 : 3;
			UINT32 AFRL3 : 3;
			UINT32 AFRL4 : 3;
			UINT32 AFRL5 : 3;
			UINT32 AFRL6 : 3;
			UINT32 AFRL7 : 3;

		}bits;

	}GPIOx_AFRL;

	union // GPIOx_AFRH
	{
		UINT32 all32;
		struct
		{
			UINT32 AFRH0 : 3;
			UINT32 AFRH1 : 3;
			UINT32 AFRH2 : 3;
			UINT32 AFRH3 : 3;
			UINT32 AFRH4 : 3;
			UINT32 AFRH5 : 3;
			UINT32 AFRH6 : 3;
			UINT32 AFRH7 : 3;

		}bits;

	}GPIOx_AFRH;
}tGPIO;

typedef struct
{
	union // TIMx_CR1
	{
		UINT32 all32;
		struct
		{
			UINT32 CEN     : 1;
			UINT32 UDIS    : 1;
			UINT32 URS     : 1;
			UINT32 OPM     : 1;
			UINT32 DIR     : 1;
			UINT32 CMS     : 2;
			UINT32 ARPE    : 1;
			UINT32 CKD     : 2;
			UINT32 RSVD_10 : 22;
		}bits;

	}TIMx_CR1;

	union // TIMxCR2
	{
		UINT32 all32;
		struct
		{
			UINT32 RSVD_0 : 3;
			UINT32 CCDS   : 1;
			UINT32 MMS    : 3;
			UINT32 TI1S   : 1;
			UINT32 RSVD_8 : 24;
		}bits;

	}TIMx_CR2;

	union // TIMx_SMCR
	{
		UINT32 all32;
		struct
		{
			UINT32 SMS     : 3;
			UINT32 RSVD_3  : 1;
			UINT32 TS      : 3;
			UINT32 MSM     : 1;
			UINT32 ETF     : 4;
			UINT32 ETPS    : 2;
			UINT32 ECE     : 1;
			UINT32 ETP 	   : 1;
			UINT32 RSVD_15 : 17;
		}bits;

	}TIMx_SMCR;

	union // TIMx_DIER
	{
		UINT32 all32;
		struct
		{
			UINT32 UIE     : 1;
			UINT32 CC1IE   : 1;
			UINT32 CC2IE   : 1;
			UINT32 CC3IE   : 1;
			UINT32 CC4IE   : 1;
			UINT32 RSVD_5  : 1;
			UINT32 TIE     : 1;
			UINT32 RSVD_7  : 1;
			UINT32 UDE     : 1;
			UINT32 CC1DE   : 1;
			UINT32 CC2DE   : 1;
			UINT32 CC3DE   : 1;
			UINT32 CC4DE   : 1;
			UINT32 COMDE   : 1;
			UINT32 TDE     : 1;
			UINT32 RSVD_15 : 17;
		}bits;

	}TIMx_DIER;

	union // TIMx_SR
	{
		UINT32 all32;
		struct
		{
			UINT32 UIF     : 1;
			UINT32 CC1IF   : 1;
			UINT32 CC2IF   : 1;
			UINT32 CC3IF   : 1;
			UINT32 CC4IF   : 1;
			UINT32 RSVD_5  : 1;
			UINT32 TIF     : 1;
			UINT32 CC1OF   : 1;
			UINT32 CC2OF   : 1;
			UINT32 CC3OF   : 1;
			UINT32 CC4OF   : 1;
			UINT32 RSVD_13 : 20;
		}bits;

	}TIMx_SR;

    union // TIMx_EGR
	{
		UINT32 all32;
		struct
		{
			UINT32 UG     : 1;
			UINT32 CC1G   : 1;
			UINT32 CC2G   : 1;
			UINT32 CC3G   : 1;
			UINT32 CC4G   : 1;
			UINT32 RSVD_5 : 1;
			UINT32 TG     : 1;
			UINT32 RSVD_7 : 26;
		}bits;

	}TIMx_EGR;

    union // TIMx_CCMR1
	{
    	UINT32 all32;
    	struct
		{
    		UINT32 CC1S    : 2;
    		UINT32 OC1FE   : 1;
    		UINT32 OC1PE   : 1;
    		UINT32 OC1M    : 3;
    		UINT32 OC1CE   : 1;
    		UINT32 CC2S    : 2;
    		UINT32 OC2FE   : 1;
    		UINT32 OC2PE   : 1;
    		UINT32 OC2M    : 3;
    		UINT32 OC2CE   : 1;
    		UINT32 RSVD_16 : 16;
		}bits;

	}TIMx_CCMR1;

    union // TIMx_CCMR2
	{
    	UINT32 all32;
    	struct
		{
    		UINT32 CC3S    : 2;
    		UINT32 OC3FE   : 1;
    		UINT32 OC3PE   : 1;
    		UINT32 OC3M    : 3;
    		UINT32 OC3CE   : 1;
    		UINT32 CC4S    : 2;
    		UINT32 OC4FE   : 1;
    		UINT32 OC4PE   : 1;
    		UINT32 OC4M    : 3;
    		UINT32 OC4CE   : 1;
    		UINT32 RSVD_16 : 16;
		}bits;

	}TIMx_CCMR2;

    union // TIMx_CCER
	{
    	UINT32 all32;
    	struct
		{
    		UINT32 CC1E    : 1;
    		UINT32 CC1P    : 1;
    		UINT32 RSVD_2  : 1;
    		UINT32 CC1NP   : 1;
    		UINT32 CC2E    : 1;
    		UINT32 CC2P    : 1;
    		UINT32 RSVD_6  : 1;
    		UINT32 CC2NP   : 1;
    		UINT32 CC3E    : 1;
    		UINT32 CC3P    : 1;
    		UINT32 RSVD_10 : 1;
    		UINT32 CC3NP   : 1;
    		UINT32 CC4E    : 1;
    		UINT32 CC4P    : 1;
    		UINT32 RSVD_14 : 1;
    		UINT32 CC4NP   : 1;
    		UINT32 RSVD_16 : 16;
		}bits;

	}TIMx_CCER;

	union // TIMx_CNT
	{
		UINT32 all32;
		struct
		{
			UINT16 CNT_L : 16;
			UINT16 CNT_H : 16;
		}bits;

	}TIMx_CNT;

	union // TIMx_PSC
	{
		UINT32 all32;
		struct
		{
			UINT32 PSC     : 16;
			UINT32 RSVD_15 : 16;
		}bits;

	}TIMx_PSC;

	union // TIMx_ARR
	{
		UINT32 all32;
		struct
		{
			UINT32 ARR_L : 16;
			UINT32 ARR_H : 16;
		}bits;

	}TIMx_ARR;

	union // TIMx_CCR1
	{
		UINT32 all32;
		struct
		{
			UINT32 CCR1_L : 16;
			UINT32 CCR1_H : 16;
		}bits;

	}TIMx_CCR1;

	union // TIMx_CCR2
	{
		UINT32 all32;
		struct
		{
			UINT32 CCR2_L : 16;
			UINT32 CCR2_H : 16;
		}bits;

	}TIMx_CCR2;

	union // TIMx_CCR3
	{
		UINT32 all32;
		struct
		{
			UINT32 CCR3_L : 16;
			UINT32 CCR3_H : 16;
		}bits;

	}TIMx_CCR3;

	union // TIMx_CCR4
	{
		UINT32 all32;
		struct
		{
			UINT32 CCR4_L : 16;
			UINT32 CCR4_H : 16;
		}bits;

	}TIMx_CCR4;

	UINT32 AUTOPAD_R40000044;

	union // TIMx_DMA
	{
		UINT32 all32;
		struct
		{
			UINT32 DBA     : 5;
			UINT32 RSVD_5  : 3;
			UINT32 DBL     : 5;
			UINT32 RSVD_13 : 19;
		}bits;

	}TIMx_DMA;

	union // TIMx_DMAR
	{
		UINT32 all32;
		struct
		{
			UINT32 DMAB    : 16;
			UINT32 RSVD_16 : 16;
		}bits;

	}TIMx_DMAR;

	union // TIM2_OR
	{
		UINT32 all32;
		struct
		{
			UINT32 RSVD_0   : 10;
			UINT32 ITR1_RMP : 2;
			UINT32 RSVD_12  : 20;
		}bits;

	}TIM2_OR;

	union // TIM5_OR
	{
		UINT32 all32;
		struct
		{
			UINT32 RSVD_0  : 6;
			UINT32 TI4_RMP : 2;
			UINT32 RSVD_8  : 24;
		}bits;

	}TIM5_OR;
}tTIMx;

extern volatile tFLASH*   sFLASH;
extern volatile tPWR*     sPWR;
extern volatile tRCC*     sRCC;
extern volatile tGPIO*    sGPIOA;
extern volatile tGPIO*    sGPIOB;
extern volatile tGPIO*    sGPIOC;
extern volatile tTIMx*    sTIM2;
extern volatile tTIMx*    sTIM3;
extern volatile tTIMx*    sTIM4;
extern volatile tTIMx*    sTIM5;

#endif /* ASIC_H_ */
