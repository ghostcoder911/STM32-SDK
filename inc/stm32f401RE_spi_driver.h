/*
 * stm32f401RE_spi_driver.h
 *
 *  Created on: Aug 18, 2026
 *      Author: ANEESA
 */

#ifndef INC_STM32F401RE_SPI_DRIVER_H_
#define INC_STM32F401RE_SPI_DRIVER_H_

#include "stm32f401RE.h"

typedef struct
{
	uint8_t SPI_DeviceMode; 		//master or slave
	uint8_t SPI_BusConfig; 			//full/ half duplex or simplex
	uint8_t SPI_SCLSpeed; 			//clock speed (prescalar)
	uint8_t SPI_DFF; 				//data frame format 8 or 16 bit
	uint8_t SPI_CPOL; 				//clock polarity
	uint8_t SPI_CPHA; 				//clock phase
	uint8_t SPI_SSM; 				//s/w slave management
}SPI_Config_t;

typedef struct
{
    SPI_RegDef_t  *pSPIx;       // pointer to spi peripheral
    SPI_Config_t  SPIConfig;   // Configuration settings
}SPI_Handle_t;

/*SPI device mode macros*/

#define SPI_MASTER_MODE		1
#define SPI_SLAVE_MODE		0

/*SPI Bus congiguration*/

#define SPI_BUS_CONFIG_FD				1
#define SPI_BUS_CONFIG_HD				2
#define SPI_BUS_CONFIG_SIMPLEX_RXONLY	3

/*SPI SCLSpeed (Clock speed)- prescalar values*/

#define SPI_SCLK_SPEED_DIV2			0
#define SPI_SCLK_SPEED_DIV4			1
#define SPI_SCLK_SPEED_DIV8			2
#define SPI_SCLK_SPEED_DIV16		3
#define SPI_SCLK_SPEED_DIV32 		4
#define SPI_SCLK_SPEED_DIV64		5
#define SPI_SCLK_SPEED_DIV128		6
#define SPI_SCLK_SPEED_DIV256		7

/*SPI Data frame format*/

#define SPI_DFF_8BITS		0
#define SPI_DFF_16BITS		1

/*SPI CPOL*/

#define SPI_CPOL_LOW		0
#define SPI_CPOL_HIGH		1

/*SPI CPHA*/
#define SPI_CPHA_LOW        0
#define SPI_CPHA_HIGH       1

/*SPI Software slave management*/
#define SPI_SSM_DI          0
#define SPI_SSM_EN          1

/*SPI Flag Definitions*/
#define SPI_TXE_FLAG 		(1 <<  SPI_SR_TXE)
#define SPI_RXNE_FLAG 		(1 <<  SPI_SR_RXNE)
#define SPI_BUSY_FLAG 		(1 <<  SPI_SR_BSY)

// Peripheral Clock Setup
void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi);

//Init and Deinit
void SPI_Init(SPI_Handle_t *pSPIHandle);
void SPI_DeInit(SPI_RegDef_t *pSPIx);

void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len);
void SPI_RecieveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t Len);

#endif /* INC_STM32F401RE_SPI_DRIVER_H_ */
