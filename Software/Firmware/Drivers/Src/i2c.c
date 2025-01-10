#include "i2c.h"

/*
 * @brief  I2C_PeriphCmd, Enable or Disable I2C peripheral
 * @param  I2Cx = I2C Peripheral
 * @param  stateOfI2C = ENABLE or DISABLE
 * @retval Void
 */
void I2C_PeriphCmd(I2C_TypeDef_t *I2Cx, FunctionalState_t stateOfI2C)
{
	if(stateOfI2C == ENABLE)
	{
		I2Cx->CR1 |=  (0x1U << I2C_CR1_PE);
	}
	else
	{
		I2Cx->CR1 &= ~(0x1U << I2C_CR1_PE);
	}
}

void I2C_Init(I2C_HandleTypeDef_t *I2C_Handle)
{
	uint32_t pClockValue = 0x0U;

	pClockValue = RCC_GetPClock1();

	if(Check_PClock_Value(pClockValue, I2C_Handle->Init.ClockSpeed) != 1U)
	{
		uint32_t tempValue = 0x0U;
		uint32_t freqValue = 0x0U;

		/* ACK State and Stretching Mode Configuration */
		tempValue = I2C_Handle->Instance->CR1;
		tempValue |= (I2C_Handle->Init.ACK_State) | (I2C_Handle->Init.ClockStretch);
		I2C_Handle->Instance->CR1 = tempValue;

		/* Frequenct Value of PCLOCK for Clock Generation */
		freqValue = I2C_Get_FreqValue(pClockValue);
		tempValue = I2C_Handle->Instance->CR2;
		tempValue |= (freqValue << 0U);
		I2C_Handle->Instance->CR2 = tempValue;

		/* Address Configuration */
		tempValue = I2C_Handle->Instance->OAR1;

		if(I2C_Handle->Init.AdressingMode == I2C_ADDRESS_7)
		{
			tempValue |= (I2C_Handle->Init.MyOwnAdress << 1U);
		}
		else
		{
			tempValue |= (I2C_Handle->Init.MyOwnAdress << 0U);
		}

	}
}


