/*
 * stm32f401RE_i2c_driver.c
 *
 *  Created on: Aug 14, 2026
 *      Author: ANEESA
 */
#include "stm32f401RE.h"
#include "stm32f401Re_rcc_driver.h"

static void I2C_GenerateStartCondition(I2C_RegDef_t *pI2Cx);

static void I2C_GenerateStopCondition(I2C_RegDef_t *pI2Cx);

static void I2C_ExecuteAddressPhaseWrite(I2C_RegDef_t *pI2Cx, uint8_t SubNodeAddr);

static void I2C_ClearADDRFlag(I2C_Handle_t *pI2CHandle);

void I2C_PeriClockControl(I2C_RegDef_t *pI2Cx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		if(pI2Cx == I2C1)
		{
			I2C1_PCLK_EN();
		}else if (pI2Cx == I2C2)
		{
			I2C2_PCLK_EN();
		}else if (pI2Cx == I2C3)
		{
			I2C3_PCLK_EN();
		}
	}
	else
	{
		if(pI2Cx == I2C1)
		{
			I2C1_PCLK_DI();
		}else if (pI2Cx == I2C2)
		{
			I2C2_PCLK_DI();
		}else if (pI2Cx == I2C3)
		{
			I2C3_PCLK_DI();
		}
	}
}

void I2C_Init(I2C_Handle_t *pI2CHandle)
{
	//void I2C_Init(I2C_Handle_t *pI2CHandle)
	//{
		uint32_t tempreg = 0 ;

		//enable the clock for the I2Cx peripheral
		I2C_PeriClockControl(pI2CHandle->pI2Cx,ENABLE);

		//ack control bit
		tempreg |= pI2CHandle->I2C_Config.I2C_AckControl << 10;
		pI2CHandle->pI2Cx->CR1 = tempreg;

		//configure the FREQ field of CR2
		tempreg = 0;
		tempreg |= RCC_GetPCLK1Value() /1000000U ;
		pI2CHandle->pI2Cx->CR2 =  (tempreg & 0x3F);

	   //program the device own address
		tempreg = 0;
		tempreg |= pI2CHandle->I2C_Config.I2C_DeviceAddress << 1;
		tempreg |= ( 1 << 14);
		pI2CHandle->pI2Cx->OAR1 = tempreg;

		//CCR calculations
		uint16_t ccr_value = 0;
		tempreg = 0;
		if(pI2CHandle->I2C_Config.I2C_SCLSpeed <= I2C_SCL_SPEED_SM)
		{
			//mode is standard mode
			ccr_value = (RCC_GetPCLK1Value() / ( 2 * pI2CHandle->I2C_Config.I2C_SCLSpeed ) );
			tempreg |= (ccr_value & 0xFFF);
		}else
		{
			//mode is fast mode
			tempreg |= ( 1 << 15);	// set to fast mode inbit no.15
			tempreg |= (pI2CHandle->I2C_Config.I2C_FMDutyCycle << 14);
			if(pI2CHandle->I2C_Config.I2C_FMDutyCycle == I2C_FM_DUTY_2)
			{
				ccr_value = (RCC_GetPCLK1Value() / ( 3 * pI2CHandle->I2C_Config.I2C_SCLSpeed ) );
			}else
			{
				ccr_value = (RCC_GetPCLK1Value() / ( 25 * pI2CHandle->I2C_Config.I2C_SCLSpeed ) );
			}
			tempreg |= (ccr_value & 0xFFF);
		}
		pI2CHandle->pI2Cx->CCR = tempreg;

}
void I2C_DeInit(I2C_RegDef_t *pI2Cx)
{
	if (pI2Cx == I2C1)
			{
				I2C1_REG_RESET();
			}
			else if (pI2Cx == I2C2)
				{
					I2C2_REG_RESET();
				}
			else if (pI2Cx == I2C3)
				{
					I2C3_REG_RESET();
				}
}

static void I2C_GenerateStartCondition(I2C_RegDef_t *pI2Cx)
{
	pI2Cx->CR1 |= ( 1 << I2C_CR1_START);
}

static void I2C_GenerateStopCondition(I2C_RegDef_t *pI2Cx)
{
	pI2Cx->CR1 |= ( 1 << I2C_CR1_STOP);
}

uint8_t I2C_GetFlagStatus(I2C_RegDef_t *pI2Cx , uint32_t FlagName)
{
	if(pI2Cx->SR1 & FlagName)
	{
		return FLAG_SET;
	}
	return FLAG_RESET;
}

static void I2C_ExecuteAddressPhaseWrite(I2C_RegDef_t *pI2Cx, uint8_t SubNodeAddr)
{
	SubNodeAddr = SubNodeAddr << 1;
	SubNodeAddr &= ~(1);
	pI2Cx->DR = SubNodeAddr ;

}

static void I2C_ClearADDRFlag(I2C_Handle_t *pI2CHandle)
{
	uint32_t dummy_read;
	// clear the ADDR flag(read SR1, SR2)
	dummy_read = pI2CHandle->pI2Cx->SR1;
	dummy_read = pI2CHandle->pI2Cx->SR2;
	(void)dummy_read;
}


void I2C_MainSendData(I2C_Handle_t *pI2CHandle, uint8_t *pTxBuffer, uint32_t Len, uint8_t SubNodeAddr)
{
	// generate start condition
	I2C_GenerateStartCondition(pI2CHandle->pI2Cx);

	// Start generation completion can be confirmed by checking the SB flag in SR1
	// NB: Until SB is cleared SCL will be streched ie., pulled to LOW

	while( ! I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_SB) );

	/* Send the address of the slave with r/nw bit set to w(0) (total 8 bits)*/
	I2C_ExecuteAddressPhaseWrite(pI2CHandle->pI2Cx, SubNodeAddr);

	/* Check ADDr flag in SR1 to confirm the address phase is completed*/
	while(! I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_ADDR) );

	/* Clear the ADDR flag according to its software sequence
	 * NB: Until ADDR is cleared SCL will be strecheed (pulled to LOW)*/
	I2C_ClearADDRFlag(pI2CHandle);

	// send the data until len becomes 0

	while(Len > 0)
	{
		// wait until TXE is set
		while( ! I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_TXE) );
		pI2CHandle->pI2Cx->DR= *pTxBuffer;
		pTxBuffer++;
		Len--;
	}

	/*when Len becomes 0 wait for TXE=1 And BTF=1 before generating the STOP condition
	 * NB: TXE=1 &BTF+1 means that both SR and DR are empty and next transition should begin
	 * when BTF =1 SCl will be Streched (pulled to low)*/
	while( ! I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_TXE) );

	while( ! I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_BTF) );

	I2C_GenerateStopCondition(pI2CHandle->pI2Cx);

}


void I2C_MainReceiveData(I2C_Handle_t *pI2CHandle, uint8_t *pRxBuffer, uint8_t Len, uint8_t SubNodeAddr)
{

}

