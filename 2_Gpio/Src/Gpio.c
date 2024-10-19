/*
 * Gpio.c
 *
 *  Created on: Oct 15, 2024
 *      Author: mrbaytar
 */


#include "main.h"

void Discovery_Onboard_Leds_Config(void)
{
	RCC->AHB1ENR |= (1 << 3); // GPIOD Clock Enable

	// IO12 IO13 IO14 IO15 settings
	GPIOD->MODER |= (1 << 24) | (1 << 26) | (1 << 28) | (1 << 30); // General purpose output mode (io12 io13 io14 io15)
	GPIOD->OTYPER &= ~((1 << 12) | (1 << 13) | (1 << 14) | (1 << 15)); // Output push-pull (reset state)
	GPIOD->OSPEEDR |= (3 << 24) | (3 << 26) | (3 << 28) | (3 << 30);  // output speed : Very high speed
	GPIOD->PUPDR &= ~((1 << 24) | (1 << 26) | (1 << 28) | (1 << 30)); // No pull-up, pull-down
}


void Discovery_Onboard_Button_Config(void)
{
	RCC->AHB1ENR |= (1 << 0); // IO port A clock enable

	GPIOA->MODER &= ~((1 << 0) | (1 << 1)); // PA0 Input
	GPIOA->PUPDR |= (1 << 1); // Pull-down register enable
}
