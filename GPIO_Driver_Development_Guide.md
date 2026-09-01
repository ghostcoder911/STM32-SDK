# STM32F401RE GPIO Driver Development Guide

## 1. Introduction

The GPIO driver provides a software interface for configuring and controlling the General Purpose Input/Output peripherals of the STM32F401RE.

The driver supports:

- GPIO pin configuration
- Input, output, alternate-function and analog modes
- Interrupt-triggered input modes
- Pull-up and pull-down configuration
- Output type selection
- Output speed selection
- Digital input/output operations
- GPIO peripheral clock control
- GPIO initialization and de-initialization

---

## 2. GPIO Driver Architecture

```text
Application
    |
    v
GPIO Driver API
    |
    +-- GPIO_Init()
    +-- GPIO_DeInit()
    +-- GPIO_PeriClockControl()
    +-- GPIO_ReadFromInputPin()
    +-- GPIO_WriteToOutPin()
    +-- GPIO_ReadFromInputPort()
    +-- GPIO_WriteToOutPort()
    +-- GPIO_ToggleOutPin()
    |
    v
STM32F401RE GPIO Registers
```

---

## 3. GPIO Configuration Structure

The driver uses `GPIO_PinConfig_t` to hold the configuration of one GPIO pin.

| Parameter | Purpose |
|---|---|
| `GPIO_PinNumber` | Selects GPIO pin 0 to 15 |
| `GPIO_PinMode` | Input/output/alternate-function/analog/interrupt mode |
| `GPIO_PinSpeed` | Low, medium, fast or high speed |
| `GPIO_PinPuPdControl` | No pull, pull-up or pull-down |
| `GPIO_PinOPType` | Push-pull or open-drain |
| `GPIO_AltFunMode` | Alternate-function number 0 to 15 |

---

## 4. GPIO Handle

`GPIO_Handle_t` contains:

- Pointer to the GPIO peripheral
- GPIO pin configuration

Example:

```c
GPIO_Handle_t GpioLed;

GpioLed.pGPIOx = GPIOA;

GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_5;
GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_Type_PP;
```

---

## 5. GPIO Pin Modes

The driver defines:

```c
GPIO_MODE_IN
GPIO_MODE_OUT
GPIO_MODE_ALFN
GPIO_MODE_ANALOG
GPIO_MODE_IT_FT
GPIO_MODE_IT_RT
GPIO_MODE_IT_RFT
```

### Input

Used when the MCU reads an external digital signal.

### Output

Used when the MCU drives a digital signal.

### Alternate Function

Used when a peripheral such as USART, SPI, I2C or timer controls the pin.

### Analog

Used for analog functions and to reduce unnecessary digital input activity.

### Interrupt Modes

The driver provides falling-edge, rising-edge and rising/falling-edge input modes.

---

## 6. GPIO Speed

Available speed settings are:

```c
GPIO_SPEED_LOW
GPIO_SPEED_MEDIUM
GPIO_SPEED_FAST
GPIO_SPEED_HIGH
```

---

## 7. GPIO Output Type

### Push-Pull

```c
GPIO_OP_Type_PP
```

### Open-Drain

```c
GPIO_OP_Type_OD
```

---

## 8. Pull-Up / Pull-Down

```c
GPIO_NO_PUPD
GPIO_NO_PU
GPIO_NO_PD
```

---

## 9. GPIO Initialization

```c
void GPIO_Init(GPIO_Handle_t *pGPIOHandle);
```

This function configures the selected GPIO peripheral and pin according to the values stored in the handle.

Typical sequence:

```text
Enable GPIO clock
      |
      v
Configure mode
      |
      v
Configure speed
      |
      v
Configure pull-up/pull-down
      |
      v
Configure output type
      |
      v
Configure alternate function if required
```

---

## 10. GPIO De-Initialization

```c
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx);
```

This function resets the selected GPIO peripheral.

---

## 11. Peripheral Clock Control

```c
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi);
```

The GPIO peripheral clock must be enabled before accessing the peripheral registers.

---

## 12. Input Operations

Read one GPIO pin:

```c
uint8_t GPIO_ReadFromInputPin(
    GPIO_RegDef_t *pGPIOx,
    uint8_t PinNumber
);
```

Read the complete GPIO port:

```c
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx);
```

---

## 13. Output Operations

Write one pin:

```c
void GPIO_WriteToOutPin(
    GPIO_RegDef_t *pGPIOx,
    uint8_t PinNumber,
    uint8_t value
);
```

Write the complete port:

```c
void GPIO_WriteToOutPort(
    GPIO_RegDef_t *pGPIOx,
    uint16_t value
);
```

Toggle a pin:

```c
void GPIO_ToggleOutPin(
    GPIO_RegDef_t *pGPIOx,
    uint8_t PinNumber,
    uint8_t value
);
```

---

## 14. Example: LED Configuration

```c
GPIO_Handle_t GpioLed;

GpioLed.pGPIOx = GPIOA;

GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_5;
GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_Type_PP;

GPIO_PeriClockControl(GPIOA, ENABLE);
GPIO_Init(&GpioLed);

GPIO_WriteToOutPin(GPIOA, GPIO_PIN_NO_5, 1);
```

---

## 15. Summary

The GPIO driver abstracts low-level STM32 GPIO register operations and provides a reusable API for pin configuration and digital I/O.
