/*
 * stm32f401RE.h
 *
 *  Created on: Aug 4, 2026
 *      Author: ANEESA
 */

#ifndef STM32F401RE_H_
#define STM32F401RE_H_

#include <stdint.h>
#define __vo  volatile
/*
 * Memory base  address
 */
#define FLASH_BASEADDR 				0x08000000U
#define ROM_BASEADDR 				0x1FFF0000U
#define SRAM_BASEADDR 				0x20000000U

/*
 * Peripheral Base address*/

#define PERIPH_BASEADDR 			0x40000000U
#define APB1_BASEADDR 				PERIPH_BASEADDR
#define APB2_BASEADDR 				0x40010000U
#define AHB1_BASEADDR 				0x40020000U
#define AHB2_BASEADDR 				0x50000000U

/* AHB1 peripheral base address*/

#define GPIOA_BASEADDR 		(AHB1_BASEADDR + 0X0000)
#define GPIOB_BASEADDR 		(AHB1_BASEADDR + 0X0400)
#define GPIOC_BASEADDR 		(AHB1_BASEADDR + 0X0800)
#define GPIOD_BASEADDR 		(AHB1_BASEADDR + 0X0C00)
#define GPIOE_BASEADDR 		(AHB1_BASEADDR + 0X1000)
#define GPIOH_BASEADDR 		(AHB1_BASEADDR + 0X1C00)

#define RCC_BASEADDR 		(AHB1_BASEADDR + 0X3800)

/*AHB1 peripheral base address*/

#define USB_BASEADDR 		AHB2_BASEADDR

/*APB1 Peripheral base address*/

#define TIM2_BASEADDR 			(APB1_BASEADDR + 0X0000)
#define TIM3_BASEADDR 			(APB1_BASEADDR + 0X0400)
#define TIM4_BASEADDR 			(APB1_BASEADDR + 0X0800)
#define TIM5_BASEADDR 			(APB1_BASEADDR + 0X0C00)

#define SPI2_BASEADDR 			(APB1_BASEADDR + 0X3800)
#define SPI3_BASEADDR 			(APB1_BASEADDR + 0X3C00)

#define USART2_BASEADDR 		(APB1_BASEADDR + 0X4400)

#define I2C1_BASEADDR 			(APB1_BASEADDR + 0X5400)
#define I2C2_BASEADDR 			(APB1_BASEADDR + 0X5800)
#define I2C3_BASEADDR 			(APB1_BASEADDR + 0X5C00)

/*APB2 peripheral base address*/

#define TIM1_BASEADDR 					(APB2_BASEADDR + 0X0000)

#define USART1_BASEADDR 				(APB2_BASEADDR + 0X1000)
#define USART6_BASEADDR 				(APB2_BASEADDR + 0X1400)

#define ADC1_BASEADDR 					(APB2_BASEADDR + 0X2000)

#define SPI1_BASEADDR 					(APB2_BASEADDR + 0X3000)
#define SPI4_BASEADDR 					(APB2_BASEADDR + 0X3400)

#define SYSCFG_BASEADDR 				(APB2_BASEADDR + 0X3800)
#define EXTI_BASEADDR 					(APB2_BASEADDR + 0X3C00)

#define TIM9_BASEADDR 					(APB2_BASEADDR + 0X4000)
#define TIM10_BASEADDR 					(APB2_BASEADDR + 0X4400)
#define TIM11_BASEADDR 					(APB2_BASEADDR + 0X4800)

/*
 * GPIO Register definition structure*/
typedef struct
{
	__vo uint32_t MODER;    // mode register,  		offset:0x00
	__vo uint32_t OTYPER;	// o/p type reg.,  		offset:0x04
	__vo uint32_t OSPEEDR;	// o/p speed reg., 		offset:0x08
	__vo uint32_t PUPDR;	// pull up/down reg., 	offset:0x0C
	__vo uint32_t IDR;		// i/p data reg., 		offset:0x10
	__vo uint32_t ODR;		// o/p data reg., 		offset:0x14
	__vo uint32_t BSRR;		// bit set/reset reg., 	offset:0x18
	__vo uint32_t LCKR;		// config lock reg., 	offset:0x1C
	__vo uint32_t AFR[2];	// alternate fun reg., 	offset:0x20-24
}GPIO_RegDef_t;

/* RCC register definitions
 *this registers are needed for  enabling peripheral clock */
typedef struct
{
	__vo uint32_t CR;				//clock cntrl reg.,						offset:0x00
	__vo uint32_t PLLCFGR;			//PLL config reg.,						offset:0x04
	__vo uint32_t CFGR;				//clock config reg.,					offset:0x08
	__vo uint32_t CIR;				//clock interrupt reg.,					offset:0x0C
	__vo uint32_t AHB1RSTR;			//AHB1 peripheral reset reg.,			offset:0x10
	__vo uint32_t AHB2RSTR;			//AHB2 peripheral reset reg.,			offset:0x14
	 uint32_t RESERVED0[2];			//reserved ,							offset:0x18-1C
	__vo uint32_t APB1RSTR;			//APB1 peripheral reset reg.,			offset:0x20
	__vo uint32_t APB2RSTR;			//APB2 peripheral reset reg.,			offset:0x24
	 uint32_t RESERVED1[2];			//reserved								offset:0x28-2C
	__vo uint32_t AHB1ENR;			// AHB1 clock enable reg.,				offset:0x30
	__vo uint32_t AHB2ENR;			// AHB2 clock enable reg.,				offset:0x34
	__vo uint32_t RESERVED2[2];		// reserved,							offset:0x38-3C
	__vo uint32_t APB1ENR;			// APB1 clock enable reg.,				offset:0x40
	__vo uint32_t APB2ENR;			// APB2 clock enable reg.,				offset:0x44
	uint32_t RESERVED3[2];			// reg.,								offset:0x48-4C
	__vo uint32_t AHB1LPENR;		//AHB1 clk enable lowpwr mode reg.,		offset:0x50
	__vo uint32_t AHB2LPENR;		//AHB2 clk enable lowpwr mode reg.,		offset:0x54
	uint32_t RESERVED4[2];			// reg.,								offset:0x58-5C
	__vo uint32_t APB1LPENR;		//APB1 clk enable lowpwr mode reg.,		offset:0x60
	__vo uint32_t APB2LPENR;		//APB2 clk enable lowpwr mode reg.,		offset:0x64
	uint32_t RESERVED5[2];			// reg.,								offset:0x68-6C
	__vo uint32_t BDCR;				// backup domain cntrl reg.,			offset:0x70
	__vo uint32_t CSR;				// clk cntrl & status reg.,				offset:0x74
	 uint32_t RESERVED6[2];			// reg.,								offset:0x78-7C
	__vo uint32_t SSCGR;			// spread spctrm clk genratn reg.,		offset:0x80
	__vo uint32_t PLLI2SCFGR;		// PLLI2S cnfg reg.,					offset:0x84
	__vo uint32_t DCKCFGR;			// dedictd clk cnfg reg.,				offset:0x8C

}RCC_RegDef_t;

/*I2C register definitions*/
typedef struct
{
	__vo uint32_t  CR1;			//I2C cntrl reg1.,				offset:0x00
	__vo uint32_t  CR2;			//I2C cntrl reg2.,				offset:0x04
	__vo uint32_t  OAR1;		//I2C own adres reg1.,			offset:0x08
	__vo uint32_t  OAR2;		//I2C own adres reg2.,			offset:0x0C
	__vo uint32_t  DR;			//I2C data reg.,				offset:0x10
	__vo uint32_t  SR1;			//I2C status reg1.,				offset:0x14
	__vo uint32_t  SR2;			//I2C status reg2.,				offset:0x18
	__vo uint32_t  CCR;			//I2C clk cntrl reg.,			offset:0x1C
	__vo uint32_t  TRISE;		//I2C TRISE reg.,				offset:0x20
	__vo uint32_t  FLTR;		//I2C FLTR reg.,				offset:0x24

}I2C_RegDef_t;

/* SPI register definitions*/
typedef struct
{
	__vo uint32_t CR1; 			//SPI cntrl reg.,   			offset:0x00
	__vo uint32_t SR;			//SPI status reg.,   			offset:0x08
	__vo uint32_t DR;			//SPI data reg.,	   			offset:0x0C
	__vo uint32_t CRCPR;		//SPI CRC polynomial reg.,   	offset:0x10
	__vo uint32_t RXCRCR;		//SPI RX CRC reg.,   			offset:0x14
	__vo uint32_t TXCRCR;		//SPI TX CRCreg.,   			offset:0x18
	__vo uint32_t I2SCFGR;		//SPI configuration reg.,  		offset:0x1C
	__vo uint32_t I2SPR;		//SPI prescalar reg.,   		offset:0x20
}SPI_RegDef_t;

/*USART register definition*/

typedef struct
{
	__vo uint32_t  SR;			// USART status reg., 			offset:0x00
	__vo uint32_t  DR;			// USART data reg., 			offset:0x04
	__vo uint32_t  BRR;			// USART baudrate reg., 		offset:0x08
	__vo uint32_t  CR1;			// USART cntrl reg., 			offset:0x0C
	__vo uint32_t  CR2;			// USART cntrl reg., 			offset:0x10
	__vo uint32_t  CR3;			// USART cntrl reg., 			offset:0x14
	__vo uint32_t  GTPR;		// USART guard & prescl reg., 	offset:0x18
}USART_RegDef_t;

/*SYSCFG */

typedef struct
{
	__vo uint32_t	MEMRMP;
	__vo uint32_t	PMC;
	__vo uint32_t	EXTICR1;
	__vo uint32_t	EXTICR2;
	__vo uint32_t	EXTICR3;
	__vo uint32_t	EXTICR4;
	__vo uint32_t	CMPCR;
}SYSCFG_RegDef_t;

/* EXTI register definitions*/

typedef struct
{
	__vo uint32_t	IMR;
	__vo uint32_t	EMR;
	__vo uint32_t	RTSR;
	__vo uint32_t	FTSR;
	__vo uint32_t	SWIER;
	__vo uint32_t	PR;
}EXTI_RegDef_t;

/* peripheral  definitions
 * macros typecast base addresses to register structure pointers*/

#define GPIOA  ((GPIO_RegDef_t*)GPIOA_BASEADDR)
#define GPIOB  ((GPIO_RegDef_t*)GPIOB_BASEADDR)
#define GPIOC  ((GPIO_RegDef_t*)GPIOC_BASEADDR)
#define GPIOD  ((GPIO_RegDef_t*)GPIOD_BASEADDR)
#define GPIOE  ((GPIO_RegDef_t*)GPIOE_BASEADDR)
#define GPIOH  ((GPIO_RegDef_t*)GPIOH_BASEADDR)

#define RCC    ((RCC_RegDef_t*)RCC_BASEADDR)

#define I2C1   ((I2C_RegDef_t*)I2C1_BASEADDR)
#define I2C2   ((I2C_RegDef_t*)I2C2_BASEADDR)
#define I2C3   ((I2C_RegDef_t*)I2C3_BASEADDR)

#define SPI1   ((SPI_RegDef_t*)SPI1_BASEADDR )
#define SPI2   ((SPI_RegDef_t*)SPI2_BASEADDR )
#define SPI3   ((SPI_RegDef_t*)SPI3_BASEADDR )
#define SPI4   ((SPI_RegDef_t*)SPI4_BASEADDR )

#define USART1   ((USART_RegDef_t*)USART1_BASEADDR )
#define USART2   ((USART_RegDef_t*)USART2_BASEADDR )
#define USART6   ((USART_RegDef_t*)USART6_BASEADDR )


/* clock enable macros for GPIOs
 * GPIO clks are in AHB1 bus and in RCC registers*/

#define GPIOA_PCLK_EN()		(RCC-> AHB1ENR |= (1 << 0))
#define GPIOB_PCLK_EN()		(RCC-> AHB1ENR |= (1 << 1))
#define GPIOC_PCLK_EN()		(RCC-> AHB1ENR |= (1 << 2))
#define GPIOD_PCLK_EN()		(RCC-> AHB1ENR |= (1 << 3))
#define GPIOE_PCLK_EN()		(RCC-> AHB1ENR |= (1 << 4))
#define GPIOH_PCLK_EN()		(RCC-> AHB1ENR |= (1 << 7))

/*I2C,SPI, USART clock enable macros*/

#define I2C1_PCLK_EN()		(RCC-> APB1ENR |= (1 << 21))
#define I2C2_PCLK_EN()		(RCC-> APB1ENR |= (1 << 22))
#define I2C3_PCLK_EN()		(RCC-> APB1ENR |= (1 << 23))

#define SPI1_PCLK_EN()		(RCC-> APB2ENR |= (1 << 12))
#define SPI2_PCLK_EN()		(RCC-> APB1ENR |= (1 << 14))
#define SPI3_PCLK_EN()		(RCC-> APB1ENR |= (1 << 15))
#define SPI4_PCLK_EN()		(RCC-> APB2ENR |= (1 << 13))

#define USART1_PCLK_EN()	(RCC-> APB2ENR |= (1 << 4))
#define USART2_PCLK_EN()	(RCC-> APB1ENR |= (1 << 17))
#define USART6_PCLK_EN()	(RCC-> APB2ENR |= (1 << 5))

/* clock disable macros for GPIOs
 * GPIO clks are in AHB1 bus and in RCC registers*/

#define GPIOA_PCLK_DI()		(RCC-> AHB1ENR &= ~(1 << 0))
#define GPIOB_PCLK_DI()		(RCC-> AHB1ENR &= ~(1 << 1))
#define GPIOC_PCLK_DI()		(RCC-> AHB1ENR &= ~(1 << 2))
#define GPIOD_PCLK_DI()		(RCC-> AHB1ENR &= ~(1 << 3))
#define GPIOE_PCLK_DI()		(RCC-> AHB1ENR &= ~(1 << 4))
#define GPIOH_PCLK_DI()		(RCC-> AHB1ENR &= ~(1 << 7))

/*I2C,SPI, USART clock disable macros*/

#define I2C1_PCLK_DI()		(RCC-> APB1ENR &= ~(1 << 21))
#define I2C2_PCLK_DI()		(RCC-> APB1ENR &= ~(1 << 22))
#define I2C3_PCLK_DI()		(RCC-> APB1ENR &= ~(1 << 23))

#define SPI1_PCLK_DI()		(RCC-> APB2ENR &= ~(1 << 12))
#define SPI2_PCLK_DI()		(RCC-> APB1ENR &= ~(1 << 14))
#define SPI3_PCLK_DI()		(RCC-> APB1ENR &= ~(1 << 15))
#define SPI4_PCLK_DI()		(RCC-> APB2ENR &= ~(1 << 13))

#define USART1_PCLK_DI()	(RCC-> APB2ENR &= ~(1 << 4))
#define USART2_PCLK_DI()	(RCC-> APB1ENR &= ~(1 << 17))
#define USART6_PCLK_DI()	(RCC-> APB2ENR &= ~(1 << 5))

/* Macros To reset GPIOx Peripherals*/

#define GPIOA_REG_RESET()                   do{ (RCC->AHB1RSTR |= (1 << 0)); (RCC->AHB1RSTR &= ~(1 << 0)); }while(0)
#define GPIOB_REG_RESET()                   do{ (RCC->AHB1RSTR |= (1 << 1)); (RCC->AHB1RSTR &= ~(1 << 1)); }while(0)
#define GPIOC_REG_RESET()                   do{ (RCC->AHB1RSTR |= (1 << 2)); (RCC->AHB1RSTR &= ~(1 << 2)); }while(0)
#define GPIOD_REG_RESET()                   do{ (RCC->AHB1RSTR |= (1 << 3)); (RCC->AHB1RSTR &= ~(1 << 3)); }while(0)
#define GPIOE_REG_RESET()                   do{ (RCC->AHB1RSTR |= (1 << 4)); (RCC->AHB1RSTR &= ~(1 << 4)); }while(0)
#define GPIOH_REG_RESET()                   do{ (RCC->AHB1RSTR |= (1 << 7)); (RCC->AHB1RSTR &= ~(1 << 7)); }while(0)

/*Macros to reset I2C peripherals*/

#define I2C1_REG_RESET()                    do{ (RCC->APB1RSTR |= (1 << 21)); (RCC->APB1RSTR &= ~(1 << 21)); }while(0)
#define I2C2_REG_RESET()                    do{ (RCC->APB1RSTR |= (1 << 22)); (RCC->APB1RSTR &= ~(1 << 22)); }while(0)
#define I2C3_REG_RESET()                    do{ (RCC->APB1RSTR |= (1 << 23)); (RCC->APB1RSTR &= ~(1 << 23)); }while(0)

/* macros to reset SPI peripherals*/

#define SPI1_REG_RESET()					 do{ (RCC->APB2RSTR |= (1 << 12)); (RCC->APB2RSTR &= ~(1 << 12)); }while(0)
#define SPI2_REG_RESET()					 do{ (RCC->APB1RSTR |= (1 << 14)); (RCC->APB1RSTR &= ~(1 << 14)); }while(0)
#define SPI3_REG_RESET()					 do{ (RCC->APB1RSTR |= (1 << 15)); (RCC->APB1RSTR &= ~(1 << 15)); }while(0)
#define SPI4_REG_RESET()					 do{ (RCC->APB2RSTR |= (1 << 13)); (RCC->APB2RSTR &= ~(1 << 13)); }while(0)


#define ENABLE			1
#define DISABLE			0
#define SET				ENABLE
#define RESET			DISABLE
#define GPIO_PIN_SET	SET
#define GPIO_PIN_RESET	RESET
#define FLAG_SET 		SET
#define FLAG_RESET 		RESET


/*Bit position definition of I2C peripheral*/

//Bit position definition I2C_CR1

#define I2C_CR1_PE		                    0
#define I2C_CR1_SMBUS                       1
#define I2C_CR1_SMBTYPE                     3
#define I2C_CR1_ENARP                       4
#define I2C_CR1_ENPEC                       5
#define I2C_CR1_ENGC                        6
#define I2C_CR1_NOSTRETCH                   7
#define I2C_CR1_START                       8
#define I2C_CR1_STOP                        9
#define I2C_CR1_ACK                         10
#define I2C_CR1_POS                         11
#define I2C_CR1_PEC                         12
#define I2C_CR1_ALERT                       13
#define I2C_CR1_SWRST                       15

//Bit position definition I2C_CR2

#define I2C_CR2_FREQ                        0
#define I2C_CR2_ITERREN                     8
#define I2C_CR2_ITEVTEN                     9
#define I2C_CR2_ITBUFEN                     10
#define I2C_CR2_DMAEN                       11
#define I2C_CR2_LAST                        12

//Bit position definition I2C_OAR1

#define I2C_OAR1_ADD0                       0
#define I2C_OAR1_ADD71                      1
#define I2C_OAR1_ADD98                      8
#define I2C_OAR1_ADDMODE                    15

//Bit position definitions I2C_SR1

#define I2C_SR1_SB                          0
#define I2C_SR1_ADDR                        1
#define I2C_SR1_BTF                         2
#define I2C_SR1_ADD10                       3
#define I2C_SR1_STOPF                       4
#define I2C_SR1_RXNE                        6
#define I2C_SR1_TXE                         7
#define I2C_SR1_BERR                        8
#define I2C_SR1_ARLO                        9
#define I2C_SR1_AF                          10
#define I2C_SR1_OVR                         11
#define I2C_SR1_PECERR                      12
#define I2C_SR1_TIMEOUT                     14
#define I2C_SR1_SMBALERT                    15

//Bit position definitions I2C_SR2

#define I2C_SR2_MSL                         0
#define I2C_SR2_BUSY                        1
#define I2C_SR2_TRA                         2
#define I2C_SR2_GENCALL                     4
#define I2C_SR2_SMBDEFAULT                  5
#define I2C_SR2_SMBHOST                     6
#define I2C_SR2_DUALF                       7

//Bit position definitions I2C_CCR

#define I2C_CCR_CCR                         0
#define I2C_CCR_DUTY                        14
#define I2C_CCR_FS                          15

// Bit position definition SPI_CR1

#define SPI_CR1_CPHA						0
#define SPI_CR1_CPOL						1
#define SPI_CR1_MSTR						2
#define SPI_CR1_BR							3
#define SPI_CR1_SPE							6
#define SPI_CR1_LSBFIRST					7
#define SPI_CR1_SSI							8
#define SPI_CR1_SSM							9
#define SPI_CR1_RXONLY						10
#define SPI_CR1_DFF							11
#define SPI_CR1_CRCNEXT						12
#define SPI_CR1_CRCEN						13
#define SPI_CR1_BIDIOE						14
#define SPI_CR1_BIDIMODE					15

// Bit position definition SPI_CR2

#define SPI_CR2_RXDMAEN						0
#define SPI_CR2_TXDMAEN 					1
#define SPI_CR2_SSOE 						2
#define SPI_CR2_FRF							4
#define SPI_CR2_ERRIE						5
#define SPI_CR2_RXNEIE						6
#define SPI_CR2_TXEIE						7

// Bit position definition SPI_SR

#define SPI_SR_RXNE							0
#define SPI_SR_TXE							1
#define SPI_SR_CHSIDE 						2
#define SPI_SR_UDR 							3
#define SPI_SR_CRCERR						4
#define SPI_SR_MODF							5
#define SPI_SR_OVR							6
#define SPI_SR_BSY 							7
#define SPI_SR_FRE							8

// Bit position definition USART_SR

#define USART_SR_PE							0
#define USART_SR_FE							1
#define USART_SR_NF							2
#define USART_SR_ORE						3
#define USART_SR_IDLE 						4
#define USART_SR_RXNE 						5
#define USART_SR_TC 						6
#define USART_SR_TXE 						7
#define USART_SR_LBD						8
#define USART_SR_CTS						9

// Bit position definition USART_CR1

#define USART_CR1_SBK						0
#define USART_CR1_RWU						1
#define USART_CR1_RE						2
#define USART_CR1_TE						3
#define USART_CR1_IDLEIE					4
#define USART_CR1_RXNEIE 					5
#define USART_CR1_TCIE						6
#define USART_CR1_TXEIE 					7
#define USART_CR1_PEIE						8
#define USART_CR1_PS					    9
#define USART_CR1_PCE						10
#define USART_CR1_WAKE					    11
#define USART_CR1_M							12
#define USART_CR1_UE					    13
#define USART_CR1_OVER8						15

// Bit position definition USART_CR2

#define USART_CR2_ADD						0
#define USART_CR2_LBDL 						5
#define USART_CR2_LBDIE						6
#define USART_CR2_LBCL 						8
#define USART_CR2_CPHA 						9
#define USART_CR2_CPOL						10
#define USART_CR2_CLKEN 					11
#define USART_CR2_STOP						12
#define USART_CR2_LINEN						14

// Bit position definition USART_CR3

#define USART_CR3_EIE						0
#define USART_CR3_IREN 						1
#define USART_CR3_IRLP						2
#define USART_CR3_HDSEL						3
#define USART_CR3_NACK 						4
#define USART_CR3_SCEN						5
#define USART_CR3_DMAR 						6
#define USART_CR3_DMAT						7
#define USART_CR3_RTSE						8
#define USART_CR3_CTSE						9
#define USART_CR3_CTSIE 					10
#define USART_CR3_ONEBIT					11




#include "stm32f401RE_gpio.h"
#include "stm32f401RE_i2c_driver.h"
#include "stm32f401RE_spi_driver.h"

#endif /* STM32F401RE_H_ */
