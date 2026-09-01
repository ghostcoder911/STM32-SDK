/**
 * @brief LED and Button Example
 * @author Vidhya
 * @brief This example demonstrates how to control an LED using a button on the STM32F401 micro-controller.
*/


#include "stm32f401xe_gpio.h"

#define BTN_PRESS 0

void delay(void)
{
    for (uint32_t i = 0; i < 500000; i++);
}

/**
 * @brief Button-Controlled LED
 * @details The green LED is a user LED connected to ARDUINO® signal D13 corresponding to STM32 I/O PA5
 *          The user button is connected to the I/O PC13 (pin 2) of the STM32 micro-controller.
*/

int main(void)
{

	GPIO_Handle_t GpioLed,GpioBtn;



    /*Configure LED (PA5)
     * @note The green LED is a user LED connected to ARDUINO® signal D13 corresponding to STM32 I/O PA5
     *       gpio pin 5 of GPIOA port is configured as output mode, push-pull type, no pull-up/pull-down, and fast speed.
     *       initialized using the GPIO_Init() function.
     *       clock for GPIOA port is enabled using the GPIO_PeriClockControl() function.
     * @note In the main loop, the gpio pin 5 of GPIOA port is toggled in an infinite loop with a delay between each toggle using the GPIO_ToggleOutputPin() function.
    to create a blinking effect for the LED. 
    */
       GpioLed.pGPIOx = GPIOA;
       GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_5;        //LED-PA5
       GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;          //output mode
       GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;       //fast speed
       GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;      //push-pull type
       GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;    //no pull-up/pull-down

       /**Configure Button (PC13)
        * @note The user button is connected to the I/O PC13 (pin 2) of the STM32 micro-controller.
        *       gpio pin 13 of GPIOC port is configured as input mode, no pull-up/pull-down, and fast speed.
        *       initialized using the GPIO_Init() function.
        *       clock for GPIOC port is enabled using the GPIO_PeriClockControl() function.
        *       */

       GpioBtn.pGPIOx = GPIOC;
       GpioBtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;      //User Button-PC13
       GpioBtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;          //input mode
       GpioBtn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;      //fast speed
       GpioBtn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;   //no pull-up/pull-down

       /**Enable clocks
        * @note The clock for GPIOA and GPIOC ports is enabled using the GPIO_PeriClockControl() function.
        */  

       GPIO_PeriClockControl(GPIOA, ENABLE);
       GPIO_PeriClockControl(GPIOC, ENABLE);

       /**Initialize pins
        * @note The gpio pin 5 of GPIOA port and gpio pin 13 of GPIOC port are initialized using the GPIO_Init() function.
        */

       GPIO_Init(&GpioLed);
       GPIO_Init(&GpioBtn);
      
    
      /**Button-Controlled LED
       * @note The LED is controlled by the user button connected to GPIOC pin 13.
     */

       while (1)
           {
               if (GPIO_ReadFromInputPin(GPIOC, GPIO_PIN_NO_13) == BTN_PRESS)
               {
                   delay();  // Debounce delay
                   GPIO_ToggleOutputPin(GPIOA, GPIO_PIN_NO_5);
               }
           }

           return 0;
}

