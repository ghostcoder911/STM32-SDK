/*
 * stm32f401xx_usart.c
 *
 *  Created on: Sep 7, 2026
 *      Author: Nandhu
 */
#include <stdint.h>
#include "stm32f401xx_usart.h"
#include "stm32f401xx_rcc.h"

void USART_PeripheralClkControl(USART_RegDef_t *pUSARTx, uint8_t EnOrDi)
{
	if(EnOrDi == ENABLE)
	{
		if(pUSARTx == USART1)
		{
			USART1_PCLK_EN();
		}
		else if(pUSARTx == USART2)
		{
			USART2_PCLK_EN();
		}
		else if(pUSARTx == USART6)
		{
			USART6_PCLK_EN();
		}
	}
	else
	{
		if(pUSARTx == USART1)
		{
			USART1_PCLK_DIS();
		}
		else if(pUSARTx == USART2)
		{
			USART2_PCLK_DIS();
		}
		else if(pUSARTx == USART6)
		{
			USART6_PCLK_DIS();
		}
	}
}

// To Enable USART
void USART_PeripheralControl(USART_RegDef_t *pUSARTx, uint8_t cmd)
{
	if(cmd == ENABLE)
	{
		pUSARTx->CR1 |= (1 << 13);
	}
	else
	{
		pUSARTx->CR1 &= ~(1 << 13);
	}
}

uint8_t USART_GetFlagStatus(USART_RegDef_t *pUSARTx, uint8_t StatusFlagName)
{
    if(pUSARTx->SR & StatusFlagName)       // Check if the specified flag is set in the status register(SR_TXE, SR_RXNE, SR_TC)
	{
    	return SET;
    }

   return RESET;
}

void USART_SetBaudRate(USART_RegDef_t *pUSARTx, uint32_t BaudRate)
{
	uint32_t PCLKx;
	uint32_t USARTDIV;
	uint32_t M_part, F_part;
	uint32_t tempreg = 0;

	// USART Selection
	if(pUSARTx == USART1 || pUSARTx == USART6)
	{
        // USART1 and USART6 are on APB2
        PCLKx = RCC_GetPCLK2Value();
	}
	else
	{
		PCLKx = RCC_GetPCLK1Value();
	}

	// 	Check OVER8 bit
	//	OVER8 = Oversampling mode (0 = 16x, 1 = 8x)
	//	Multiplied by 100 on bothside to extract the F_part
    if (pUSARTx->CR1 & (1 << 15))
    {
        // OVER8 = 1, oversampling by 8
    	USARTDIV = ((25 * PCLKx) / (2 * BaudRate));
    }
    else
    {
        // OVER8 = 0, oversampling by 16
    	USARTDIV = ((25 * PCLKx) / (4 * BaudRate));
    }

    //	Calculate MANTISSA & FRACTION
    M_part = (USARTDIV / 100);
    F_part = (USARTDIV - (M_part * 100));

    //	Final F_part calculation to be pushed to the register
    // Calculate final fraction value
    if (pUSARTx->CR1 & (1 << 15))
    {
        // OVER8 = 1
        F_part = ((F_part * 8) + 50) / 100;
        F_part &= 0x07;  // Only 3 bits for OVER8
    }
    else
    {
        // OVER8 = 0
        F_part = ((F_part * 16) + 50) / 100;
        F_part &= 0x0F;  // 4 bits for normal mode
    }

    //	Fit M_part (15:4), F_part (3:0)
    tempreg |= (M_part << 4) | (F_part);

    pUSARTx->BRR = tempreg;

}

void USART_Init(USART_Handle_t *pUSARTHandle)
{
	uint32_t tempreg = 0;
/*** CR1 Configuration ***/
	//	1. Set the mode Tx, Rx, Tx/Rx
	if(pUSARTHandle->USART_PinConfig.USART_Mode == USART_MODE_ONLY_TX)
	{
		tempreg |= (1 << 3);	//	TE bit
	}
	else
	if(pUSARTHandle->USART_PinConfig.USART_Mode == USART_MODE_ONLY_RX)
	{
		tempreg |= (1 << 2);	//	RE bit
	}
	else
	if(pUSARTHandle->USART_PinConfig.USART_Mode == USART_MODE_TXRX)
	{
		tempreg |= (1 << 2) | (1 << 3);
	}
	//pUSARTHandle->pUSARTx->CR1 = tempreg;	// Avoiding CR1 updation twice

	//	2. Configure word length
	tempreg |= (pUSARTHandle->USART_PinConfig.USART_WordLength << 12);

	//	3.	Parity settings
	if(pUSARTHandle->USART_PinConfig.USART_ParityControl == USART_PARITY_EN_EVEN)
	{
		tempreg |= (1 << 10); // Parity Control Enable
		// PS bit = 0 for even parity (default)
	}
	else
	if(pUSARTHandle->USART_PinConfig.USART_ParityControl == USART_PARITY_EN_ODD)
	{
		tempreg |= (1 << 10); // Parity Control Enable
		tempreg |= (1 << 9); // PS bit = 1 for odd parity
	}
	pUSARTHandle->pUSARTx->CR1 = tempreg;

/*** CR2 Configuration ***/
	// Set the stop bits
	tempreg = 0;
	tempreg	|= (pUSARTHandle->USART_PinConfig.USART_NoOfStopBits << 12);
	pUSARTHandle->pUSARTx->CR2 = tempreg;

/*** CR3 Configuration ***/
	// Enable USART Tx/Rx
	tempreg = 0;
	if(pUSARTHandle->USART_PinConfig.USART_HWFlowControl == USART_HW_FLOW_CTRL_CTS)
	{
		tempreg	|= (1 << 9);
	}
	else
	if(pUSARTHandle->USART_PinConfig.USART_HWFlowControl == USART_HW_FLOW_CTRL_RTS)
	{
		tempreg	|= (1 << 8);
	}
	else
	if(pUSARTHandle->USART_PinConfig.USART_HWFlowControl == USART_HW_FLOW_CTRL_CTS_RTS)
	{
		tempreg	|= (1 << 9)	| (1 << 8);
	}
	pUSARTHandle->pUSARTx->CR3 = tempreg;


	/*
	 * Configure the Baud Rate
	 */
	USART_SetBaudRate(pUSARTHandle->pUSARTx , pUSARTHandle->USART_PinConfig.USART_Baud);
}

void USART_SendData(USART_Handle_t *pUSARTHandle, uint8_t *pTxBuffer, uint32_t len)
{
	uint16_t *pdata;
	for(uint32_t i = 0; i < len; i++)
	{

		//	Wait until TXE flag is set
		while(!(pUSARTHandle->pUSARTx->SR & (1 << 7)));

		//Check for word length = 9
		if(pUSARTHandle->USART_PinConfig.USART_WordLength == USART_WORDLEN_9BITS)
		{
			pdata = (uint16_t*)pTxBuffer;
			pUSARTHandle->pUSARTx->DR = (*pdata & (uint16_t)0x01FF);

			if(pUSARTHandle->USART_PinConfig.USART_ParityControl == USART_PARITY_DISABLE)
			{
                // No parity: 9 data bits, increment by 2
				pTxBuffer += 2;
			}
			else
			{
				// Parity used: 8 data bits + 1 parity
				pTxBuffer++;
			}
		}
		else	// if 8-bit data
		{
			pUSARTHandle->pUSARTx->DR = *pTxBuffer & (uint8_t)0xFF;
			pTxBuffer++; // Move to the next byte for the next loop iteration
		}

	}

    // Wait until TC flag is set (transmission complete)
    while (!USART_GetFlagStatus(pUSARTHandle->pUSARTx, USART_FLAG_TC));
}

void USART_ReceiveData(USART_Handle_t *pUSARTHandle, uint8_t *pRxBuffer, uint32_t len)
{
	for(uint32_t i = 0; i < len; i++)
	{
		while(!(pUSARTHandle->pUSARTx->SR & (USART_FLAG_RXNE)));
		if(pUSARTHandle->USART_PinConfig.USART_WordLength == USART_WORDLEN_9BITS)
		{
			if(pUSARTHandle->USART_PinConfig.USART_ParityControl == USART_PARITY_DISABLE)
			{
				(*(uint16_t*)pRxBuffer) = (uint16_t)(pUSARTHandle->pUSARTx->DR & 0x1FF);
				pRxBuffer+=2;
			}
			else
			{
				*pRxBuffer = (uint8_t)(pUSARTHandle->pUSARTx->DR & 0xFF);
				pRxBuffer++;
			}
		}
		else	// 8-bit Reception
		{
			if(pUSARTHandle->USART_PinConfig.USART_ParityControl == USART_PARITY_DISABLE)
			{
				*pRxBuffer = (uint8_t)(pUSARTHandle->pUSARTx->DR & (uint8_t)0xFF);
				pRxBuffer++;
			}
			else
			{
				*pRxBuffer = (uint8_t)(pUSARTHandle->pUSARTx->DR & (uint8_t)0x7F);
				pRxBuffer++;
			}

		}

	}
}

void USARTReceiveString(USART_Handle_t *pUSARTHandle, char* str, uint8_t buff_size)
{
	char ch;
	uint8_t i=0;// index
	while(1)
	{
		 while(!((pUSARTHandle->pUSARTx->SR) & (1 << USART_SR_RXNE)));// wait till data received in buffer
		ch= pUSARTHandle->pUSARTx->DR;// read received data

		if(ch=='\n')
		{
			break;
		}
		if(i+1 < buff_size)// prevent buffer overflow
		{
			str[i]=ch;// store in buffer
			i++;
		}
		else{break;}

	}
	str[i]='\0';
}
