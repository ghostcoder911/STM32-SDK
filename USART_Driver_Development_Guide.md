 STM32F401RE USART Driver Development Guide

 1. Introduction

The USART driver provides a reusable interface between application software and the STM32F401RE USART peripheral.

The driver supports:

- USART configuration
- Peripheral clock control
- USART initialization/de-initialization
- Baud-rate configuration
- Data transmission
- Data reception
- Interrupt-based communication
- Status flag handling
- Peripheral enable/disable


2. USART Configuration

The USART configuration structure contains:

| Parameter | Description |
|---|---|
| `USART_Mode` | TX, RX or TX/RX |
| `USART_Baud` | Baud rate |
| `USART_NoOfStopBits` | Number of stop bits |
| `USART_WordLength` | 8-bit or 9-bit word length |
| `USART_ParityControl` | Disabled, even or odd parity |
| `USART_HWFlowControl` | None, CTS, RTS or CTS+RTS |


## 3. USART Handle

The USART handle stores:

- USART peripheral pointer
- USART configuration
- TX buffer
- RX buffer
- TX length
- RX length
- TX busy state
- RX busy state

This allows the same driver API to be used with different USART peripherals.

---

## 4. USART Modes

```c
USART_MODE_ONLY_TX
USART_MODE_ONLY_RX
USART_MODE_TXRX
```

### TX

The peripheral is configured for transmission.

### RX

The peripheral is configured for reception.

### TX/RX

The peripheral supports both transmission and reception.

---

## 5. Baud Rates

The driver provides standard baud-rate definitions including:

```text
1200
2400
9600
19200
38400
57600
115200
230400
460800
921600
```

---

## 6. Word Length

```c
USART_WORDLEN_8BITS
USART_WORDLEN_9BITS
```

---

## 7. Parity

```c
USART_PARITY_DISABLE
USART_PARITY_EN_EVEN
USART_PARITY_EN_ODD
```

---

## 8. Stop Bits

```c
USART_STOPBITS_1
USART_STOPBITS_0_5
USART_STOPBITS_2
USART_STOPBITS_1_5
```

---

## 9. Hardware Flow Control

```c
USART_HW_FLOW_CTRL_NONE
USART_HW_FLOW_CTRL_CTS
USART_HW_FLOW_CTRL_RTS
USART_HW_FLOW_CTRL_CTS_RTS
```

The driver configures CTS and RTS through the USART CR3 register.

---

## 10. USART Initialization

```c
void USART_Init(USART_Handle_t *pUSARTHandle);
```

The initialization process configures:

```text
Peripheral clock
      |
      v
Mode
      |
      v
Word length
      |
      v
Parity
      |
      v
Stop bits
      |
      v
Hardware flow control
      |
      v
Baud rate
```

---

## 11. Peripheral Clock Control

```c
void USART_PeriClockControl(
    USART_RegDef_t *pUSARTx,
    uint8_t EnorDi
);

The driver determines the selected USART and enables/disables its peripheral clock.


## 12. Peripheral Enable/Disable

void USART_PeripheralControl(
    USART_RegDef_t *pUSARTx,
    uint8_t Cmd
);


The implementation controls the USART enable bit in CR1.

---

## 13. Baud Rate Calculation

The USART driver calculates BRR using the peripheral clock.

The formula used is:

```text
Baud = FCK / [8 × (2 - OVER8) × USARTDIV]
```

Where:

```text
FCK      = peripheral clock
OVER8    = oversampling mode
USARTDIV = USART divider
```

For USART1 and USART6, the driver obtains the APB2 clock.

For USART2, the driver obtains the APB1 clock.

---

## 14. Example Baud Rate

For:

```text
Peripheral clock = 16 MHz
Baud rate        = 115200
Oversampling     = 16
```

the driver calculates the USART divider and writes the resulting value to the BRR register.

---

## 15. Data Transmission

Blocking transmission:

```c
void USART_SendData(
    USART_Handle_t *pUSARTHandle,
    uint8_t *pTxBuffer,
    uint32_t Len
);
```

The function sends a buffer of the requested length.

---

## 16. Data Reception

Blocking reception:

```c
void USART_ReceiveData(
    USART_Handle_t *pUSARTHandle,
    uint8_t *pRxBuffer,
    uint32_t Len
);
```

---

## 17. Interrupt-Based Transmission

```c
uint8_t USART_SendDataIT(
    USART_Handle_t *pUSARTHandle,
    uint8_t *pTxBuffer,
    uint32_t Len
);
```

This API starts interrupt-driven transmission.

---

## 18. Interrupt-Based Reception

```c
uint8_t USART_ReceiveDataIT(
    USART_Handle_t *pUSARTHandle,
    uint8_t *pRxBuffer,
    uint32_t Len
);
```

This API starts interrupt-driven reception.

---

## 19. USART Status Flags

The driver provides flag handling APIs:

```c
uint8_t USART_GetFlagStatus(
    USART_RegDef_t *pUSARTx,
    uint8_t StatusFlagName
);

void USART_ClearFlag(
    USART_RegDef_t *pUSARTx,
    uint16_t StatusFlagName
);
```

Common USART flags include:

```c
USART_FLAG_TXE
USART_FLAG_RXNE
USART_FLAG_TC
```

### TXE

Transmit data register empty.

### RXNE

Receive data register not empty.

### TC

Transmission complete.

---

## 20. Example Configuration

```c
USART_Handle_t usart;

usart.pUSARTx = USART2;

usart.USART_Config.USART_Mode =
    USART_MODE_TXRX;

usart.USART_Config.USART_Baud =
    USART_STD_BAUD_9600;

usart.USART_Config.USART_NoOfStopBits =
    USART_STOPBITS_1;

usart.USART_Config.USART_WordLength =
    USART_WORDLEN_8BITS;

usart.USART_Config.USART_ParityControl =
    USART_PARITY_DISABLE;

usart.USART_Config.USART_HWFlowControl =
    USART_HW_FLOW_CTRL_NONE;

USART_Init(&usart);
```

---

## 21. Typical Serial Terminal Settings

```text
Baud Rate : 9600
Data Bits : 8
Parity    : None
Stop Bits : 1
Flow Ctrl : None
```

---

## 22. Driver Dependencies

```text
USART Driver
     |
     +---- STM32F401XE device header
     |
     +---- RCC Driver
              |
              +---- PCLK1
              +---- PCLK2
```

The RCC driver is required for baud-rate calculation.

---

## 23. Common Configuration Problems

- USART peripheral clock not enabled
- Wrong GPIO alternate function
- Wrong TX/RX pins
- Incorrect baud rate
- Incorrect word length
- Incorrect parity
- Incorrect stop bits
- Incorrect hardware flow-control setting
- Incorrect APB clock calculation

---

## 24. Summary

The USART driver provides a reusable serial-communication abstraction for the STM32F401RE. It separates application code from direct USART register manipulation and supports both blocking and interrupt-based communication.
