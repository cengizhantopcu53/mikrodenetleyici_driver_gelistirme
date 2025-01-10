#ifndef INC_EXTI_H_
#define INC_EXTI_H_

#include "stm32f407xx.h"

typedef struct
{
	uint8_t EXTI_LineNumber;				/*!> EXTI Line number for valid GPIO pin @ref EXTI_Line_Pin_define */
	uint8_t TriggerSelection;				/*!> EXTI Trigger @ref EXTI_Trigger 							   */
	uint8_t EXTI_Mode;						/*!> EXTI Mode values @ref EXTI_Modes                              */
	FunctionalState_t EXTI_LineCmd;			/*!> Mask or Unmask the Line number                                */

}EXTI_InitTypeDef_t;

/*
 * @defgroup EXTI_GPIO_Port_define
 */
#define EXTI_GPIOA           ((uint8_t)0x0)
#define EXTI_GPIOB           ((uint8_t)0x1)
#define EXTI_GPIOC           ((uint8_t)0x2)
#define EXTI_GPIOD           ((uint8_t)0x3)
#define EXTI_GPIOE           ((uint8_t)0x4)
#define EXTI_GPIOF           ((uint8_t)0x5)
#define EXTI_GPIOG           ((uint8_t)0x6)
#define EXTI_GPIOH           ((uint8_t)0x7)

/*
 * @defgroup EXTI_Line_Pin_define
 */
#define EXTI_LINE_0          ((uint8_t)0x0)
#define EXTI_LINE_1          ((uint8_t)0x1)
#define EXTI_LINE_2          ((uint8_t)0x2)
#define EXTI_LINE_3          ((uint8_t)0x3)
#define EXTI_LINE_4          ((uint8_t)0x4)
#define EXTI_LINE_5          ((uint8_t)0x5)
#define EXTI_LINE_6          ((uint8_t)0x6)
#define EXTI_LINE_7          ((uint8_t)0x7)
#define EXTI_LINE_8          ((uint8_t)0x8)
#define EXTI_LINE_9          ((uint8_t)0x9)
#define EXTI_LINE_10         ((uint8_t)0xA)
#define EXTI_LINE_11         ((uint8_t)0xB)
#define EXTI_LINE_12         ((uint8_t)0xC)
#define EXTI_LINE_13         ((uint8_t)0xD)
#define EXTI_LINE_14         ((uint8_t)0xE)
#define EXTI_LINE_15         ((uint8_t)0xF)

/*
 * @defgroup EXTI_Trigger
 */
#define EXTI_TRIGGER_NONE                   0x00000000U
#define EXTI_TRIGGER_RISING                 0x00000001U
#define EXTI_TRIGGER_FALLING                0x00000002U
#define EXTI_TRIGGER_RISING_FALLING         (EXTI_TRIGGER_RISING | EXTI_TRIGGER_FALLING)

/*
 * @defgroup EXTI_Modes
 */
#define EXTI_MODE_INTERRUPT                 (0x00U)
#define EXTI_MODE_EVENT                     (0x04U)

void EXTI_Init(EXTI_InitTypeDef_t *EXTI_InitStruct);
void EXTI_LineConfig(uint8_t PortSource, uint8_t EXTI_LineSource);
void NVIC_EnableInterrupt(IRQn_TypeDef_t IRQNumber);

#endif /* INC_EXTI_H_ */
