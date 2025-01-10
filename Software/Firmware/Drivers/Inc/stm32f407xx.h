#ifndef INC_STM32F407XX_H_
#define INC_STM32F407XX_H_

#include <stdint.h>
#include <string.h>
#include <stddef.h>

#define __IO volatile

/*
 * Exported Macro
 */
#define SET_BIT(REG, BIT)           ((REG) |= (BIT))
#define CLEAR_BIT(REG, BIT)         ((REG) &= ~(BIT))
#define READ_BIT(REG, BIT)          ((REG) & (BIT))
#define UNUSED(x)                   (void)x

/*
 * Exported Types
 */
typedef enum
{
	DISABLE = 0x0U,
	ENABLE = !DISABLE

}FunctionalState_t;

/*
 * Cortex-M4 Processor Peripherals
 */
#define NVIC_ISER0 					((uint32_t*)(0xE000E100UL))

/*
 * Interrupt Number Definition
 */
typedef enum
{
  EXTI0_IRQn = 6,      				/*!< EXTI Line0 Interrupt */
  EXTI1_IRQn = 7,      				/*!< EXTI Line1 Interrupt */
  EXTI2_IRQn = 8,      				/*!< EXTI Line2 Interrupt */
  EXTI3_IRQn = 9,      				/*!< EXTI Line3 Interrupt */
  EXTI4_IRQn = 10,     				/*!< EXTI Line4 Interrupt */
  SPI1_IRQn = 35,                   /*!< SPI1 Interrupt       */
  USART2_IRQn = 38,                 /*!< EXTI2 Interrupt      */

}IRQn_TypeDef_t;

/*
 * Memory Base Address
 */
#define FLASH_BASE_ADDR             (0x08000000UL)  /* Flash Base Address (up to 1MB) */
#define SRAM1_BASE_ADDR				(0x20000000UL)  /* SRAM1 Base Address 112KB 	  */
#define SRAM2_BASE_ADDR			    (0x2001C000UL)  /* SRAM1 Base Address 16KB        */

/*
 * Peripheral Base Address
 */
#define PERIP_BASE_ADDR				(0x40000000UL)  /* Base Address for All peripherals */

#define APB1_BASE_ADDR              PERIP_BASE_ADDR                   /* APB1 Bus Domain Base Address */
#define APB2_BASE_ADDR              (PERIP_BASE_ADDR + 0x10000UL)     /* APB2 Bus Domain Base Address */
#define AHB1_BASE_ADDR              (PERIP_BASE_ADDR + 0x20000UL)     /* AHB1 Bus Domain Base Address */
#define AHB2_BASE_ADDR              (PERIP_BASE_ADDR + 0x10000000UL)  /* AHB2 Bus Domain Base Address */

/*
 * APB1 Peripheral Base Address
 */
#define TIM2_BASE_ADDR				(APB1_BASE_ADDR + 0x0000UL)
#define TIM3_BASE_ADDR				(APB1_BASE_ADDR + 0x0400UL)
#define TIM4_BASE_ADDR				(APB1_BASE_ADDR + 0x0800UL)
#define TIM5_BASE_ADDR				(APB1_BASE_ADDR + 0x0C00UL)
#define TIM6_BASE_ADDR				(APB1_BASE_ADDR + 0x1000UL)
#define TIM7_BASE_ADDR				(APB1_BASE_ADDR + 0x1400UL)
#define TIM12_BASE_ADDR				(APB1_BASE_ADDR + 0x1800UL)
#define TIM13_BASE_ADDR			    (APB1_BASE_ADDR + 0x1C00UL)
#define TIM14_BASE_ADDR			    (APB1_BASE_ADDR + 0x2000UL)
#define RTC_BASE_ADDR          		(APB1_BASE_ADDR + 0x2800UL)
#define WWDG_BASE_ADDR          	(APB1_BASE_ADDR + 0x2C00UL)
#define IWDG_BASE_ADDR         		(APB1_BASE_ADDR + 0x3000UL)
#define I2S2ext_BASE_ADDR        	(APB1_BASE_ADDR + 0x3400UL)
#define SPI2_BASE_ADDR              (APB1_BASE_ADDR + 0x3800UL)
#define SPI3_BASE_ADDR              (APB1_BASE_ADDR + 0x3C00UL)
#define I2S3ext_BASE_ADDR           (APB1_BASE_ADDR + 0x4000UL)
#define USART2_BASE_ADDR            (APB1_BASE_ADDR + 0x4400UL)
#define USART3_BASE_ADDR            (APB1_BASE_ADDR + 0x4800UL)
#define UART4_BASE_ADDR             (APB1_BASE_ADDR + 0x4C00UL)
#define UART5_BASE_ADDR             (APB1_BASE_ADDR + 0x5000UL)
#define I2C1_BASE_ADDR              (APB1_BASE_ADDR + 0x5400UL)
#define I2C2_BASE_ADDR              (APB1_BASE_ADDR + 0x5800UL)
#define I2C3_BASE_ADDR              (APB1_BASE_ADDR + 0x5C00UL)
#define CAN1_BASE_ADDR              (APB1_BASE_ADDR + 0x6400UL)
#define CAN2_BASE_ADDR              (APB1_BASE_ADDR + 0x6800UL)
#define PWR_BASE_ADDR               (APB1_BASE_ADDR + 0x7000UL)
#define DAC_BASE_ADDR               (APB1_BASE_ADDR + 0x7400UL)

/*
 * APB2 Peripherals Base Addresses
 */
#define TIM1_BASE_ADDR              (APB2_BASE_ADDR + 0x0000UL)
#define TIM8_BASE_ADDR              (APB2_BASE_ADDR + 0x0400UL)
#define USART1_BASE_ADDR            (APB2_BASE_ADDR + 0x1000UL)
#define USART6_BASE_ADDR            (APB2_BASE_ADDR + 0x1400UL)
#define SDIO_BASE_ADDR              (APB2_BASE_ADDR + 0x2C00UL)
#define SPI1_BASE_ADDR              (APB2_BASE_ADDR + 0x3000UL)
#define SPI4_BASE_ADDR              (APB2_BASE_ADDR + 0x3400UL)
#define SYSCFG_BASE_ADDR            (APB2_BASE_ADDR + 0x3800UL)
#define EXTI_BASE_ADDR              (APB2_BASE_ADDR + 0x3C00UL)
#define TIM9_BASE_ADDR              (APB2_BASE_ADDR + 0x4000UL)
#define TIM10_BASE_ADDR             (APB2_BASE_ADDR + 0x4400UL)
#define TIM11_BASE_ADDR             (APB2_BASE_ADDR + 0x4800UL)

/*
 * AHB1 Peripherals Base Addresses
 */
#define GPIOA_BASE_ADDR             (AHB1_BASE_ADDR + 0x0000UL)
#define GPIOB_BASE_ADDR             (AHB1_BASE_ADDR + 0x0400UL)
#define GPIOC_BASE_ADDR             (AHB1_BASE_ADDR + 0x0800UL)
#define GPIOD_BASE_ADDR             (AHB1_BASE_ADDR + 0x0C00UL)
#define GPIOE_BASE_ADDR             (AHB1_BASE_ADDR + 0x1000UL)
#define RCC_BASE_ADDR               (AHB1_BASE_ADDR + 0x3800UL)

/*
 * Peripheral Structure Definitions
 */

/*
 * General-purpose I/Os (GPIO)
 */
typedef struct
{
	__IO uint32_t MODER;            /*!< GPIO port mode register 			    Address offset: 0x00      */
	__IO uint32_t OTYPER;		    /*!< GPIO port output type register 	    Address offset: 0x04      */
	__IO uint32_t OSPEEDER;		    /*!< GPIO port output speed register 	    Address offset: 0x08      */
	__IO uint32_t PUPDR;		    /*!< GPIO port pull-up/pull-down register   Address offset: 0x0C      */
	__IO uint32_t IDR;			    /*!< GPIO port input data register	        Address offset: 0x10      */
	__IO uint32_t ODR;			    /*!< GPIO port output data register 	    Address offset: 0x14      */
	__IO uint32_t BSRR;			    /*!< GPIO port bit set/reset register 	    Address offset: 0x18      */
	__IO uint32_t LCKR;			    /*!< GPIO port configuration lock register 	Address offset: 0x1C 	  */
	__IO uint32_t AFR[2];           /*!< GPIO alternate function low register  	Address offset: 0x20-0x24 */

}GPIO_TypeDef_t;


/*
 * Reset and clock control (RCC)
 */
typedef struct
{
	  __IO uint32_t CR;             /*!< RCC clock control register                                   Address offset: 0x00     */
	  __IO uint32_t PLLCFGR;        /*!< RCC PLL configuration register                               Address offset: 0x04     */
	  __IO uint32_t CFGR;           /*!< RCC clock configuration register                             Address offset: 0x08     */
	  __IO uint32_t CIR;            /*!< RCC clock interrupt register                                 Address offset: 0x0C      */
	  __IO uint32_t AHB1RSTR;       /*!< RCC AHB1 peripheral reset register                           Address offset: 0x10      */
	  __IO uint32_t AHB2RSTR;       /*!< RCC AHB2 peripheral reset register                           Address offset: 0x14      */
	  __IO uint32_t AHB3RSTR;       /*!< RCC AHB3 peripheral reset register                           Address offset: 0x18      */
	  uint32_t      RESERVED0;      /*!< Reserved                                                     Address offset: 0x1C      */
	  __IO uint32_t APB1RSTR;       /*!< RCC APB1 peripheral reset register                           Address offset: 0x20      */
	  __IO uint32_t APB2RSTR;       /*!< RCC APB2 peripheral reset register                           Address offset: 0x24      */
	  uint32_t      RESERVED1[2];   /*!< Reserved                                                     Address offset: 0x28-0x2C */
	  __IO uint32_t AHB1ENR;        /*!< RCC AHB1 peripheral clock register                           Address offset: 0x30      */
	  __IO uint32_t AHB2ENR;        /*!< RCC AHB2 peripheral clock register                           Address offset: 0x34      */
	  __IO uint32_t AHB3ENR;        /*!< RCC AHB3 peripheral clock register                           Address offset: 0x38      */
	  uint32_t      RESERVED2;      /*!< Reserved                                                     Address offset: 0x3C      */
	  __IO uint32_t APB1ENR;        /*!< RCC APB1 peripheral clock enable register                    Address offset: 0x40      */
	  __IO uint32_t APB2ENR;        /*!< RCC APB2 peripheral clock enable register                    Address offset: 0x44      */
	  uint32_t      RESERVED3[2];   /*!< Reserved                                                     Address offset: 0x48-0x4C */
	  __IO uint32_t AHB1LPENR;      /*!< RCC AHB1 peripheral clock enable in low power mode register  Address offset: 0x50      */
	  __IO uint32_t AHB2LPENR;      /*!< RCC AHB2 peripheral clock enable in low power mode register  Address offset: 0x54      */
	  __IO uint32_t AHB3LPENR;      /*!< RCC AHB3 peripheral clock enable in low power mode register  Address offset: 0x58      */
	  uint32_t      RESERVED4;      /*!< Reserved                                                     Address offset: 0x5C      */
	  __IO uint32_t APB1LPENR;      /*!< RCC APB1 peripheral clock enable in low power mode register  Address offset: 0x60      */
	  __IO uint32_t APB2LPENR;      /*!< RCC APB2 peripheral clock enable in low power mode register  Address offset: 0x64      */
	  uint32_t      RESERVED5[2];   /*!< Reserved                                                     Address offset: 0x68-0x6C */
	  __IO uint32_t BDCR;           /*!< RCC Backup domain control register                           Address offset: 0x70      */
	  __IO uint32_t CSR;            /*!< RCC clock control & status register                          Address offset: 0x74      */
	  uint32_t      RESERVED6[2];   /*!< Reserved                                                     Address offset: 0x78-0x7C */
	  __IO uint32_t SSCGR;          /*!< RCC spread spectrum clock generation register                Address offset: 0x80      */
	  __IO uint32_t PLLI2SCFGR;     /*!< RCC PLLI2S configuration register                            Address offset: 0x84      */

}RCC_TypeDef_t;

/*
 * System Configuration Controller (SYSCFG)
 */
typedef struct
{
	__IO uint32_t MEMRMP;          /*!< SYSCFG memory remap register 			          Address offset: 0x00      */
	__IO uint32_t PMC;		       /*!< SYSCFG peripheral mode configuration register 	  Address offset: 0x04      */
	__IO uint32_t EXTI_CR[4];	   /*!< SYSCFG external interrupt configuration register  Address offset: 0x08-0x14 */
	uint32_t RESERVED[2];		   /*!< Reserved                     	                  Address offset: 0x18-0x1C */
	__IO uint32_t CMPCR;		   /*!< Compensation cell control register  	          Address offset: 0x20      */

}SYSCFG_TypeDef_t;

/*
 * External interrupt (EXTI)
 */
typedef struct
{
	__IO uint32_t IMR;             /*!< Interrupt mask register 			Address offset: 0x00 */
	__IO uint32_t EMR;		       /*!< Event mask register 	            Address offset: 0x04 */
	__IO uint32_t RTSR;	           /*!< Rising trigger selection register   Address offset: 0x08 */
	__IO uint32_t FTSR;	           /*!< Falling trigger selection register  Address offset: 0x0C */
	__IO uint32_t SWIER;	       /*!< Software interrupt event register   Address offset: 0x10 */
	__IO uint32_t PR;	           /*!< Pending register                    Address offset: 0x14 */

}EXTI_TypeDef_t;

/*
 * Serial peripheral interface (SPI)
 */
typedef struct
{
	__IO uint32_t CR1;             /*!< SPI control register 1 	 	  	Address offset: 0x00 */
	__IO uint32_t CR2;		       /*!< SPI control register 2 	      	Address offset: 0x04 */
	__IO uint32_t SR;	           /*!< SPI status register   		  	Address offset: 0x08 */
	__IO uint32_t DR;	           /*!< SPI data register   		  	Address offset: 0x0C */
	__IO uint32_t CRCPR;	       /*!< SPI CRC polynomial register		Address offset: 0x10 */
	__IO uint32_t RXCRCR;	       /*!< SPI RX CRC register   		  	Address offset: 0x14 */
	__IO uint32_t TXCRCR;	       /*!< SPI TX CRC register		      	Address offset: 0x18 */

}SPI_TypeDef_t;

/*
 * Universal synchronous asynchronous receiver transmitter (USART)
 */
typedef struct
{
	__IO uint32_t SR;              /*!< Status register 	 				Address offset: 0x00 */
	__IO uint32_t DR;		       /*!< Data  register 	     				Address offset: 0x04 */
	__IO uint32_t BRR;	           /*!< Baud rate register   				Address offset: 0x08 */
	__IO uint32_t CR1;	           /*!< Control register 1   				Address offset: 0x0C */
	__IO uint32_t CR2;	           /*!< Control register 2   				Address offset: 0x10 */
	__IO uint32_t CR3;	       	   /*!< Control register 3   				Address offset: 0x14 */
	__IO uint32_t GTPR;	           /*!< Guard time and prescaler register   Address offset: 0x18 */

}USART_TypeDef_t;

/*
 * Inter-integrated circuit (I2C)
 */
typedef struct
{
	__IO uint32_t CR1;             /*!< Control register 1      Address offset: 0x00 */
	__IO uint32_t CR2;		       /*!< Control register 2 	     Address offset: 0x04 */
	__IO uint32_t OAR1;	           /*!< Own address register 1   Address offset: 0x08 */
	__IO uint32_t OAR2;	           /*!< Own address register 2   Address offset: 0x0C */
	__IO uint32_t DR;	           /*!< Data register   		 Address offset: 0x10 */
	__IO uint32_t SR1;	       	   /*!< Status register 1   	 Address offset: 0x14 */
	__IO uint32_t SR2;	           /*!< Status register 2        Address offset: 0x18 */
	__IO uint32_t CCR;	           /*!< Clock control register   Address offset: 0x1C */
	__IO uint32_t TRISE;	       /*!< TRISE register           Address offset: 0x20 */
	__IO uint32_t FLTR;	           /*!< FLTR register            Address offset: 0x24 */

}I2C_TypeDef_t;

/*
 * Base Address Definitions Peripheral
 */
#define GPIOA                       ((GPIO_TypeDef_t *)(GPIOA_BASE_ADDR))
#define GPIOB                       ((GPIO_TypeDef_t *)(GPIOB_BASE_ADDR))
#define GPIOC                       ((GPIO_TypeDef_t *)(GPIOC_BASE_ADDR))
#define GPIOD                       ((GPIO_TypeDef_t *)(GPIOD_BASE_ADDR))
#define GPIOE                       ((GPIO_TypeDef_t *)(GPIOE_BASE_ADDR))

#define RCC                         ((RCC_TypeDef_t *)(RCC_BASE_ADDR))

#define SYSCFG                      ((SYSCFG_TypeDef_t *)(SYSCFG_BASE_ADDR))

#define EXTI                        ((EXTI_TypeDef_t *)(EXTI_BASE_ADDR))

#define SPI1                        ((SPI_TypeDef_t *)(SPI1_BASE_ADDR))
#define SPI2                        ((SPI_TypeDef_t *)(SPI2_BASE_ADDR))
#define SPI3                        ((SPI_TypeDef_t *)(SPI3_BASE_ADDR))

#define USART2                      ((USART_TypeDef_t *)(USART2_BASE_ADDR))
#define USART3                      ((USART_TypeDef_t *)(USART3_BASE_ADDR))
#define UART4                       ((USART_TypeDef_t *)(UART4_BASE_ADDR))
#define UART5                       ((USART_TypeDef_t *)(UART5_BASE_ADDR))

#define USART1                      ((USART_TypeDef_t *)(USART1_BASE_ADDR))
#define USART6                      ((USART_TypeDef_t *)(USART6_BASE_ADDR))

#define I2C1                        ((I2C_TypeDef_t *)(I2C1_BASE_ADDR))
#define I2C2                        ((I2C_TypeDef_t *)(I2C2_BASE_ADDR))
#define I2C3                        ((I2C_TypeDef_t *)(I2C3_BASE_ADDR))

/*
 * Bit Definitions
 */
#define RCC_AHB1ENR_GPIOAEN_Pos     (0U)                               // RCC AHB1ENR register GPIOAEN Bit Position
#define RCC_AHB1ENR_GPIOAEN_Msk     (0x1 << RCC_AHB1ENR_GPIOAEN_Pos)   // RCC AHB1ENR register GPIOAEN Bit Mask
#define RCC_AHB1ENR_GPIOAEN         RCC_AHB1ENR_GPIOAEN_Msk            // RCC AHB1ENR register GPIOAEN Macro

#define RCC_AHB1ENR_GPIOBEN_Pos     (1U)                               // RCC AHB1ENR register GPIOBEN Bit Position
#define RCC_AHB1ENR_GPIOBEN_Msk     (0x1 << RCC_AHB1ENR_GPIOBEN_Pos)   // RCC AHB1ENR register GPIOBEN Bit Mask
#define RCC_AHB1ENR_GPIOBEN         RCC_AHB1ENR_GPIOBEN_Msk            // RCC AHB1ENR register GPIOBEN Macro

#define RCC_AHB1ENR_GPIOCEN_Pos     (2U)                               // RCC AHB1ENR register GPIOCEN Bit Position
#define RCC_AHB1ENR_GPIOCEN_Msk     (0x1 << RCC_AHB1ENR_GPIOCEN_Pos)   // RCC AHB1ENR register GPIOCEN Bit Mask
#define RCC_AHB1ENR_GPIOCEN         RCC_AHB1ENR_GPIOCEN_Msk            // RCC AHB1ENR register GPIOCEN Macro

#define RCC_AHB1ENR_GPIODEN_Pos     (3U)                               // RCC AHB1ENR register GPIODEN Bit Position
#define RCC_AHB1ENR_GPIODEN_Msk     (0x1 << RCC_AHB1ENR_GPIODEN_Pos)   // RCC AHB1ENR register GPIODEN Bit Mask
#define RCC_AHB1ENR_GPIODEN         RCC_AHB1ENR_GPIODEN_Msk            // RCC AHB1ENR register GPIODEN Macro

#define RCC_AHB1ENR_GPIOEEN_Pos     (4U)                               // RCC AHB1ENR register GPIOEEN Bit Position
#define RCC_AHB1ENR_GPIOEEN_Msk     (0x1 << RCC_AHB1ENR_GPIOEEN_Pos)   // RCC AHB1ENR register GPIOEEN Bit Mask
#define RCC_AHB1ENR_GPIOEEN         RCC_AHB1ENR_GPIOEEN_Msk            // RCC AHB1ENR register GPIOEEN Macro

#define RCC_APB1ENR_USART2EN_Pos    (17U)                              // RCC APB1ENR register USART2EN Bit Position
#define RCC_APB1ENR_USART2EN_Msk    (0x1 << RCC_APB1ENR_USART2EN_Pos)  // RCC APB1ENR register USART2EN Bit Mask
#define RCC_APB1ENR_USART2EN        RCC_APB1ENR_USART2EN_Msk           // RCC APB1ENR register USART2EN Macro

#define RCC_APB1ENR_SPI2EN_Pos      (14U)                              // RCC APB1ENR register SPI2EN Bit Position
#define RCC_APB1ENR_SPI2EN_Msk      (0x1 << RCC_APB1ENR_SPI2EN_Pos)    // RCC APB1ENR register SPI2EN Bit Mask
#define RCC_APB1ENR_SPI2EN          RCC_APB1ENR_SPI2ENN_Msk            // RCC APB1ENR register SPI2EN Macro

#define RCC_APB1ENR_SPI3EN_Pos      (15U)                              // RCC APB1ENR register SPI3EN Bit Position
#define RCC_APB1ENR_SPI3EN_Msk      (0x1 << RCC_APB1ENR_SPI3EN_Pos)    // RCC APB1ENR register SPI3EN Bit Mask
#define RCC_APB1ENR_SPI3EN          RCC_APB1ENR_SPI3ENN_Msk            // RCC APB1ENR register SPI3EN Macro

#define RCC_APB1ENR_I2C1EN_Pos      (21U)                              // RCC APB1ENR register I2C1EN Bit Position
#define RCC_APB1ENR_I2C1EN_Msk      (0x1 << RCC_APB1ENR_I2C1EN_Pos)    // RCC APB1ENR register I2C1EN Bit Mask
#define RCC_APB1ENR_I2C1EN          RCC_APB1ENR_I2C1EN_Msk             // RCC APB1ENR register I2C1EN Macro

#define RCC_APB1ENR_I2C2EN_Pos      (22U)                              // RCC APB1ENR register I2C2EN Bit Position
#define RCC_APB1ENR_I2C2EN_Msk      (0x1 << RCC_APB1ENR_I2C2EN_Pos)    // RCC APB1ENR register I2C2EN Bit Mask
#define RCC_APB1ENR_I2C2EN          RCC_APB1ENR_I2C2EN_Msk             // RCC APB1ENR register I2C2EN Macro

#define RCC_APB1ENR_I2C3EN_Pos      (23U)                              // RCC APB1ENR register I2C3EN Bit Position
#define RCC_APB1ENR_I2C3EN_Msk      (0x1 << RCC_APB1ENR_I2C3EN_Pos)    // RCC APB1ENR register I2C3EN Bit Mask
#define RCC_APB1ENR_I2C3EN          RCC_APB1ENR_I2C3EN_Msk             // RCC APB1ENR register I2C3EN Macro

#define RCC_APB2ENR_SYSCFGEN_Pos    (14U)                              // RCC APB2ENR register SYSCFGEN Bit Position
#define RCC_APB2ENR_SYSCFGEN_Msk    (0x1 << RCC_APB2ENR_SYSCFGEN_Pos)  // RCC APB2ENR register SYSCFGEN Bit Mask
#define RCC_APB2ENR_SYSCFGEN        RCC_APB2ENR_SYSCFGEN_Msk           // RCC APB2ENR register SYSCFGEN Macro

#define RCC_APB2ENR_SPI1EN_Pos    	(12U)                              // RCC APB2ENR register SPI1EN Bit Position
#define RCC_APB2ENR_SPI1EN_Msk      (0x1 << RCC_APB2ENR_SPI1EN_Pos)    // RCC APB2ENR register SPI1EN Bit Mask
#define RCC_APB2ENR_SPI1EN          RCC_APB2ENR_SPI1EN_Msk             // RCC APB2ENR register SPI1EN Macro

#define GPIO_LCKR_LCKK_Pos          (16U)                              // GPIO LCKR register LCKK Bit Position
#define GPIO_LCKR_LCKK_Msk          (0x1 << RCC_AHB1ENR_GPIOEEN_Pos)   // GPIO LCKR register LCKK Bit Mask
#define GPIO_LCKR_LCKK              RCC_AHB1ENR_GPIOEEN_Msk            // GPIO LCKR register LCKK Macro

#define GPIO_CR1_SPE                (6U)                               // SPI CR1 register SPE Bit Position

#define SPI_SR_RXNE                 (0U) 							   // SPI SR register RXNE Bit Position
#define SPI_SR_TXE                  (1U) 							   // SPI SR register TXE Bit Position
#define SPI_SR_BSY                  (7U) 							   // SPI SR register BSY Bit Position

#define SPI_CR1_DFF                 (11U)							   // SPI CR2 register DFF Bit Position

#define SPI_CR2_TXEIE               (7U)							   // SPI CR2 register TXEIE Bit Position
#define SPI_CR2_RXNEIE              (6U)							   // SPI CR2 register RXNEIE Bit Position

#define USART_CR1_UE 				(13U)							   // USART CR1 register UE Bit Position
#define USART_CR1_TXEIE             (7U)							   // USART CR1 register TXEIE Bit Position
#define USART_CR1_RXNEIE            (5U)							   // USART CR1 register RXNEIE Bit Position

#define USART_CR2_STOP 				(12U)							   // USART CR2 register STOP Bit Position

#define USART_SR_TXE 				(7U)							   // USART SR register TXE Bit Position
#define USART_SR_TC 				(6U)							   // USART SR register TC Bit Position
#define USART_SR_RXNE 				(5U)							   // USART SR register RXNE Bit Position

#define I2C_CR1_PE                  (0U)                               // I2C CR1 register PE Bit Position

/*
 * Flag Definitions
 */
#define SPI_TXE_Flag                (0x1U << SPI_SR_TXE)
#define SPI_BSY_Flag                (0x1U << SPI_SR_BSY)
#define SPI_RXNE_Flag               (0x1U << SPI_SR_RXNE)

#define USART_TXE_Flag                (0x1U << USART_SR_TXE)
#define USART_TC_Flag                 (0x1U << USART_SR_TC)
#define USART_RXNE_Flag                 (0x1U << USART_SR_RXNE)

/*
 * Peripheral and Communication Units
 */
#include "rcc.h"
#include "gpio.h"
#include "exti.h"
#include "spi.h"
#include "usart.h"
#include "i2c.h"

#endif /* INC_STM32F407XX_H_ */
