/*
 * stm32f401xx_usart.h
 *
 *  Created on: Sep 5, 2026
 *      Author: admin
 */

#ifndef INC_STM32F401XX_USART_H_
#define INC_STM32F401XX_USART_H_

#include "stm32f401xx.h"

/*
 * Configuration structure for USARTx peripheral
 */
typedef struct
{
	uint8_t USART_Mode;			   // TX only, RX only, or both
    uint32_t USART_Baud;           // Baud rate
    uint8_t  USART_NoOfStopBits;   // Stop bits: 1, 0.5, 2, 1.5
    uint8_t  USART_WordLength;     // 8 or 9 bits
    uint8_t  USART_ParityControl;  // None, Even, Odd
    uint8_t  USART_HWFlowControl;  // None, CTS, RTS, CTS+RTS
}USART_PinConfig_t;

/*
 * Handle structure for USARTx peripheral
 */
typedef struct
{
	USART_RegDef_t *pUSARTx;			// Pointer to USART Peripheral
	USART_PinConfig_t USART_PinConfig;	// Configuration settings

    // For interrupt-based communication
    uint8_t        *pTxBuffer;    // TX buffer pointer
    uint8_t        *pRxBuffer;    // RX buffer pointer
    uint32_t       TxLen;         // TX length
    uint32_t       RxLen;         // RX length
    uint8_t        TxBusyState;   // TX state
    uint8_t        RxBusyState;   // RX state
}USART_Handle_t;

/*
 * @USART_Mode
 */
#define USART_MODE_ONLY_TX    0
#define USART_MODE_ONLY_RX    1
#define USART_MODE_TXRX       2

/*
 * @USART_Baud - Standard baud rates
 */
#define USART_STD_BAUD_1200     1200
#define USART_STD_BAUD_2400     2400
#define USART_STD_BAUD_9600     9600
#define USART_STD_BAUD_19200    19200
#define USART_STD_BAUD_38400    38400
#define USART_STD_BAUD_57600    57600
#define USART_STD_BAUD_115200   115200
#define USART_STD_BAUD_230400   230400
#define USART_STD_BAUD_460800   460800
#define USART_STD_BAUD_921600   921600

/*
 * @USART_ParityControl
 */
#define USART_PARITY_DISABLE   0
#define USART_PARITY_EN_EVEN   1
#define USART_PARITY_EN_ODD    2

/*
 * @USART_WordLength
 */
#define USART_WORDLEN_8BITS    0
#define USART_WORDLEN_9BITS    1

/*
 * @USART_NoOfStopBits
 */
#define USART_STOPBITS_1       0
#define USART_STOPBITS_0_5     1
#define USART_STOPBITS_2       2
#define USART_STOPBITS_1_5     3

/*
 * @USART_HWFlowControl
 */
#define USART_HW_FLOW_CTRL_NONE     0
#define USART_HW_FLOW_CTRL_CTS      1
#define USART_HW_FLOW_CTRL_RTS      2
#define USART_HW_FLOW_CTRL_CTS_RTS  3

/**
 * @brief flags(SR register-Bits 7(TXE):5(RXNE):6(TC))
 */
#define USART_FLAG_TXE 			( 1 << USART_SR_TXE)   // Transmit data register empty flag
#define USART_FLAG_RXNE 		( 1 << USART_SR_RXNE)  // Receive data register not empty flag
#define USART_FLAG_TC 			( 1 << USART_SR_TC)    // Transmission complete flag

/********************************************************
 * 	USART Peripheral Clock Control
 ********************************************************/
void USART_PeripheralClkControl(USART_RegDef_t *pUSARTx, uint8_t EnOrDi);
void USART_PeripheralControl(USART_RegDef_t *pUSARTx, uint8_t cmd);

void USART_SetBaudRate(USART_RegDef_t *pUSARTx, uint32_t BaudRate);
void USART_Init(USART_Handle_t *pUSARTHandle);
void USART_SendData(USART_Handle_t *pUSARTHandle, uint8_t *pTxBuffer, uint32_t len);
void USART_ReceiveData(USART_Handle_t *pUSARTHandle, uint8_t *pRxBuffer, uint32_t len);

void USARTReceiveString(USART_Handle_t *pUSARTHandle, char* str, uint8_t buff_size);
#endif /* INC_STM32F401XX_USART_H_ */
