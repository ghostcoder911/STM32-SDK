/*
 * stm32f401xe_rcc.h
 *
 *  Created on: Aug 17, 2026
 *      Author: deepu
 */

#ifndef INC_STM32F401XE_RCC_H_
#define INC_STM32F401XE_RCC_H_

#include "stm32f401xe.h"

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

#endif /* INC_STM32F401XE_RCC_H_ */
