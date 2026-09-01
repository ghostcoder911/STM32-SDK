/** 
 * stm32f401xe.h
 *Created on: Aug 19, 2026
 *@version 1.0
 */

//Header guards/include guards-prventssame header files being included multiple times

#ifndef STM32F401XE_H_
#define STM32F401XE_H_
#include <stdint.h>
#define _vo volatile

/** 
 * @brief Base addresses of Flash,ROM and SRAM memories
 */
#define FLASH_BASEADDR    0x08000000U               //Flash memory base address
#define ROM_BASEADDR      0x1FFF0000U               //ROM base address
#define SRAM_BASEADDR     0x20000000U               //SRAMbase address

/** 
 * @brief Peripheral bus addresses of AHBx and APBx buses
 */

#define PERIPHER_BASEADDR   0x40000000U
#define APB1_BASEADDR   PERIPHER_BASEADDR
#define APB2_BASEADDR       0x40010000U
#define AHB1_BASEADDR       0x40020000U
#define AHB2_BASEADDR       0x50000000U

/** 
 * @brief AHB1 Peripheral Base Addresses of GPIOx and RCC
 */

#define GPIOA_BASEADDR   (AHB1_BASEADDR + 0X0000)
#define GPIOB_BASEADDR   (AHB1_BASEADDR + 0X0400)
#define GPIOC_BASEADDR   (AHB1_BASEADDR + 0X0800)
#define GPIOD_BASEADDR   (AHB1_BASEADDR + 0X0C00)
#define GPIOE_BASEADDR   (AHB1_BASEADDR + 0X1000)
#define GPIOH_BASEADDR   (AHB1_BASEADDR + 0X1C00)

#define RCC_BASEADDR     (AHB1_BASEADDR + 0X3800)

/** 
 * @brief AHB2 Peripheral Base Addresses of USB
 */

#define USB_BASEADDR     AHB2_BASEADDR

/** 
 * @brief APB1 Peripheral Base Addresses of TIMx,SPIx,USARTx and I2Cx
 */

#define TIM2_BASEADDR   (APB1_BASEADDR + 0X0000)
#define TIM3_BASEADDR   (APB1_BASEADDR + 0X0400)
#define TIM4_BASEADDR   (APB1_BASEADDR + 0X0800)
#define TIM5_BASEADDR   (APB1_BASEADDR + 0X0C00)

#define SPI2_BASEADDR   (APB1_BASEADDR + 0X3800)
#define SPI3_BASEADDR   (APB1_BASEADDR + 0X3C00)

#define USART2_BASEADDR   (APB1_BASEADDR + 0X4400)

#define I2C1_BASEADDR   (APB1_BASEADDR + 0X5400)
#define I2C2_BASEADDR   (APB1_BASEADDR + 0X5800)
#define I2C3_BASEADDR   (APB1_BASEADDR + 0X5C00)

/** 
 * @brief APB2 Peripheral Base Addresses of TIMx,SPIx,USARTx and ADC
 */
#define TIM1_BASEADDR   (APB2_BASEADDR + 0X0000)

#define USART1_BASEADDR   (APB2_BASEADDR + 0X1000)
#define USART6_BASEADDR   (APB2_BASEADDR + 0X1400)
#define ADC_BASEADDR      (APB2_BASEADDR + 0X2000)

#define SPI1_BASEADDR      (APB2_BASEADDR + 0X3000)
#define SPI4_BASEADDR      (APB2_BASEADDR + 0X3400)

#define SYSCFG_BASEADDR      (APB2_BASEADDR + 0X3800)
#define EXTI_BASEADDR        (APB2_BASEADDR + 0X3C00)
#define TIM9_BASEADDR        (APB2_BASEADDR + 0X4000)
#define TIM10_BASEADDR       (APB2_BASEADDR + 0X4400)
#define TIM11_BASEADDR       (APB2_BASEADDR + 0X4800)

/** 
 * @brief GPIO peripheral register definition structure
 */

typedef struct
{
			_vo uint32_t MODER;                    /* Mode register,Offset: 0x00 */
			_vo uint32_t OTYPER;                   /* Output type register,Offset: 0x04 */
			_vo uint32_t OSPEEDR;                  /* Output speed register,Offset: 0x08*/
			_vo uint32_t PUPDR;                    /*Pull-up/pull-down register, Offset: 0x0C */
			_vo uint32_t IDR;                      /* Input data register,Offset: 0x10 */
			_vo uint32_t ODR;                      /* Output data register,Offset: 0x14 */
			_vo uint32_t BSRR;                     /* Bit set/reset register,Offset: 0x18 */
			_vo uint32_t LCKR;                     /* Configuration lock register,Offset: 0x1C */
			_vo uint32_t AFR[2];                   /* Alternate function registers,
													AFR[0] = AFRL (Offset: 0x20)
													AFR[1] = AFRH (Offset: 0x24) */
}GPIO_RegDef_t;

/** 
 * @brief RCC register definition structure-Enable/disable peripheral clock
 */


typedef struct
{


			_vo  uint32_t CR;             /*Clock control register,Offset: 0x00 */
			_vo  uint32_t PLLCFGR;        /*PLL configuration register,Offset: 0x04 */
			_vo  uint32_t CFGR;          /*Clock configuration register,Offset: 0x08 */
			_vo  uint32_t CIR;           /*Clock interrupt register,Offset: 0x0C */
			_vo  uint32_t AHB1RSTR;      /*AHB1 peripheral reset register,Offset: 0x10 */
			_vo  uint32_t AHB2RSTR;      /* AHB2 peripheral reset register,Offset: 0x14 */
			uint32_t Reserved0[2];
			_vo  uint32_t APB1RSTR;      /*APB1 peripheral reset register,Offset: 0x20 */
			_vo  uint32_t APB2RSTR;      /*APB2 peripheral reset register,Offset: 0x24 */
			uint32_t Reserved1[2];
			_vo  uint32_t AHB1ENR;       /*AHB1 clock enable register,Offset: 0x30 */
			_vo  uint32_t AHB2ENR;       /*AHB2 clock enable register,Offset: 0x34 */
			uint32_t Reserved2[2];
			_vo  uint32_t APB1ENR;       /*APB1 clock enable register,ffset: 0x40 */
			_vo  uint32_t APB2ENR;       /*APB2 clock enable register,ffset: 0x44 */
			uint32_t Reserved3[2];
			_vo  uint32_t AHB1LPENR;     /*AHB1 clock enabled in low power mode register,offset: 0x50 */
			_vo  uint32_t AHB2LPENR;     /*AHB2 clock enabled in low power mode register,offset: 0x54 */
			uint32_t Reserved4[2];
			_vo  uint32_t APB1LPENR;     /*APB1 clock enabled in low power mode register,offset: 0x60 */
			_vo  uint32_t APB2LPENR;     /*APB2 clock enabled in low power mode register,offset: 0x64 */
			uint32_t Reserved5[2];
			_vo  uint32_t BDCR;          /*Backup domain control register,offset: 0x70 */
			_vo  uint32_t CSR;           /*Clock control  and status register,offset: 0x74 */
			uint32_t Reserved6[2];
			_vo  uint32_t SSCGR;         /*Spread spectrum Clock control generation register,offset: 0x80 */
			_vo  uint32_t PLLI2SCFGR;    /*PLLI2S configuration register,offset: 0x80 */
			_vo  uint32_t DCKCF;         /*Dedicated Clocks Configuration Register:0x8C*/

} RCC_RegDef_t;


/** 
 * @brief SPI Register Definition Structure
 */
typedef struct
{
			_vo   uint32_t   CR1;      /*Control register 1,Offset: 0x00 */
			_vo   uint32_t   CR2;      /*Control register 2,Offset: 0x04 */
			_vo   uint32_t   SR;       /* Status register, Offset: 0x08 */
			_vo   uint32_t   DR;       /* Data register, Offset: 0x0C */
			_vo   uint32_t   CRCPR1;   /*CRC polynomial register,Offset: 0x10*/
			_vo   uint32_t   RXCRCR;   /*RX CRC register,Offset: 0x14 */
			_vo   uint32_t   TXCRCR;   /*TX CRC register,Offset: 0x18 */
			_vo   uint32_t   I2SCFGR;  /*I2S configuration,Offset: 0x1C */
			_vo   uint32_t   I2SPR;    /*I2S Prescaler,Offset: 0x20 */

} SPI_RegDef_t;

/** 
 * @brief I2C Register Definition Structure
 */
typedef struct
{
		_vo   uint32_t   CR1;       /* Control register 1,Offset: 0x00 */
		_vo   uint32_t   CR2;       /* Control register 2,Offset: 0x04 */
		_vo   uint32_t   OAR1;      /*Own address register 1,Offset: 0x08 */
		_vo   uint32_t   OAR2;      /*Own address register 2,Offset: 0x0C */
		_vo   uint32_t   DR;        /* Data register,Offset: 0x10 */
		_vo   uint32_t   SR1;       /* Status register1,Offset: 0x14 */
		_vo   uint32_t   SR2;       /* Status register2,Offset: 0x18 */
		_vo   uint32_t   CCR;       /*  Clock Control register,Offset: 0x1C */
		_vo   uint32_t   TRISE;     /*TRISE register, Offset: 0x20 */
		_vo   uint32_t   FLTR;      /*FLTR register,Offset: 0x24 */
} I2C_RegDef_t;

/** 
 * @brief USART Register Definition Structure
 */
typedef struct
{
		_vo uint32_t SR;       /*Status register,Offset: 0x00 */
		_vo uint32_t DR;       /*Data register,Offset: 0x04 */
		_vo uint32_t BRR;      /* Baud rate register,Offset: 0x08 */
		_vo uint32_t CR1;      /*Control register 1,Offset: 0x0C */
		_vo uint32_t CR2;      /*Control register 2,Offset: 0x10 */
		_vo uint32_t CR3;      /*Control register 3,Offset: 0x14 */
		_vo uint32_t GTPR;     /*Guard time & prescaler reg,Offset: 0x18 */

}  USART_RegDef_t;

/** 
 * @brief EXTI register definition structure
 */
typedef struct
{
	_vo uint32_t EXTI_IMR;                   /*Interrupt mask register,offset: 0x00 */
	_vo uint32_t EXTI_EMR;                   /*Event mask register,offset: 0x04 */
	_vo uint32_t EXTI_RTSR;                   /*Rising trigger selection register,offset: 0x00 */
	_vo uint32_t EXTI_FTSR;                   /*Falling trigger selection register,offset: 0x00 */
	_vo uint32_t MEEXTI_SWIER;                /*Software interrupt event register,offset: 0x00 */
	_vo uint32_t EXTI_PR;                     /*Pending register,offset: 0x00 */

} EXTI_RegDef_t;

/** 
 * @brief SYSCFG Register Definition Structure-Handle interrupts
 */
typedef struct
{
		_vo uint32_t MEMRMP;                   /*!< SYSCFG memory remap regiser,offset: 0x00 */
		_vo uint32_t PMC;                      /*!< SYSCFG peripheral mode configuration registeer,offset: 0x04 */
		_vo uint32_t EXTICR[4];                /*!< SYSCFG external interrupt configuration,offset: 0x08-0x14 */
		uint32_t     RESERVED1[2];             /*!< Reserved,offset: 0x18-0x1C */
		_vo uint32_t CMPCR;                    /*!< SYSCFG compensation cell control register, offset: 0x20 */
		uint32_t      RESERVED2[2];             /*!< Reserved,offset: 0x24-0x28 */
		_vo uint32_t CFGR;                     /*!< SYSCFG configuration register,offset: 0x2C */

} SYSCFG_RegDef_t;

/** 
 * @brief Peripheral Pointer Definitions
 * @brief typecasting the base address to our structure pointer
 */

/***************Peripheral structure pointer typecasting to base address of each peripheral***************/

#define GPIOA   ((GPIO_RegDef_t*) GPIOA_BASEADDR)
#define GPIOB   ((GPIO_RegDef_t*) GPIOB_BASEADDR)
#define GPIOC   ((GPIO_RegDef_t*) GPIOC_BASEADDR)
#define GPIOD   ((GPIO_RegDef_t*) GPIOD_BASEADDR)
#define GPIOE   ((GPIO_RegDef_t*) GPIOE_BASEADDR)
#define GPIOH   ((GPIO_RegDef_t*) GPIOH_BASEADDR)

/*!< RCC */
#define RCC   ((RCC_RegDef_t*) RCC_BASEADDR)

/*!< SPI */
#define SPI1   ((SPI_RegDef_t*)  SPI1_BASEADDR)
#define SPI2   ((SPI_RegDef_t*)  SPI2_BASEADDR)
#define SPI3  ((SPI_RegDef_t*)  SPI3_BASEADDR)
#define SPI4  ((SPI_RegDef_t*)  SPI4_BASEADDR)

/*!< I2C */
#define I2C1   ((I2C_RegDef_t*)  I2C1_BASEADDR)
#define I2C2   ((I2C_RegDef_t*)  I2C2_BASEADDR)
#define I2C3   ((I2C_RegDef_t*)  I2C3_BASEADDR)

/*!< USART */
#define USART1   ((USART_RegDef_t*)  USART1_BASEADDR)
#define USART2   ((USART_RegDef_t*) USART2_BASEADDR)
#define USART6   ((USART_RegDef_t*) USART6_BASEADDR)

/*!< EXTI */
#define EXTI          ((EXTI_RegDef_t*)EXTI_BASEADDR)

/*!< SYSCONFIG */
#define SYSCFG          ((SYSCFG_RegDef_t*)SYSCFG_BASEADDR)


/*************************CLOCK ENABLE MACROS*******************************************/

 /*!< GPIO CLOCK ENABLE*/
#define GPIOA_PCLK_EN()  (RCC->AHB1ENR |= (1<<0))
#define GPIOB_PCLK_EN()  (RCC->AHB1ENR |= (1<<1))
#define GPIOC_PCLK_EN()  (RCC->AHB1ENR |= (1<<2))
#define GPIOD_PCLK_EN()  (RCC->AHB1ENR |= (1<<3))
#define GPIOE_PCLK_EN()  (RCC->AHB1ENR |= (1<<4))
#define GPIOH_PCLK_EN()  (RCC->AHB1ENR |= (1<<7))

/*!< SPI CLOCK ENABLE */
#define SPI1_PCLK_EN()   (RCC->APB2ENR |= (1<<12))
#define SPI2_PCLK_EN()   (RCC->APB1ENR |= (1<<14))
#define SPI3_PCLK_EN()   (RCC->APB1ENR |= (1<<15))
#define SPI4_PCLK_EN()   (RCC->APB2ENR |= (1<<13))


/*!< I2C CLOCK ENABLE */

#define I2C1_PCLK_EN()   (RCC->APB1ENR |= (1<<21))
#define I2C2_PCLK_EN()   (RCC->APB1ENR |= (1<<22))
#define I2C3_PCLK_EN()   (RCC->APB1ENR |= (1<<23))


/*!< USART CLOCK ENABLE */

#define USART1_PCLK_EN()   (RCC->APB2ENR |= (1<<4))
#define USART2_PCLK_EN()   (RCC->APB1ENR |= (1<<17))
#define USART6_PCLK_EN()   (RCC->APB2ENR |= (1<<5))


/*!< SYSCONFIG CLOCK ENABLE */

#define SYSCFG_PCLK_EN()   (RCC->APB2ENR |= (1<<14))

/********************************Clock Disable Macros***************************************/

/*!< GPIO Clock Disable */
#define GPIOA_PCLK_DI()    (RCC->AHB1ENR &= ~(1 << 0))
#define GPIOB_PCLK_DI()    (RCC->AHB1ENR &= ~(1 << 1))
#define GPIOC_PCLK_DI()    (RCC->AHB1ENR &= ~(1 << 2))
#define GPIOD_PCLK_DI()    (RCC->AHB1ENR &= ~(1 << 3))
#define GPIOE_PCLK_DI()    (RCC->AHB1ENR &= ~(1 << 4))
#define GPIOH_PCLK_DI()    (RCC->AHB1ENR &= ~(1 << 7))


/*!< SPI Clock Disable */
#define SPI1_PCLK_DI()     (RCC->APB2ENR &= ~(1 << 12))
#define SPI2_PCLK_DI()     (RCC->APB1ENR &= ~(1 << 14))
#define SPI3_PCLK_DI()     (RCC->APB1ENR &= ~(1 << 15))
#define SPI4_PCLK_DI()     (RCC->APB2ENR &= ~ (1 << 13))

/*!< I2C Clock Disable */
#define I2C1_PCLK_DI()     (RCC->APB1ENR &= ~ (1 << 21))
#define I2C2_PCLK_DI()     (RCC->APB1ENR &= ~ (1 << 22))
#define I2C3_PCLK_DI()     (RCC->APB1ENR &= ~ (1 << 23))

/*!< USART Clock Disable */
#define USART1_PCLK_DI()   (RCC->APB2ENR &= ~ (1 << 4))
#define USART2_PCLK_DI()   (RCC->APB1ENR &= ~ (1 << 17))
#define USART6_PCLK_DI()   (RCC->APB2ENR &= ~(1 << 5))

/*!< Clock Disable Macros for SYSCFG*/
#define SYSCFG_PCLK_DI()    (RCC->APB2ENR &= ~(1 << 14))

/*********************************** Peripheral Reset Macros**********************************/

/*!< GPIO Reset - using do-while(0) for safe macro usage */
/*!< Macros to reset GPIOx peripherals*/
#define GPIOA_REG_RESET()                   do{ (RCC->AHB1RSTR |= (1 << 0)); (RCC->AHB1RSTR &= ~(1 << 0)); }while(0)
#define GPIOB_REG_RESET()                   do{ (RCC->AHB1RSTR |= (1 << 1)); (RCC->AHB1RSTR &= ~(1 << 1)); }while(0)
#define GPIOC_REG_RESET()                   do{ (RCC->AHB1RSTR |= (1 << 2)); (RCC->AHB1RSTR &= ~(1 << 2)); }while(0)
#define GPIOD_REG_RESET()                   do{ (RCC->AHB1RSTR |= (1 << 3)); (RCC->AHB1RSTR &= ~(1 << 3)); }while(0)
#define GPIOE_REG_RESET()                   do{ (RCC->AHB1RSTR |= (1 << 4)); (RCC->AHB1RSTR &= ~(1 << 4)); }while(0)
#define GPIOH_REG_RESET()                   do{ (RCC->AHB1RSTR |= (1 << 7)); (RCC->AHB1RSTR &= ~(1 << 7)); }while(0)

/*!< Macros to reset I2C peripherals*/
#define I2C1_REG_RESET()                    do{ (RCC->APB1RSTR |= (1 << 21)); (RCC->APB1RSTR &= ~(1 << 21)); }while(0)
#define I2C2_REG_RESET()                    do{ (RCC->APB1RSTR |= (1 << 22)); (RCC->APB1RSTR &= ~(1 << 22)); }while(0)
#define I2C3_REG_RESET()                    do{ (RCC->APB1RSTR |= (1 << 23)); (RCC->APB1RSTR &= ~(1 << 23)); }while(0)

/*!< Macros to reset SPI peripherals*/
#define SPI1_REG_RESET()                    do{ (RCC->APB2RSTR |= (1 << 12)); (RCC->APB2RSTR &= ~(1 << 12)); }while(0)
#define SPI2_REG_RESET()                    do{ (RCC->APB1RSTR |= (1 << 14)); (RCC->APB1RSTR &= ~(1 << 14)); }while(0)
#define SPI3_REG_RESET()                    do{ (RCC->APB1RSTR |= (1 << 15)); (RCC->APB1RSTR &= ~(1 << 15)); }while(0)
#define SPI4_REG_RESET()                    do{ (RCC->APB2RSTR |= (1 << 13)); (RCC->APB2RSTR &= ~(1 << 13)); }while(0)

/*!< Macros to reset USART peripherals*/
#define USART1_REG_RESET()                  do{ (RCC->APB2RSTR |= (1 << 4)); (RCC->APB2RSTR &= ~(1 << 4)); }while(0)
#define USART2_REG_RESET()                  do{ (RCC->APB1RSTR |= (1 << 17)); (RCC->APB1RSTR &= ~(1 << 17)); }while(0)
#define USART6_REG_RESET()                  do{ (RCC->APB2RSTR |= (1 << 5)); (RCC->APB2RSTR &= ~(1 << 5)); }while(0)

/********************************** Generic macros *****************************************************/
#define ENABLE        1
#define DISABLE       0
#define SET           ENABLE
#define RESET         DISABLE
#define GPIO_PIN_SET  SET
#define GPIO_PIN_RESET RESET
#define FLAG_RESET     RESET
#define FLAG_SET       SET



/*************************************** Bit Position Definitions of SPI **********************************/
/**
 * @brief Bit position definitions of SPI_CR1
 */
#define SPI_CR1_CPHA                        0
#define SPI_CR1_CPOL                        1
#define SPI_CR1_MSTR                        2
#define SPI_CR1_BR                          3
#define SPI_CR1_SPE                         6
#define SPI_CR1_LSBFIRST                    7
#define SPI_CR1_SSI                         8
#define SPI_CR1_SSM                         9
#define SPI_CR1_RXONLY                      10
#define SPI_CR1_DFF                         11
#define SPI_CR1_CRCNEXT                     12
#define SPI_CR1_CRCEN                       13
#define SPI_CR1_BIDIOE                      14
#define SPI_CR1_BIDIMODE                    15

/**
 * @brief Bit position definitions of SPI_CR2
 */
#define SPI_CR2_RXDMAEN                     0
#define SPI_CR2_TXDMAEN                     1
#define SPI_CR2_SSOE                        2
#define SPI_CR2_FRF                         4
#define SPI_CR2_ERRIE                       5
#define SPI_CR2_RXNEIE                      6
#define SPI_CR2_TXEIE                       7
/**
 * @brief Bit position definitions of SPI_SR
 */
#define SPI_SR_RXNE                         0
#define SPI_SR_TXE                          1
#define SPI_SR_CHSIDE                       2
#define SPI_SR_UDR                          3
#define SPI_SR_CRCERR                       4
#define SPI_SR_MODF                         5
#define SPI_SR_OVR                          6
#define SPI_SR_BSY                          7
#define SPI_SR_FRE                          8

/******************************* Bit Position Definitions of USART **********************************/
/*
 * @brief position definitions USART_CR1
 */
#define USART_CR1_SBK                       0
#define USART_CR1_RWU                       1
#define USART_CR1_RE                        2
#define USART_CR1_TE                        3
#define USART_CR1_IDLEIE                    4
#define USART_CR1_RXNEIE                    5
#define USART_CR1_TCIE                      6
#define USART_CR1_TXEIE                     7
#define USART_CR1_PEIE                      8
#define USART_CR1_PS                        9
#define USART_CR1_PCE                       10
#define USART_CR1_WAKE                      11
#define USART_CR1_M                         12
#define USART_CR1_UE                        13
#define USART_CR1_OVER8                     15

/*
 * @brief Bit position definitions USART_CR2
 */
#define USART_CR2_ADD                       0
#define USART_CR2_LBDL                      5
#define USART_CR2_LBDIE                     6
#define USART_CR2_LBCL                      8
#define USART_CR2_CPHA                      9
#define USART_CR2_CPOL                      10
#define USART_CR2_CLKEN                     11
#define USART_CR2_STOP                      12
#define USART_CR2_LINEN                     14

/*
 * @brief Bit position definitions USART_CR3
 */
#define USART_CR3_EIE                       0
#define USART_CR3_IREN                      1
#define USART_CR3_IRLP                      2
#define USART_CR3_HDSEL                     3
#define USART_CR3_NACK                      4
#define USART_CR3_SCEN                      5
#define USART_CR3_DMAR                      6
#define USART_CR3_DMAT                      7
#define USART_CR3_RTSE                      8
#define USART_CR3_CTSE                      9
#define USART_CR3_CTSIE                     10
#define USART_CR3_ONEBIT                    11

/*
 * @brief Bit position definitions USART_SR
 */
#define USART_SR_PE                         0
#define USART_SR_FE                         1
#define USART_SR_NE                         2
#define USART_SR_ORE                        3
#define USART_SR_IDLE                       4
#define USART_SR_RXNE                       5
#define USART_SR_TC                         6
#define USART_SR_TXE                        7
#define USART_SR_LBD                        8
#define USART_SR_CTS                        9


/******************************Bit Position Definitions of I2C**********************************/

/**
 * @brief Bit position definitions I2C_CR1
 */

#define I2C_CR1_PE                          0
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

/*
 * @brief Bit position definitions I2C_CR2
 */
#define I2C_CR2_FREQ                        0
#define I2C_CR2_ITERREN                     8
#define I2C_CR2_ITEVTEN                     9
#define I2C_CR2_ITBUFEN                     10
#define I2C_CR2_DMAEN                       11
#define I2C_CR2_LAST                        12

/*
 * @brief Bit position definitions I2C_OAR1
 */
#define I2C_OAR1_ADD0                       0
#define I2C_OAR1_ADD71                      1
#define I2C_OAR1_ADD98                      8
#define I2C_OAR1_ADDMODE                    15

/*
 * @brief Bit position definitions I2C_SR1
 */
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

/*
 * @brief Bit position definitions I2C_SR2
 */
#define I2C_SR2_MSL                         0
#define I2C_SR2_BUSY                        1
#define I2C_SR2_TRA                         2
#define I2C_SR2_GENCALL                     4
#define I2C_SR2_SMBDEFAULT                  5
#define I2C_SR2_SMBHOST                     6
#define I2C_SR2_DUALF                       7

/*
 * @brief Bit position definitions I2C_CCR
 */
#define I2C_CCR_CCR                         0
#define I2C_CCR_DUTY                        14
#define I2C_CCR_FS                          15

/*************************************Bit position definitions of RCC peripheral*****************************/

/*
 * @brief Bit position definitions RCC_CR
 */
#define RCC_CR_HSION                        0
#define RCC_CR_HSIRDY                       1
#define RCC_CR_HSITRIM                      3
#define RCC_CR_HSICAL                       8
#define RCC_CR_HSEON                        16
#define RCC_CR_HSERDY                       17
#define RCC_CR_HSEBYP                       18
#define RCC_CR_CSSON                        19
#define RCC_CR_PLLON                        24
#define RCC_CR_PLLRDY                       25
#define RCC_CR_PLLI2SON                     26
#define RCC_CR_PLLI2SRDY                    27
#define RCC_CR_PLLSAION                     28
#define RCC_CR_PLLSAIRDY                    29

/*
 * @brief Bit position definitions RCC_CFGR
 */
#define RCC_CFGR_SW                         0
#define RCC_CFGR_SWS                        2
#define RCC_CFGR_HPRE                       4
#define RCC_CFGR_PPRE1                      10
#define RCC_CFGR_PPRE2                      13
#define RCC_CFGR_RTCPRE                     16
#define RCC_CFGR_MCO1                       21
#define RCC_CFGR_MCO1PRE                    24
#define RCC_CFGR_MCO2PRE                    27
#define RCC_CFGR_MCO2                       30



#include "stm32f401xe_gpio.h"
#include "stm32f401xe_i2c.h"
#include "stm32f401xe_usart.h"
#include "stm32f401xe_rcc.h"


#endif /* STM32F401XE_H_ */
