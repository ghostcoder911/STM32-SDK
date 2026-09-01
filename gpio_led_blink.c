
/**
 *  @brief LED Blink Example
 *  @author Vidhya
 * @note This example demonstrates how to blink an LED using GPIO on the STM32F401 micro-controller.
 */
 #include "stm32f401xe_gpio.h"
 #include <stdint.h>

/**
 * @brief Delay function
 * This function creates a simple delay by executing a loop for a specified number of iterations.
 */
void delay(void)
{
    for (uint32_t i = 0; i < 500000; i++);
}
int main(void)
{
    GPIO_Handle_t GpioLed;

    /*
    @brief Configure LED pin (PA5)-gpio pin 5 of GPIOA port
    @note The green LED is a user LED connected to ARDUINO® signal D13 corresponding to STM32 I/O PA5
    gpio pin 5 of GPIOA port is configured as output mode, push-pull type, no pull-up/pull-down, and fast speed.
    initialized using the GPIO_Init() function.
    clock for GPIOA port is enabled using the GPIO_PeriClockControl() function.
    @note In the main loop, the gpio pin 5 of GPIOA port is toggled in an infinite loop with a delay between each toggle using the GPIO_ToggleOutputPin() function.
    to create a blinking effect for the LED.
    */

    GpioLed.pGPIOx = GPIOA;
    GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_5;
    GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
    GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
    GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

    // Enable clock for GPIOA
    GPIO_PeriClockControl(GPIOA, ENABLE);

    // Initialize the GPIO pin
    GPIO_Init(&GpioLed);

    // Blink forever
    while (1)
    {
        GPIO_ToggleOutputPin(GPIOA, GPIO_PIN_NO_5);
        delay();
    }

    return 0;
}

