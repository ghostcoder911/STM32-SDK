/*
 * stm32f401RE_spi_driver.c
 *
 *  Created on: Aug 18, 2026
 *      Author: ANEESA
 */
#include "stm32f401RE_spi_driver.h"

void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
		{
			if(pSPIx == SPI1)
			{
				SPI1_PCLK_EN();
			}
			else if (pSPIx == SPI2)
			{
				SPI2_PCLK_EN();
			}
			else if (pSPIx == SPI3)
			{
				SPI3_PCLK_EN();
			}
			else if (pSPIx == SPI4)
			{
				SPI4_PCLK_EN();
			}
		}
		else
		{
			if(pSPIx == SPI1)
			{
				SPI1_PCLK_DI();
			}
			else if (pSPIx == SPI2)
			{
				SPI2_PCLK_DI();
			}
			else if (pSPIx == SPI3)
			{
				SPI3_PCLK_DI();
			}
			else if (pSPIx == SPI4)
			{
				SPI4_PCLK_DI();
			}
		}
}

void SPI_Init(SPI_Handle_t *pSPIHandle)
{
	SPI_PeriClockControl(pSPIHandle->pSPIx, ENABLE);
	uint32_t tempreg=0;

	tempreg |= pSPIHandle->SPIConfig.SPI_DeviceMode << SPI_CR1_MSTR;  // configuring the device mode master/slave
	// Bus Configurtaion
	if(pSPIHandle->SPIConfig.SPI_BusConfig ==  SPI_BUS_CONFIG_FD)
	{
		tempreg &=(1 <<  SPI_CR1_BIDIMODE);  // if it is FD Mode then BIDIMODE bit of CR1 should be clear
	}
	else if(pSPIHandle->SPIConfig.SPI_BusConfig ==  SPI_BUS_CONFIG_HD)
	{
		tempreg |=(1 <<  SPI_CR1_BIDIMODE);  // if it is HD Mode then BIDIMODE bit of CR1 should be set
	}
	else if(pSPIHandle->SPIConfig.SPI_BusConfig ==  SPI_BUS_CONFIG_SIMPLEX_RXONLY)
	{
		tempreg &=(1 <<  SPI_CR1_BIDIMODE);  // if it is SIMPLEX Mode then BIDIMODE bit of CR1 should be clear
		tempreg |=(1 <<  SPI_CR1_RXONLY);		// and RXONLY bit should be set
	}
	tempreg |= pSPIHandle->SPIConfig.SPI_SCLSpeed << SPI_CR1_BR;

	tempreg |= pSPIHandle->SPIConfig.SPI_CPOL << SPI_CR1_CPOL;

	tempreg |= pSPIHandle->SPIConfig.SPI_CPHA <<SPI_CR1_CPHA;

	tempreg |= pSPIHandle->SPIConfig.SPI_DFF << SPI_CR1_DFF;

	pSPIHandle->pSPIx->CR1 = tempreg;
}
void SPI_DeInit(SPI_RegDef_t *pSPIx)
{
	if (pSPIx == SPI1)
		{
			SPI1_REG_RESET();
		}
		else if (pSPIx == SPI2)
			{
				SPI2_REG_RESET();
			}
		else if (pSPIx == SPI3)
			{
				SPI3_REG_RESET();
			}
		else if (pSPIx == SPI4)
			{
				SPI4_REG_RESET();
			}
}

uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx, uint8_t FlagName)
{
	if(pSPIx->SR & FlagName)
	{
		return FLAG_SET;
	}
	else
	{
		return FLAG_RESET;
	}
}
void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len)
{
	while(Len > 0)
	{
		// wait until TXE flag is set
		while (SPI_GetFlagStatus(pSPIx, SPI_TXE_FLAG )==FLAG_RESET) ;

			// check DFF bit in CR1
			if((pSPIx->CR1 & (1 << SPI_CR1_DFF)))
			{
				pSPIx->DR = *(uint16_t*)pTxBuffer;
				Len--;
				Len--;
				(uint16_t*)pTxBuffer++;
			}
			else
			{
				pSPIx->DR = *(pTxBuffer);
				Len--;
				pTxBuffer++;
			}

	}
}
void SPI_RecieveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t Len)
{
	while (Len > 0)
		{
			// wait until RXNE flag is set
		while(SPI_GetFlagStatus(pSPIx, SPI_RXNE_FLAG )==FLAG_RESET);

				if((pSPIx->CR1 & (1 << SPI_CR1_DFF)))
				{
					*((uint16_t*)pRxBuffer)= pSPIx->DR ;
					Len--;
					Len--;
					(uint16_t*)pRxBuffer++;
				}
				else
				{
					*(pRxBuffer) = pSPIx->DR;
					Len--;
					pRxBuffer++;
				}

		}
}
