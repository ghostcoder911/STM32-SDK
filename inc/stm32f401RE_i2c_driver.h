/*
 * stm32f401RE_i2c_driver.h
 *
 *  Created on: Aug 14, 2026
 *      Author: ANEESA
 */

#ifndef INC_STM32F401RE_I2C_DRIVER_H_
#define INC_STM32F401RE_I2C_DRIVER_H_

#include "stm32f401RE.h"

/*Config. structure for I2C peripheral*/
typedef struct
{
	uint32_t I2C_SCLSpeed;
	uint8_t  I2C_DeviceAddress;
	uint8_t  I2C_AckControl;
	uint8_t  I2C_FMDutyCycle;

}I2C_Config_t;

typedef struct
{
	I2C_RegDef_t 	*pI2Cx;
	I2C_Config_t 	I2C_Config;
}I2C_Handle_t;

/*I2C_sclspeed macro*/

#define I2C_SCL_SPEED_SM 	100000
#define I2C_SCL_SPEED_FM 	400000


/*I2C_Ackcntrl macro*/

#define I2C_ACK_ENABLE		1
#define I2C_ACK_DISABLE		0

/*i2c FMDuty Cycle*/
#define I2C_FM_DUTY_2        0
#define I2C_FM_DUTY_16_9     1

/*I2C related status flag mdefinitions */

#define I2C_FLAG_SB				(1 << I2C_SR1_SB)
#define I2C_FLAG_ADDR			(1 << I2C_SR1_ADDR)
#define I2C_FLAG_BTF			(1 << I2C_SR1_BTF)
#define I2C_FLAG_ADD10			(1 << I2C_SR1_ADD10)
#define I2C_FLAG_STOPF			(1 << I2C_SR1_STOPF)
#define I2C_FLAG_RXNE			(1 << I2C_SR1_RXNE)
#define I2C_FLAG_TXE			(1 << I2C_SR1_TXE)
#define I2C_FLAG_BERR			(1 << I2C_SR1_BERR)
#define I2C_FLAG_ARLO			(1 << I2C_SR1_ARLO)
#define I2C_FLAG_AF				(1 << I2C_SR1_AF)
#define I2C_FLAG_OVR			(1 << I2C_SR1_OVR)
#define I2C_FLAG_TIMEOUT		(1 << I2C_SR1_TIMEOUT)

/*Peripheral clk setup*/

void I2C_PeriClockControl(I2C_RegDef_t*pI2Cx, uint8_t ENorDi);

void I2C_Init(I2C_Handle_t *pI2CHandle);

void I2C_DeInit(I2C_RegDef_t *pI2Cx);

void I2C_MainSendData(I2C_Handle_t *pI2CHandle, uint8_t *pTxBuffer, uint32_t Len, uint8_t SunNodeAddr);

void I2C_MainReceiveData(I2C_Handle_t *pI2CHandle, uint8_t *pRxBuffer, uint8_t Len, uint8_t SubNodeAdrr);



#endif /* INC_STM32F401RE_I2C_DRIVER_H_ */
