/*
 * stm32f401RE_gpio.h
 *
 *  Created on: Aug 6, 2026
 *      Author: deepu
 */

#ifndef INC_STM32F401RE_GPIO_H_
#define INC_STM32F401RE_GPIO_H_

# include  "stm32f401xe.h"



typedef struct
{
	uint32_t GPIO_PinNumber;           //Pin number(0-15)
	uint32_t GPIO_PinMode;             //Input/Output/AltFn/Analog mode
	uint32_t GPIO_PinSpeed;            //Low/Medium/High/Very High speed
	uint32_t GPIO_PinPuPdControl;      //Pull-up/Pull-down configuration
	uint32_t GPIO_PinOPType;           //Push-Pull/Open-Drain
	uint32_t GPIO_PinAltFunMode;          //Alternate function Mode(0-15)
} GPIO_PinConfig_t;

/*
 * Handle structure for a GPIO pin
 */

typedef struct
{
	GPIO_RegDef_t *pGPIOx;              // Pointer to GPIO port base address
	GPIO_PinConfig_t GPIO_PinConfig;    // Pin configuration settings

}GPIO_Handle_t;;
/*
 * GPIO_PIN_NUMBERS
 */
#define GPIO_PIN_NO_0      0
#define GPIO_PIN_NO_1      1
#define GPIO_PIN_NO_2      2
#define GPIO_PIN_NO_3      3
#define GPIO_PIN_NO_4      4
#define GPIO_PIN_NO_5      5
#define GPIO_PIN_NO_6      6
#define GPIO_PIN_NO_8      8
#define GPIO_PIN_NO_9      9
#define GPIO_PIN_NO_10      10
#define GPIO_PIN_NO_11      11
#define GPIO_PIN_NO_12      12
#define GPIO_PIN_NO_13      13
#define GPIO_PIN_NO_14      14
#define GPIO_PIN_NO_15      15

/*
 * GPIO_PIN_MODES
 */

#define GPIO_MODE_IN        0           // Input mode
#define GPIO_MODE_OUT       1           // General purpose output mode
#define GPIO_MODE_ALTFN      2           // Alternate function mode
#define GPIO_MODE_ANALOG    3           // Analog mode
// Interrupt modes (custom values > 3)
#define GPIO_MODE_IT_FT    4           // Input with falling edge trigger
#define GPIO_MODE_IT_RT    5           // Input with rising edge trigger
#define GPIO_MODE_IT_RFT   6           // Input with rising/falling edge trigger
/*
 *GPIO_PIN_SPEED
 */
#define GPIO_SPEED_LOW       0          // Low speed
#define GPIO_SPEED_MEDIUM    1          // Medium speed
#define GPIO_SPEED_FAST      2          // High speed
#define GPIO_SPEED_HIGH      3          // Very high speed

/*
 * GPIO_PIN_OUTPUT_TYPES
 */

#define GPIO_OP_TYPE_PP      0           // Push-pull
#define GPIO_OP_TYPE_OD      1           // Open-drain

/*
 * GPIO pin pull-up/pull-down configuration
 */
#define GPIO_NO_PUPD         0          // No pull-up, pull-down
#define GPIO_NO_PU           1          // Pull-up
#define GPIO_NO_PD           2          // Pull-down

/*
 * Initialize and Reset GPIO Peripherals
 */

void GPIO_Init(GPIO_Handle_t *pGPIOHandle);
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx);

/*
 * Perpheral clk setup
 */
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx,uint8_t EnorDi);

/*
 * Data Read/Write
 */

uint8_t  GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx,uint8_t PinNumber);
void GPIO_WriteToOutPin(GPIO_RegDef_t *pGPIOx,uint8_t PinNumber,uint8_t value);
uint16_t  GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx);
void GPIO_WriteToOutPort(GPIO_RegDef_t *pGPIOx,uint16_t value);
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);
/*
void I2C_MasterSendData(I2C_Handle_t *pI2CHandle,uint8_t *pTxbuffer, uint32_t Len, uint8_t SlaveAddr,uint8_t Sr);
void I2C_MasterReceiveData(I2C_Handle_t *pI2CHandle,uint8_t *pRxBuffer, uint8_t Len, uint8_t SlaveAddr,uint8_t Sr);
uint8_t I2C_MasterSendDataIT(I2C_Handle_t *pI2CHandle,uint8_t *pTxbuffer, uint32_t Len, uint8_t SlaveAddr,uint8_t Sr);
uint8_t I2C_MasterReceiveDataIT(I2C_Handle_t *pI2CHandle,uint8_t *pRxBuffer, uint8_t Len, uint8_t SlaveAddr,uint8_t Sr);
*/
#endif /*INC_STM32F401RE_GPIO_H_*/

