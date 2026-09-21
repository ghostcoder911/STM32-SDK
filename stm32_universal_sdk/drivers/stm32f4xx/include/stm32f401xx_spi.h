/*
 * stm32f401xx_spi.h
 *
 *  Created on: Sep 18, 2026
 *      Author: Nandhu
 */

#ifndef INC_STM32F401XX_SPI_H_
#define INC_STM32F401XX_SPI_H_

#include "stm32f401xx.h"

/*
 * Configuration structure for SPIx peripheral
 */
typedef struct
{
	uint8_t SPI_DeviceMode;  // Master or Slave mode
	uint8_t SPI_BusConfig;   // Full-duplex, Half-duplex, or Simplex (Rx only)
	uint8_t SPI_SclkSpeed;   // Clock speed (Baud rate prescaler: div2, div4, div8, etc.)
	uint8_t SPI_DFF;         // Data Frame Format (8-bit or 16-bit payload)
	uint8_t SPI_CPOL;        // Clock Polarity (Is the clock line High or Low when idle?)
	uint8_t SPI_CPHA;        // Clock Phase (Is data captured on the 1st or 2nd clock edge?)
	uint8_t SPI_SSM;         // Software Slave Management (Hardware NSS pin or Software control)
} SPI_Config_t;

/*
 * Handle structure for SPIx peripheral
 */
typedef struct
{
	SPI_RegDef_t *pSPIx;		// Pointer to the base address of SPI1, SPI2, SPI3, or SPI4
	SPI_Config_t SPI_Config;	// User's Configuration settings

    // For interrupt-based communication
    uint8_t        *pTxBuffer;    // TX buffer pointer
    uint8_t        *pRxBuffer;    // RX buffer pointer
    uint32_t       TxLen;         // TX length
    uint32_t       RxLen;         // RX length
    uint8_t        TxBusyState;   // TX state
    uint8_t        RxBusyState;   // RX state
}SPI_Handle_t;

/*
 * @SPI_DeviceMode
 */
#define SPI_DEVICE_MODE_MASTER    1
#define SPI_DEVICE_MODE_SLAVE     0

/*
 * @SPI_BusConfig
 */
#define SPI_BUS_CONFIG_FD         1  // Full duplex
#define SPI_BUS_CONFIG_HD         2  // Half duplex
#define SPI_BUS_CONFIG_SIMPLEX_RX 3  // Simplex RX only

/*
 * @SPI_SclkSpeed - Prescaler values
 */
#define SPI_SCLK_SPEED_DIV2       0
#define SPI_SCLK_SPEED_DIV4       1
#define SPI_SCLK_SPEED_DIV8       2
#define SPI_SCLK_SPEED_DIV16      3
#define SPI_SCLK_SPEED_DIV32      4
#define SPI_SCLK_SPEED_DIV64      5
#define SPI_SCLK_SPEED_DIV128     6
#define SPI_SCLK_SPEED_DIV256     7

/*
 * @SPI_DFF - Data Frame Format
 */
#define SPI_DFF_8BITS             0
#define SPI_DFF_16BITS            1

/*
 * @SPI_CPOL
 */
#define SPI_CPOL_LOW              0
#define SPI_CPOL_HIGH             1

/*
 * @SPI_CPHA
 */
#define SPI_CPHA_LOW              0  // First clock edge
#define SPI_CPHA_HIGH             1  // Second clock edge

/*
 * @SPI_SSM - Software Slave Management
 * With SSM=1 (software), you control the slave select manually.
 * With SSM=0 (hardware), the SPI peripheral controls NSS automatically.
 */
#define SPI_SSM_DI                0  // Hardware NSS
#define SPI_SSM_EN                1  // Software NSS

/*
 * SPI Status Register Flags
 */
#define SPI_RXNE_FLAG    (1 << 0)  // RX buffer not empty
#define SPI_TXE_FLAG     (1 << 1)  // TX buffer empty
#define SPI_CHSIDE_FLAG  (1 << 2)  // Channel side
#define SPI_UDR_FLAG     (1 << 3)  // Underrun flag
#define SPI_CRCERR_FLAG  (1 << 4)  // CRC error
#define SPI_MODF_FLAG    (1 << 5)  // Mode fault
#define SPI_OVR_FLAG     (1 << 6)  // Overrun flag
#define SPI_BSY_FLAG     (1 << 7)  // Busy flag
#define SPI_FRE_FLAG     (1 << 8)  // Frame error


/*************************************************************
 *                 APIs supported by this driver
 *************************************************************/

/*
 * Peripheral Clock Setup
 */
void SPI_PeripheralClkControl(SPI_RegDef_t *pSPIx, uint8_t EnOrDi);

/*
 * Init and De-init
 */
void SPI_Init(SPI_Handle_t *pSPIHandle);
void SPI_DeInit(SPI_RegDef_t *pSPIx);

/*
 * Data Send and Receive (Blocking/Polling)
 */
void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len);
void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t Len);

/*
 * Data Send and Receive (Interrupt-based)
 */
uint8_t SPI_SendDataIT(SPI_Handle_t *pSPIHandle, uint8_t *pTxBuffer, uint32_t Len);
uint8_t SPI_ReceiveDataIT(SPI_Handle_t *pSPIHandle, uint8_t *pRxBuffer, uint32_t Len);

/*
 * IRQ Configuration and ISR Handling
 */
void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
void SPI_IRQHandling(SPI_Handle_t *pSPIHandle);

/*
 * Other Peripheral Control APIs
 */
void SPI_PeripheralControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi);
void SPI_SSIConfig(SPI_RegDef_t *pSPIx, uint8_t EnorDi);
void SPI_SSOEConfig(SPI_RegDef_t *pSPIx, uint8_t EnorDi);
uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx, uint32_t FlagName);
void SPI_ClearOVRFlag(SPI_RegDef_t *pSPIx);
void SPI_CloseTransmission(SPI_Handle_t *pSPIHandle);
void SPI_CloseReception(SPI_Handle_t *pSPIHandle);

/*
 * Application Callback (weak function to be overridden)
 */
void SPI_ApplicationEventCallback(SPI_Handle_t *pSPIHandle, uint8_t AppEvent);


#endif /* INC_STM32F401XX_SPI_H_ */
