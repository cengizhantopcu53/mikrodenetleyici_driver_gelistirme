#include "exti.h"

/*
 * @brief  EXTI_Init for Valid GPIO port and Line Number
 * @param  EXTI_InitStruct = User Config Structure
 * @retval None
 */
void EXTI_Init(EXTI_InitTypeDef_t *EXTI_InitStruct)
{
	uint32_t tempValue = 0;

	tempValue = (uint32_t)EXTI_BASE_ADDR;

	EXTI->IMR &= ~(0x1U << EXTI_InitStruct->EXTI_LineNumber);
	EXTI->EMR &= ~(0x1U << EXTI_InitStruct->EXTI_LineNumber);

	if(EXTI_InitStruct->EXTI_LineCmd != DISABLE)
	{
		tempValue += EXTI_InitStruct->EXTI_Mode;

		*((__IO uint32_t*)tempValue) |= (0x1U << EXTI_InitStruct->EXTI_LineNumber);

		tempValue = (uint32_t)EXTI_BASE_ADDR;

		EXTI->RTSR &= ~(0x1U << EXTI_InitStruct->EXTI_LineNumber);
		EXTI->FTSR &= ~(0x1U << EXTI_InitStruct->EXTI_LineNumber);

		if(EXTI_InitStruct->TriggerSelection == EXTI_TRIGGER_RISING_FALLING)
		{
			EXTI->RTSR |= (0x1U << EXTI_InitStruct->EXTI_LineNumber);
			EXTI->FTSR |= (0x1U << EXTI_InitStruct->EXTI_LineNumber);
		}
		else
		{
			tempValue += EXTI_InitStruct->TriggerSelection;

			*((__IO uint32_t*)tempValue) |= (0x1U << EXTI_InitStruct->EXTI_LineNumber);
		}
	}
	else
	{
		tempValue = (uint32_t)EXTI_BASE_ADDR;

		tempValue += EXTI_InitStruct->EXTI_Mode;

		*((__IO uint32_t*)tempValue) &= ~(0x1U << EXTI_InitStruct->EXTI_LineNumber);
	}
}

/*
 * @brief  GPIO_LineConfig, Configures the port and pin for SYSCFG
 * @param  PortSource = Port Value A-H
 * @param  LineSource = Pin Numbers
 * @retval None
 */
void EXTI_LineConfig(uint8_t PortSource, uint8_t EXTI_LineSource)
{
	uint32_t tempValue = 0;

	tempValue = SYSCFG->EXTI_CR[EXTI_LineSource >> 2U];
	tempValue &= ~(0xFU << (EXTI_LineSource & 0x3U) * 4);
	tempValue = (PortSource << (EXTI_LineSource & 0x3U) * 4);
	SYSCFG->EXTI_CR[EXTI_LineSource >> 2U] = tempValue;
}

/*
 * @brief  NVIC_EnableInterrupt
 * @param  IRQNumber = IRQ Number of Line
 * @retval None
 */
void NVIC_EnableInterrupt(IRQn_TypeDef_t IRQNumber)
{
    uint32_t tempValue = 0;

    tempValue = *((IRQNumber >> 5U) + NVIC_ISER0);
    tempValue &= ~(0x1U << (IRQNumber & 0x1FU));
    tempValue |=  (0x1U << (IRQNumber & 0x1FU));
    *((IRQNumber >> 5U) + NVIC_ISER0) = tempValue;
}

