/*
 * stm32f401xx_rcc.h
 *
 *  Created on: Sep 9, 2026
 *      Author: admin
 */

#ifndef INC_STM32F401XX_RCC_H_
#define INC_STM32F401XX_RCC_H_

#include "stm32f401xx.h"

/*
 * Returns the APB1 peripheral clock value
 */
uint32_t RCC_GetPCLK1Value(void);

/*
 * Returns the APB2 peripheral clock value
 */
uint32_t RCC_GetPCLK2Value(void);

/*
 * Returns the PLL output clock value
 */
uint32_t RCC_GetPLLOutputClock(void);

#endif /* INC_STM32F401XX_RCC_H_ */
