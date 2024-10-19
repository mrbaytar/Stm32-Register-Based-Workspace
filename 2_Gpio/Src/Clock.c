/*
 * Clock.c
 *
 *  Created on: Oct 14, 2024
 *      Author: mrbaytar
 */


#include "Clock.h"

#define PLL_M 	4
#define PLL_N 	168
#define PLL_P 	0  // PLLP = 2

void SysClockConfig(void)
{
	/*************** >>>>>>>>> STEPS FOLLOWED <<<<<<<<< ***************
	 *
	 * 1. ENABLE HSE and wait for the HSE to become ready
	 * 2. Set the POWER ENABLE CLOCK and VOLTAGE REGULATOR
	 * 3. Configure the FLASH PREFETCH and the LATENCY Related Settings
	 * 4. Configure the PRESCALARS HCLK, PCLK1, PCLK2
	 * 5. Configure the MAIN PLL
	 * 6. Enable the PLL and wait for it to become ready
	 * 7. Select the Clock Source and wait for it to be set
	 *
	 ******************************************************************/

	// 1. ENABLE HSE and wait for the HSE to become ready
	RCC->CR |= (1 << 16); // HSE oscillator ON
	while(!(RCC->CR & (1 < 17))); // Wait for HSE clock ready flag

	// 2. Set the POWER ENABLE CLOCK and VOLTAGE REGULATOR
	RCC->APB1ENR |= 1 << 28; // Power interface clock enable
	PWR->CR |= 1 << 14; // Regulator voltage scaling output selection (Scale 1 mode)

	/*
	 * Prefetch, Instruction cache, Data cache ENABLE (1 << 8) | (1 << 9) | (1 << 10)
	 * Ratio of the CPU clock period to the flash memory access time is 5 wait states (5 << 0)
	 */
	// 3. Configure the FLASH PREFETCH and the LATENCY Related Settings
	FLASH->ACR = (1 << 8) | (1 << 9) | (1 << 10) | (5 << 0);

	// 4. Configure the PRESCALARS HCLK, PCLK1, PCLK2
	// AHB PR
	RCC->CFGR &= ~(1 << 4); // system clock not divided
	// APB1 PR
	RCC->CFGR |= (5 << 10); // AHB clock divided by 4
	// APB2 PR
	RCC->CFGR |= (4 << 13); // AHB clock divided by 2


	/*
	 * Bit 22 : HSE oscillator clock selected as PLL and PLLI2S clock entry
	 * PLL_M : 4
	 * PLL_N : 168
	 * PLL_P : 0 // PLL_P = 0 == 2.
 	 */
	// 5. Configure the MAIN PLL
	RCC->PLLCFGR = (PLL_M << 0) | (PLL_N << 6) | (PLL_P << 16) | (1 << 22);

	// 6. Enable the PLL and wait for it to become ready
	RCC->CR |= (1 << 24); // PLL ON
	while(!(RCC->CR & (1 << 25))); // Wait for (PLL) clock ready flag

	// 7. Select the Clock Source and wait for it to be set
	RCC->CFGR |= (2 << 0); // HSE oscillator selected as system clock
	while(!(RCC->CFGR & (2 << 2))); // Wait for HSE oscillator used as the system clock

}
