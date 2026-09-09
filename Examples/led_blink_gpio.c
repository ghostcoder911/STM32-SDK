/*
 * main.c
 *
 *  Created on: Aug 31, 2026
 *      Author: ANEESA
 */
#include <stdint.h>

#include "stm32f401RE.h"
#include"stm32f401RE_gpio.h"

void delay(void);

int main(void)
{
	GPIO_Handle_t Gpioled;

	//  configure the led on PA5 of STM32 Nucleo board
	Gpioled.pGPIOx = GPIOA;
	Gpioled.GPIO_PinConfig.GPIO_PinNumber = GPIO_PinNo_5;
	Gpioled.GPIO_PinConfig.GPIO_PinMode   = GPIO_MODE_OUT;
	Gpioled.GPIO_PinConfig.GPIO_PinSpeed  = GPIO_SPEED_FAST ;
	Gpioled.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	Gpioled.GPIO_PinConfig.GPIO_PinPuPd   =  GPIO_NO_PUPD;


	// Enable the clock for GPIO Pin
	GPIO_PeriClockControl(GPIOA,ENABLE);

	// GPIO Pin initialization
	 GPIO_Init(&Gpioled);

	 //LED  Blinking
	 while(1)
	 {
		 GPIO_ToggleOutputPin(GPIOA,GPIO_PinNo_5);
		 delay();
	 }

	 return 0;
}


void delay(void)
{
	for(uint32_t i=0; i< 500000; i++);
}



