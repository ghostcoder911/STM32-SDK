/*
 * stm32f401RE_gpio.h
 *
 *  Created on: Aug 7, 2026
 *      Author: ANEESA
 */

#ifndef INC_STM32F401RE_GPIO_H_
#define INC_STM32F401RE_GPIO_H_


#include "stm32f401RE.h"   // MCU header file includes

/*GPIO pin config. structure*/

typedef struct
{
	uint8_t GPIO_PinNumber; 			// pin no. 0-15
	uint8_t GPIO_PinMode; 				// pin mode: i/p, o/p, alternate, analog
	uint8_t GPIO_PinSpeed; 				// low, medium, high, very high
	uint8_t GPIO_PinPuPd; 				// pull up  / down  congig.
	uint8_t GPIO_PinOPType; 			// o/p type: push-pull / open drain
	uint8_t GPIO_PinAltFunMode; 		// alternate fun( 0-15)

}GPIO_PinConfig_t;


/*GPIO handle structure*/

typedef struct
{
	GPIO_RegDef_t *pGPIOx;					// pointer to gpio base address
	GPIO_PinConfig_t GPIO_PinConfig;  		// pin config . settings
}GPIO_Handle_t;

/* GPIO pin numbers
 * macros for pin mumbers*/

#define GPIO_PinNo_0		0
#define GPIO_PinNo_1		1
#define GPIO_PinNo_2		2
#define GPIO_PinNo_3		3
#define GPIO_PinNo_4		4
#define GPIO_PinNo_5		5
#define GPIO_PinNo_6		6
#define GPIO_PinNo_7		7
#define GPIO_PinNo_8		8
#define GPIO_PinNo_9		9
#define GPIO_PinNo_10		10
#define GPIO_PinNo_11		11
#define GPIO_PinNo_12		12
#define GPIO_PinNo_13		13
#define GPIO_PinNo_14		14
#define GPIO_PinNo_15		15

/*GPIO pin possible
macros for pin modes*/

#define GPIO_MODE_IN			0		// input mode
#define GPIO_MODE_OUT			1		// output mode
#define GPIO_MODE_ALTFUN		2		// alternate fun mode
#define GPIO_MODE_ANALOG		3		// analog mode
#define GPIO_MODE_IT_FT			4 		// interrupt at falling trigger
#define GPIO_MODE_IT_RT			5 		// interrupt at rising trigger
#define GPIO_MODE_IT_RFT		6 		// interrupt at rising or falling trigger*/

/* GPIO pin output types
 * macros for o/p types*/
#define GPIO_OP_TYPE_PP			0	//push_pull
#define GPIO_OP_TYPE_OD			1	//open_drain

/*GPIO pin speeds
 * macros for o/p speeds*/
#define GPIO_SPEED_LOW     0   // Low speed
#define GPIO_SPEED_MEDIUM  1   // Medium speed
#define GPIO_SPEED_FAST    2   // High speed
#define GPIO_SPEED_HIGH    3   // Very high speed

/*GPIO pin pull_up/pull_down configuration
 * macros for pullup and pull down*/

#define GPIO_NO_PUPD			0   //  pullup/pulldown
#define GPIO_NO_PU				1   // pull up
#define GPIO_NO_PD				2   // pull down

void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnOrDi);
void GPIO_Init(GPIO_Handle_t *pGPIOHandle);
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx);
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);
void GPIO_WritetoOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value);
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx);
void GPIO_WritetoOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value);
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);

#endif /* INC_STM32F401RE_GPIO_H_ */
