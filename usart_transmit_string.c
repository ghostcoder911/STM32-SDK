/**
 * @brief USART Transmit String Example
 * @author vidhya
 * @brief This example demonstrates how to transmit a string using the USART peripheral on the STM32F401 micro-controller.
 */

#include "stm32f401xe_usart.h"
#include "stm32f401xe_gpio.h"
#include "stm32f401xe_rcc.h"
#include <string.h>


/**
 * @brief USART2 Handle
 * @details This handle is used to configure and manage the USART2 peripheral for transmitting data.
 */
USART_Handle_t USART2Handle;

/**
 * @brief USART2 GPIO Initialization
 * @details This function initializes the GPIO pins for USART2 (PA2 -> TX, PA3 -> RX) with the appropriate settings.
 */

void USART2_GPIOInits(void)
{
    GPIO_Handle_t USARTPins;

    // Enable the clock for GPIOA
    GPIO_PeriClockControl(GPIOA, ENABLE);

    // Configure the GPIO pins for USART2 (PA2 -> TX, PA3 -> RX)
    USARTPins.pGPIOx = GPIOA;
    USARTPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN; // Alternate function mode
    USARTPins.GPIO_PinConfig.GPIO_PinAltFunMode = 7;         // AF7 for USART2
    USARTPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP; // Push-pull output type
    USARTPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD; // No pull-up/pull-down
    USARTPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST; // Fast speed

    // Configure PA2 (TX)
    USARTPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_2;
    GPIO_Init(&USARTPins);

    // Configure PA3 (RX)
    USARTPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_3;
    GPIO_Init(&USARTPins);
}

/**
 * @brief USART2 Initialization
 * @details This function initializes the USART2 peripheral with the specified settings for transmitting data.
 */

void USART2_Init(void)
{
    // Enable the clock for USART2
    USART_PeriClockControl(USART2, ENABLE);

    // Configure USART2 settings
    USART2Handle.pUSARTx = USART2;
    USART2Handle.USART_Config.USART_Baud = 115200; // Set baud rate to 115200
    USART2Handle.USART_Config.USART_Mode = USART_MODE_TXRX; // Enable both TX and RX
    USART2Handle.USART_Config.USART_NoOfStopBits = USART_STOPBITS_1; // 1 stop bit
    USART2Handle.USART_Config.USART_WordLength = USART_WORDLEN_8BITS; // 8 bits word length
    USART2Handle.USART_Config.USART_ParityControl = USART_PARITY_DISABLE; // No parity
    USART2Handle.USART_Config.USART_HWFlowControl = USART_HW_FLOW_CTRL_NONE; // No hardware flow control

    // Initialize the USART2 peripheral with the specified settings
    USART_Init(&USART2Handle);
}

/*
int main(void)
{
    // Initialize GPIO pins for USART2
    USART2_GPIOInits();

    // Initialize USART2 peripheral
    USART2_Init();

    // Enable the USART2 peripheral
    USART_PeripheralControl(USART2, ENABLE);

    // Transmit a string using USART2
    char *message = "STM32, USART Testing!";
    USART_SendData(&USART2Handle, (uint8_t *)message, strlen(message));
    while(1)
    {
       //delay
       for(int i=0; i<500000; i++);
    }
    return 0;
}
*/
int main(void)
{
    USART2_GPIOInits();

    USART2_Init();

    USART_PeripheralControl(USART2, ENABLE);

    char *message = "STM32, USART Testing!\r\n";

    while(1)
    {
        USART_SendData(&USART2Handle,
                       (uint8_t *)message,
                       strlen(message));

        for(volatile uint32_t i = 0; i < 500000; i++);
    }
}







