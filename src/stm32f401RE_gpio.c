
/*
 * stm32f401RE_gpio.c
 *
 *  Created on: Aug 7, 2026
 *      Author: ANEESA
 */

#include "stm32f401RE_gpio.h"
#include "stm32f401RE.h"


void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnOrDi)
{
	if (EnOrDi == ENABLE)
	{
		if (pGPIOx == GPIOA)
		{
			 GPIOA_PCLK_EN();
		}
		else if (pGPIOx == GPIOB)
		{
			 GPIOB_PCLK_EN();
		}
		else if (pGPIOx == GPIOC)
		{
			 GPIOC_PCLK_EN();
		}
		else if (pGPIOx == GPIOD)
		{
			 GPIOD_PCLK_EN();
		}
		else if (pGPIOx == GPIOE)
		{
			GPIOE_PCLK_EN();
		}
		else if (pGPIOx == GPIOH)
		{
			GPIOH_PCLK_EN();
		}

	}
	else
	{

		if (pGPIOx == GPIOA)
		{
			 GPIOA_PCLK_DI();
		}
		else if (pGPIOx == GPIOB)
		{
			 GPIOB_PCLK_DI();
		}
		else if (pGPIOx == GPIOC)
		{
			 GPIOC_PCLK_DI();
		}
		else if (pGPIOx == GPIOD)
		{
			 GPIOD_PCLK_DI();
		}
		else if (pGPIOx == GPIOE)
		{
			GPIOE_PCLK_DI();
		}
		else if (pGPIOx == GPIOH)
		{
			GPIOH_PCLK_DI();
		}
	}

}

void GPIO_Init(GPIO_Handle_t *pGPIOHandle)
{
	    uint32_t temp = 0;

	    // 1. Configure the mode of GPIO pin
	    if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG)
	    {
	        // Non-interrupt mode, mask
	        temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));

	        // Clear the 2 bits first
	        pGPIOHandle->pGPIOx->MODER &= ~(0x3 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));

	        // Set the new value
	        pGPIOHandle->pGPIOx->MODER |= temp;
	    }

	    else
	    {

	    }
	     temp = 0;

	            // Config. the speed
	            temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));

	            // Clear the 2 bits first
	            pGPIOHandle->pGPIOx->OSPEEDR &= ~(0x3  << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));

	            // Set the new value
	            pGPIOHandle->pGPIOx->OSPEEDR |= temp;
	     temp =0;

	     // 3. Configure the pull-up/pull-down settings
	         temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPd << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));

	         pGPIOHandle->pGPIOx->PUPDR &= ~(0x3  << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	         pGPIOHandle->pGPIOx->PUPDR |= temp;
	     temp = 0;

	     // 4. Configure the output type (only 1 bit per pin)
	         temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);

	         pGPIOHandle->pGPIOx->OTYPER &= ~(0x1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	         pGPIOHandle->pGPIOx->OTYPER |= temp;
	     temp = 0;

}

void GPIO_DeInit(GPIO_RegDef_t *pGPIOx)
{
	if (pGPIOx == GPIOA)
	{
		GPIOA_REG_RESET();
	}
	else if (pGPIOx == GPIOB)
		{
			GPIOB_REG_RESET();
		}
	else if (pGPIOx == GPIOC)
		{
			GPIOC_REG_RESET();
		}
	else if (pGPIOx == GPIOD)
		{
			GPIOD_REG_RESET();
		}
	else if (pGPIOx == GPIOE)
		{
			GPIOE_REG_RESET();
		}
	else if (pGPIOx == GPIOH)
		{
			GPIOH_REG_RESET();
		}
}

uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
 uint8_t value;

 // read IDR , shift right by pin number, mas kith 1
   value = (uint8_t)((pGPIOx->IDR >> PinNumber) & 0x00000001);
   return value;
}

void GPIO_WritetoOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value)
{
 if (Value == GPIO_PIN_SET)
 {
	 pGPIOx->ODR |=(1<< PinNumber);
 }
 else
 {
	 pGPIOx->ODR &= ~(1<< PinNumber);
 }
}
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx)
{
	uint16_t value;
	value = ((uint16_t)pGPIOx->IDR);
	return value;

}
void GPIO_WritetoOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value)
{
	pGPIOx->ODR =Value;
}
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
	pGPIOx->ODR ^=(1<< PinNumber);
}
