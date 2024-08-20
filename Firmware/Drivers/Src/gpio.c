#include "gpio.h"

/*
 * @brief  GPIO_Init, Configures the port and pin
 * @param  GPIOx = GPIO Port Base Address
 * @param  GPIO_InitTypedef_t = User Config Structures
 * @retval None
 */
void GPIO_Init(GPIO_TypeDef_t *GPIOx, GPIO_InitTypedef_t *GPIO_ConfigStruct)
{
	uint32_t position;
	uint32_t fakePosition = 0x00U;
	uint32_t lastPosition = 0x00U;
	uint32_t tempValue = 0x00U;

	for(position=0; position < 16U; position++)
	{
		fakePosition = 0x1U << position;

		lastPosition = (uint32_t)(GPIO_ConfigStruct->Pin) & fakePosition;

		if(lastPosition == fakePosition)
		{
			/*--------------------- GPIO Mode Configuration ------------------------*/
			/* Configure IO Direction mode (Input, Output, Alternate or Analog) */
			tempValue = GPIOx->MODER;
			tempValue &= ~(0x03U << (position * 2U));
			tempValue |= (GPIO_ConfigStruct->Mode << (position * 2U));
			GPIOx->MODER = tempValue;

			if(GPIO_ConfigStruct->Mode == GPIO_MODE_OUTPUT || GPIO_ConfigStruct->Mode == GPIO_MODE_AF)
			{
				/* Configure the IO Output Type */
				tempValue = GPIOx->OTYPER;
				tempValue &= ~(0x01U << position);
				tempValue |= (GPIO_ConfigStruct->Otype << position);
				GPIOx->OTYPER = tempValue;

				/* Configure the IO Speed */
				tempValue = GPIOx->OSPEEDER;
				tempValue &= ~(0x03U << (position * 2U));
				tempValue |= (GPIO_ConfigStruct->Speed << (position * 2U));
				GPIOx->OSPEEDER = tempValue;
			}

			/* Configure the IO Pull-up or Pull down*/
			tempValue = GPIOx->PUPDR;
			tempValue &= ~(0x03U << (position * 2U));
			tempValue |= (GPIO_ConfigStruct->Pull << (position * 2U));
			GPIOx->PUPDR = tempValue;

			/* Configure the IO Alternate*/
			if(GPIO_ConfigStruct->Mode == GPIO_MODE_AF)
			{
				tempValue = GPIOx->AFR[position >> 3U];
				tempValue &= ~(0xFU << ((position & 0x7U) * 4U));
				tempValue |= (GPIO_ConfigStruct->Alternate << ((position & 0x7U) * 4U));
				GPIOx->AFR[position >> 3U] = tempValue;
			}
		}
	}
}

/*
 * @brief  GPIO_Write_Pin, makes pin High or Low
 * @param  GPIOx = GPIO Port Base Address
 * @param  pinNumber = GPIO Pin Numbers 0-15
 * @param  pinState = GPIO_Pin_Set OR GPIO_Pin_Reset
 * @retval None
 */
void GPIO_WritePin(GPIO_TypeDef_t *GPIOx, uint16_t pinNumber, GPIO_PinState_t pinState)
{
	if(pinState == GPIO_Pin_Set)
	{
		GPIOx->BSRR = pinNumber;
	}
	else
	{
		GPIOx->BSRR = pinNumber << 16U;
	}
}

/*
 * @brief  GPIO_Read_Pin, makes the pin of GPIOx Port
 * @param  GPIOx = GPIO Port Base Address
 * @param  pinNumber = GPIO Pin Numbers 0-15
 * @retval GPIO_PinState_t
 */
GPIO_PinState_t GPIO_ReadPin(GPIO_TypeDef_t *GPIOx, uint16_t pinNumber)
{
	GPIO_PinState_t bitStatus = GPIO_Pin_Reset;

	if((GPIOx->IDR & pinNumber) != GPIO_Pin_Reset)
	{
		bitStatus = GPIO_Pin_Set;
	}
	return bitStatus;
}

/*
 * @brief  GPIO_Lock_Pin, makes the pin of GPIOx Port
 * @param  GPIOx = GPIO Port Base Address
 * @param  pinNumber = GPIO Pin Numbers 0-15
 * @retval None
 */
void GPIO_LockPin(GPIO_TypeDef_t *GPIOx, uint16_t pinNumber)
{
	uint32_t tempValue = GPIO_LCKR_LCKK | pinNumber;

	GPIOx->LCKR = tempValue;    /* Set LCKx bit    LCKK='1' + LCK[15-0] */
	GPIOx->LCKR = pinNumber;    /* Reset LCKx bit  LCKK='0' + LCK[15-0] */
	GPIOx->LCKR = tempValue;    /* Set LCKx bit    LCKK='1' + LCK[15-0] */
	tempValue = GPIOx->LCKR;    /* Read LCKR register */
}

/*
 * @brief  GPIO_Toggle_Pin, toggles the pin of GPIOx port
 * @param  GPIOx = GPIO Port Base Address
 * @param  pinNumber = GPIO Pin Numbers 0-15
 * @retval None
 */
void GPIO_TogglePin(GPIO_TypeDef_t *GPIOx, uint16_t pinNumber)
{
	 uint32_t odr;

	 odr = GPIOx->ODR;

	 GPIOx->BSRR = ((odr & pinNumber) << 16U) | (~odr & pinNumber);
}

