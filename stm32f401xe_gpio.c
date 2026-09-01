
#include "stm32f401xe_gpio.h"

void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx,uint8_t EnorDi)
{
	if (EnorDi == ENABLE)
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
		        }else if (pGPIOx == GPIOB)
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

	 // 1. Configure the mode of GPIO pin

	uint32_t temp=0;   //mask
	 if (pGPIOHandle -> GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG)
	{
		 temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));  //creating mask

		 // Clear the 2 bits first
		        pGPIOHandle->pGPIOx->MODER &= ~(0x3
		                << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));

		        // Set the new value
		                pGPIOHandle->pGPIOx->MODER |= temp;//mask
	}
	else
	{
		//interrupt mode
	}

	temp=0;

	//configure speed
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));  //creating mask

			 // Clear the 2 bits first
			        pGPIOHandle->pGPIOx->OSPEEDR &= ~(0x3
			                << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));

			        // Set the new value
			                pGPIOHandle->pGPIOx->OSPEEDR |= temp;//mask
   temp=0;
// 3. Configure the pull-up/pull-down settings
            temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl
                    << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));

            pGPIOHandle->pGPIOx->PUPDR &= ~(0x3
                    << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
            pGPIOHandle->pGPIOx->PUPDR |= temp;
            temp = 0;

            // 4. Configure the output type (only 1 bit per pin)
                temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType
                        << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);

                pGPIOHandle->pGPIOx->OTYPER &= ~(0x1
                        << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
                pGPIOHandle->pGPIOx->OTYPER |= temp;
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

uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx,uint8_t PinNumber)
{

	uint8_t value;
	//Read IDR,shift right by PinNumber and mask with 1
	value = (uint8_t)((pGPIOx->IDR >> PinNumber) & 0x00000001);
    return value;
}

void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx,uint8_t PinNumber,uint8_t value)
  {
	if(value==GPIO_PIN_SET)
	{
		pGPIOx->ODR |= (1<< PinNumber);
	}
	else
	{
		pGPIOx->ODR &= ~(1<< PinNumber);
	}
}


uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx)
   {

	uint16_t value;
		//Read IDR
		value = (uint16_t)pGPIOx->IDR;
	    return value;
	}

void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx,uint16_t value)
{

	pGPIOx->ODR = value;
}
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber){

	pGPIOx->ODR ^= (1 << PinNumber);
}





