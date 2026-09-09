/*
 * loopbak.c
 *
 *  Created on: Sep 2, 2026
 *      Author: ANEESA
 */

#include <stdint.h>
#include <string.h>
#include "stm32f401RE.h"


static void delay(void)
{
	for(uint32_t i=0; i<300000; i++);
}


//int main(void)
//{

static void LED_Init()
{

	GPIO_Handle_t Gpioled;
	memset(&Gpioled, 0,sizeof(Gpioled));

	//  configure the led on PA5 of STM32 Nucleo board
	Gpioled.pGPIOx = GPIOA;
	Gpioled.GPIO_PinConfig.GPIO_PinNumber = GPIO_PinNo_5;
	Gpioled.GPIO_PinConfig.GPIO_PinMode   = GPIO_MODE_OUT;
	Gpioled.GPIO_PinConfig.GPIO_PinSpeed  = GPIO_SPEED_LOW ;
	Gpioled.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	Gpioled.GPIO_PinConfig.GPIO_PinPuPd   =  GPIO_NO_PUPD;


	// Enable the clock for GPIO Pin
	GPIO_PeriClockControl(GPIOA,ENABLE);

	// GPIO Pin initialization
	 GPIO_Init(&Gpioled);
}

static void SPI2_GPIO_Init(void)
{
	GPIO_Handle_t spi_pins;
	memset(&spi_pins, 0,sizeof(spi_pins));

	GPIO_PeriClockControl(GPIOB,ENABLE);
	spi_pins.pGPIOx = GPIOB;
	spi_pins.GPIO_PinConfig.GPIO_PinAltFunMode = 5; // AF5= SPI1/SPI2 on f401
	spi_pins.GPIO_PinConfig.GPIO_PinMode   = GPIO_MODE_ALTFUN;
	spi_pins.GPIO_PinConfig.GPIO_PinSpeed  = GPIO_SPEED_HIGH ;
	spi_pins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	spi_pins.GPIO_PinConfig.GPIO_PinPuPd   =  GPIO_NO_PUPD;


	//SCK
	spi_pins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PinNo_13;
	GPIO_Init(&spi_pins);

	//MISO
	spi_pins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PinNo_14;
	GPIO_Init(&spi_pins);

	//MOSI
	spi_pins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PinNo_15;
	GPIO_Init(&spi_pins);

	// NSS pin (PB12) deliberately not configured: we use software slave
    // management (SSM) below, so hardware NSS isn't needed for this test.
}

static void SPI2_Inits(SPI_Handle_t *pSPIHandle)
{
    pSPIHandle->pSPIx = SPI2;
    pSPIHandle->SPIConfig.SPI_DeviceMode = SPI_MASTER_MODE;
    pSPIHandle->SPIConfig.SPI_BusConfig  = SPI_BUS_CONFIG_FD;
    pSPIHandle->SPIConfig.SPI_SCLSpeed   = SPI_SCLK_SPEED_DIV8; // keep it slow/safe for a first test
    pSPIHandle->SPIConfig.SPI_DFF        = SPI_DFF_8BITS;
    pSPIHandle->SPIConfig.SPI_CPOL       = SPI_CPOL_LOW;
    pSPIHandle->SPIConfig.SPI_CPHA       = SPI_CPHA_LOW;
    pSPIHandle->SPIConfig.SPI_SSM        = SPI_SSM_EN;          // software NSS management

    SPI_Init(pSPIHandle);

    pSPIHandle->pSPIx->CR1 |= (1 << SPI_CR1_SSI);
}

int main(void)
{
	    char   tx_buf[] = "Hello SPI Loopback!";
	    uint8_t     rx_buf[sizeof(tx_buf)] = {0};
	    SPI_Handle_t SPI2Handle;

	    LED_Init();
	    SPI2_GPIO_Init();
	    SPI2_Inits(&SPI2Handle);

	    SPI_PeripheralControl(SPI2, ENABLE);

	    for (uint32_t i = 0; i < sizeof(tx_buf); i++)
	        {
	            SPI_SendData(SPI2, (uint8_t *)&tx_buf[i], 1);
	            SPI_RecieveData(SPI2, &rx_buf[i], 1);
	        }

	        SPI_PeripheralControl(SPI2, DISABLE);

	        uint8_t pass = (memcmp(tx_buf, rx_buf, sizeof(tx_buf)) == 0);


	 while(1)
	 {
		 GPIO_ToggleOutputPin(GPIOA,GPIO_PinNo_5);
		 delay();

		 if(!pass)
		 {
			 // fail:blink fast
			 GPIO_ToggleOutputPin(GPIOA,GPIO_PinNo_5);
			 delay();
		 }
	 }

}


