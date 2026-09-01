/*************
 * stm32f401xe_usart.h
 *
 *  Created on: Aug 19, 2026
 *    @version 1.0
 */

#ifndef INC_STM32F401XE_USART_H_
#define INC_STM32F401XE_USART_H_


#include <stdint.h>
#include "stm32f401xe_rcc.h"
#include "stm32f401xe.h"


/** 
 * @brief Configuration structure for USART
 * This structure contains all the parameters required
 * to configure the USART peripheral.
 */

typedef struct
{
    uint8_t  USART_Mode;           // TX only, RX only, or both
    uint32_t USART_Baud;           // Baud rate
    uint8_t  USART_NoOfStopBits;   // Stop bits: 1, 0.5, 2, 1.5
    uint8_t  USART_WordLength;     // 8 or 9 bits
    uint8_t  USART_ParityControl;  // None, Even, Odd
    uint8_t  USART_HWFlowControl;  // None, CTS, RTS, CTS+RTS
} USART_Config_t;

/**
 * @brief Handle structure for USART
 * This structure contains the configuration settings and
 * runtime information for the USART peripheral.
 */
typedef struct
{
    USART_RegDef_t *pUSARTx;      // Pointer to USART peripheral
    USART_Config_t USART_Config; // Configuration settings

    // For interrupt-based communication
    uint8_t        *pTxBuffer;    // TX buffer pointer
    uint8_t        *pRxBuffer;    // RX buffer pointer
    uint32_t       TxLen;         // TX length
    uint32_t       RxLen;         // RX length
    uint8_t        TxBusyState;   // TX state
    uint8_t        RxBusyState;   // RX state
} USART_Handle_t;

/** 
 *  @brief USART Mode(CR1 register-Bits 3-Transmit Enable:2-Receive Enable)
 */
#define USART_MODE_ONLY_TX    0          // Transmit only
#define USART_MODE_ONLY_RX    1          // Receive only 
#define USART_MODE_TXRX       2          // Transmit and Receive

/** 
 * @USART_Baud - Standard baud rates(BRR register values:Mantissa(11:8) and Fraction(3:0))
 */
#define USART_STD_BAUD_1200     1200      // Standard baud rate 1200
#define USART_STD_BAUD_2400     2400      // Standard baud rate 2400
#define USART_STD_BAUD_9600     9600      // Standard baud rate 9600
#define USART_STD_BAUD_19200    19200     // Standard baud rate 19200
#define USART_STD_BAUD_38400    38400     // Standard baud rate 38400
#define USART_STD_BAUD_57600    57600     // Standard baud rate 57600
#define USART_STD_BAUD_115200   115200    // Standard baud rate 115200
#define USART_STD_BAUD_230400   230400    // Standard baud rate 230400
#define USART_STD_BAUD_460800   460800    // Standard baud rate 460800
#define USART_STD_BAUD_921600   921600    // Standard baud rate 921600

/** 
 * @brief Parity Control(CR1 register-Bit 10(Parity Enable):Bit 9(Parity Selection)
 */
#define USART_PARITY_DISABLE   0           // Parity disabled
#define USART_PARITY_EN_EVEN   1           // Even parity
#define USART_PARITY_EN_ODD    2           // Odd parity

/**
 * @brief Word Length(CRI register-Bit 12-Word Length)
 */
#define USART_WORDLEN_8BITS    0           // 8 bits data length(1 start bit, 8 data bits, n stop bits)
#define USART_WORDLEN_9BITS    1           // 9 bits data length(1 start bit, 9 data bits, n stop bits)

/**
 * @brief Number of Stop Bits(CR2 register-Bits 13:12)
 */
#define USART_STOPBITS_1       0           // 1 stop bit
#define USART_STOPBITS_0_5     1           // 0.5 stop bits
#define USART_STOPBITS_2       2           // 2 stop bits
#define USART_STOPBITS_1_5     3           // 1.5 stop bits

/**
 * @brief Hardware Flow Control(CR3 register-Bits 9(CTS Enable):8(RTS Enable))
 */
#define USART_HW_FLOW_CTRL_NONE     0           // No hardware flow control
#define USART_HW_FLOW_CTRL_CTS      1           // CTS hardware flow control
#define USART_HW_FLOW_CTRL_RTS      2           // RTS hardware flow control
#define USART_HW_FLOW_CTRL_CTS_RTS  3           // CTS and RTS hardware flow control

/** 
 * @brief flags(SR register-Bits 7(TXE):5(RXNE):6(TC))
 */

#define USART_FLAG_TXE 			( 1 << USART_SR_TXE)   // Transmit data register empty flag
#define USART_FLAG_RXNE 		( 1 << USART_SR_RXNE)  // Receive data register not empty flag
#define USART_FLAG_TC 			( 1 << USART_SR_TC)    // Transmission complete flag

/**
 * @brief states(Tx and Rx-busy state)
 */
#define USART_BUSY_IN_RX 1                            // USART is busy in receiving data         
#define USART_BUSY_IN_TX 2                           // USART is busy in transmitting data
#define USART_READY 0                                // USART is ready for communication


#define 	USART_EVENT_TX_CMPLT   0                 // USART transmission complete event
#define		USART_EVENT_RX_CMPLT   1                 // USART reception complete event
#define		USART_EVENT_IDLE       2                // USART idle event
#define		USART_EVENT_CTS        3                 // USART CTS event
#define		USART_EVENT_PE         4                 // USART parity error event
#define		USART_ERR_FE     	   5                 // USART framing error event
#define		USART_ERR_NE    	   6                 // USART noise error event
#define		USART_ERR_ORE    	   7                 // USART overrun error event

/** 
 * @brief Clock setup(clock enable/disable)
 */
void USART_PeriClockControl(USART_RegDef_t *pUSARTx, uint8_t EnOrDi);    

/*
 * @brief and De-init(initialize and de-initialize)
 */
void USART_Init(USART_Handle_t *pUSARTHandle);             
void USART_DeInit(USART_Handle_t *pUSARTHandle);

/** 
 * @brief Send and Receive
 */
void  USART_SendData(USART_Handle_t *pUSARTHandle, uint8_t *pTxBuffer, uint32_t Len);         
void  USART_ReceiveData(USART_Handle_t *pUSARTHandle,uint8_t *pRxBuffer, uint32_t Len);      
uint8_t USART_SendDataIT(USART_Handle_t *pUSARTHandle,uint8_t *pTxBuffer, uint32_t Len);
uint8_t USART_ReceiveDataIT(USART_Handle_t *pUSARTHandle,uint8_t *pRxBuffer, uint32_t Len);

/** 
 * @brief Peripheral Control APIs
 */

uint8_t USART_GetFlagStatus(USART_RegDef_t *pUSARTx, uint8_t StatusFlagName);
void USART_ClearFlag(USART_RegDef_t *pUSARTx, uint16_t StatusFlagName);
void USART_PeripheralControl(USART_RegDef_t *pUSARTx, uint8_t EnOrDi);
void USART_SetBaudRate(USART_RegDef_t *pUSARTx, uint32_t BaudRate);

#endif /* INC_STM32F401XE_USART_H_ */
