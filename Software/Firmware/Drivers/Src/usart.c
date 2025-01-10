#include "usart.h"

/*
 * @brief  USART_CloseISR_RX, Disables the interrupt for Transmission
 * @param  USART_Handle = User Config Structures
 * @retval Void
 */
static void USART_CloseISR_TX(USART_HandleTypeDef_t *USART_Handle)
{
	USART_Handle->Instance->CR1 &= ~(0x1U << USART_CR1_TXEIE);
	USART_Handle->TxDataSize = 0;
	USART_Handle->pTxDataAdrr = NULL;
	USART_Handle->busStateTx = USART_BUS_FREE;
}

/*
 * @brief  USART_CloseISR_RX, Disables the interrupt for Reception
 * @param  USART_Handle = User Config Structures
 * @retval Void
 */
static void USART_CloseISR_RX(USART_HandleTypeDef_t *USART_Handle)
{
	USART_Handle->Instance->CR1 &= ~(0x1U << USART_CR1_RXNEIE);
	USART_Handle->TxDataSize = 0;
	USART_Handle->pTxDataAdrr = NULL;
	USART_Handle->busStateTx = USART_BUS_FREE;
}

/*
 * @brief  USART_TransmitHelper, Stores the user data into the DR register
 * @param  USART_Handle = User Config Structures
 * @retval Void
 */
static void USART_TransmitHelper(USART_HandleTypeDef_t *USART_Handle)
{
	uint16_t *data16Bits;

	if((USART_Handle->Init.WordLength == USART_WORDLENGTH_9Bits) && (USART_Handle->Init.Parity == USART_PARITY_NONE))
	{
		data16Bits = (uint16_t*)(USART_Handle->pTxDataAdrr);
		USART_Handle->Instance->DR = (uint16_t)(*data16Bits & (uint16_t)(0x01FFU));
		USART_Handle->pTxDataAdrr += sizeof(uint16_t);
		USART_Handle->TxDataSize -= 2;
	}
	else
	{
		USART_Handle->Instance->DR = (uint8_t)(*(USART_Handle->pTxDataAdrr) & (uint16_t)(0x00FFU));
		USART_Handle->pTxDataAdrr++;
		USART_Handle->TxDataSize--;
	}

	if(USART_Handle->TxDataSize == 0)
	{
		USART_CloseISR_TX(USART_Handle);
	}
}

/*
 * @brief  USART_ReceiveHelper, Reads the data register and stores into the user variable
 * @param  USART_Handle = User Config Structures
 * @retval Void
 */
static void USART_ReceiveHelper(USART_HandleTypeDef_t *USART_Handle)
{
	uint16_t *data16Bits;
	uint8_t *data8Bits;

	if((USART_Handle->Init.WordLength == USART_WORDLENGTH_9Bits) && (USART_Handle->Init.Parity == USART_PARITY_NONE))
	{
		data16Bits = (uint16_t*)(USART_Handle->pRxDataAdrr);
		data8Bits = NULL;
	}
	else
	{
		data8Bits = (uint8_t*)(USART_Handle->pRxDataAdrr);
		data16Bits = NULL;
	}

	if(data8Bits == NULL)
	{
		*data16Bits = (uint16_t)(USART_Handle->Instance->DR & 0x01FFU);
		USART_Handle->pRxDataAdrr += sizeof(uint16_t);
		USART_Handle->RxDataSize -= 2;
	}
	else
	{
		if((USART_Handle->Init.WordLength == USART_WORDLENGTH_9Bits) && (USART_Handle->Init.Parity != USART_PARITY_NONE))
		{
			*data8Bits = (uint8_t)(USART_Handle->Instance->DR & 0x00FFU);
			USART_Handle->pRxDataAdrr++;
			USART_Handle->RxDataSize--;
		}
		else if((USART_Handle->Init.WordLength == USART_WORDLENGTH_8Bits) && (USART_Handle->Init.Parity == USART_PARITY_NONE))
		{
			*data8Bits = (uint8_t)(USART_Handle->Instance->DR & 0x00FFU);
			USART_Handle->pRxDataAdrr++;
			USART_Handle->RxDataSize--;
		}
		else
		{
			*data8Bits = (uint8_t)(USART_Handle->Instance->DR & 0x007FU);
			USART_Handle->pRxDataAdrr++;
			USART_Handle->RxDataSize--;
		}
	}

	if(USART_Handle->RxDataSize == 0)
	{
		USART_CloseISR_RX(USART_Handle);
	}
}

/*
 * @brief  USART_Init, Configures the USART peripheral
 * @param  USART_Handle = User Config Structures
 * @retval Void
 */
void USART_Init(USART_HandleTypeDef_t *USART_Handle)
{
	uint32_t tempValue = 0;
	uint32_t periphClock = 0;
	uint32_t mantissaPart = 0;
	uint32_t fractionPart = 0;
	uint32_t USART_DIV_Value = 0;

	/* Over Sampling, Word Length, Mode and Parity Configuration */
	tempValue = USART_Handle->Instance->CR1;
	tempValue |= (USART_Handle->Init.OverSampling) | (USART_Handle->Init.WordLength) | (USART_Handle->Init.Mode) |
			     (USART_Handle->Init.Parity) ;
	USART_Handle->Instance->CR1 = tempValue;

	/* Stop bits Configuration */
	tempValue = USART_Handle->Instance->CR2;
	tempValue &= ~(0x3U << USART_CR2_STOP);
	tempValue |= (USART_Handle->Init.StopBits);
	USART_Handle->Instance->CR2 = tempValue;

	/* Hardware Flow Control Configuration */
	tempValue = USART_Handle->Instance->CR3;
	tempValue |= (USART_Handle->Init.HardwareFlowControl);
	USART_Handle->Instance->CR3 = tempValue;

	/* Baud Rate Configuration */
	if(USART_Handle->Instance == USART1 || USART_Handle->Instance == USART6)
	{
		periphClock = RCC_GetPClock2();
	}
	else
	{
		periphClock = RCC_GetPClock1();
	}

	if(USART_Handle->Init.OverSampling == USART_OVERSAMPLING_8)
	{
		USART_DIV_Value = __USART_DIV_VALUE_8(periphClock, USART_Handle->Init.BaudRate);
		mantissaPart = (USART_DIV_Value / 100U);
		fractionPart = (USART_DIV_Value) - (mantissaPart * 100U);

		fractionPart = (((fractionPart * 8U) + 50U) / 100U) & (0x07U);
	}
	else
	{
		USART_DIV_Value = __USART_DIV_VALUE_16(periphClock, USART_Handle->Init.BaudRate);
		mantissaPart = (USART_DIV_Value / 100U);
		fractionPart = (USART_DIV_Value) - (mantissaPart * 100U);

		fractionPart = (((fractionPart * 8U) + 50U) / 100U) & (0x0FU);
	}

	tempValue |= (mantissaPart << 4U);
	tempValue |= (fractionPart << 0U);

	USART_Handle->Instance->BRR = tempValue;
}

/*
 * @brief  USART_PeriphCmd, Enable or Disable USART peripheral
 * @param  USART_Handle = User Config Structures
 * @param  stateOfUSART = ENABLE or DISABLE
 * @retval Void
 */
void USART_PeriphCmd(USART_HandleTypeDef_t *USART_Handle, FunctionalState_t stateOfUSART)
{
	if(stateOfUSART == ENABLE)
	{
		USART_Handle->Instance->CR1 |=  (0x1U << USART_CR1_UE);
	}
	else
	{
		USART_Handle->Instance->CR1 &= ~(0x1U << USART_CR1_UE);
	}
}

/*
 * @brief  USART_TransmitData, Transmits data
 * @param  USART_Handle = User Config Structures
 * @param  pData = Address of data to Send
 * @param  sizeOfData = Length of your data in bytes
 * @retval Void
 */
void USART_TransmitData(USART_HandleTypeDef_t *USART_Handle, uint8_t *pData, uint16_t sizeOfData)
{
	uint16_t *data16Bits;

	if((USART_Handle->Init.WordLength == USART_WORDLENGTH_9Bits) && (USART_Handle->Init.Parity == USART_PARITY_NONE))
	{
		data16Bits = (uint16_t*)pData;
	}
	else
	{
		data16Bits = NULL;
	}

	while(sizeOfData > 0)
	{
		while(!(USART_GetFlagStatus(USART_Handle, USART_TXE_Flag)));

		/* 9 bits Data No Parity is for Else Condition, for others you will be in If Case */
		if(data16Bits == NULL)
		{
			USART_Handle->Instance->DR = (uint8_t)(*pData & (0xFFU));
			pData++;
			sizeOfData--;
		}
		else
		{
			USART_Handle->Instance->DR = (uint16_t)(*data16Bits & (0x01FFU));
			data16Bits++;
			sizeOfData -= 2;
		}
	}

	while(!(USART_GetFlagStatus(USART_Handle, USART_TC_Flag)));
}

/*
 * @brief  USART_ReceiveData, Receive data
 * @param  USART_Handle = User Config Structures
 * @param  pData = Address of data to Send
 * @param  sizeOfData = Length of your data in bytes
 * @retval Void
 */
void USART_ReceiveData(USART_HandleTypeDef_t *USART_Handle, uint8_t *pData, uint16_t sizeOfData)
{
	uint16_t *data16Bits;
	uint8_t *data8Bits;

	if((USART_Handle->Init.WordLength == USART_WORDLENGTH_9Bits) && (USART_Handle->Init.Parity == USART_PARITY_NONE))
	{
		data16Bits = (uint16_t*)pData;
		data8Bits = NULL;
	}
	else
	{
		data8Bits = (uint8_t*)pData;
		data16Bits = NULL;
	}

	while(sizeOfData > 0)
	{
		while(!(USART_GetFlagStatus(USART_Handle, USART_RXNE_Flag)));

		if(data8Bits == NULL)
		{
			*data16Bits = (uint16_t)(USART_Handle->Instance->DR & 0x01FFU);
			data16Bits++;
			sizeOfData -= 2;
		}
		else
		{
			if((USART_Handle->Init.WordLength == USART_WORDLENGTH_9Bits) && (USART_Handle->Init.Parity != USART_PARITY_NONE))
			{
				*data8Bits = (uint8_t)(USART_Handle->Instance->DR & 0x00FFU);
				data8Bits++;
				sizeOfData--;
			}
			else if((USART_Handle->Init.WordLength == USART_WORDLENGTH_8Bits) && (USART_Handle->Init.Parity == USART_PARITY_NONE))
			{
				*data8Bits = (uint8_t)(USART_Handle->Instance->DR & 0x00FFU);
				data8Bits++;
				sizeOfData--;
			}
			else
			{
				*data8Bits = (uint8_t)(USART_Handle->Instance->DR & 0x007FU);
				data8Bits++;
				sizeOfData--;
			}
		}
	}
}

/*
 * @brief  USART_TransmitData, Transmits data data from external world with Interrupt method
 * @param  USART_Handle = User Config Structures
 * @param  pData = Address of data to Send
 * @param  sizeOfData = Length of your data in bytes
 * @retval Void
 */
void USART_TransmitData_IT(USART_HandleTypeDef_t *USART_Handle, uint8_t *pData, uint16_t sizeOfData)
{
	USART_BusStatus_t busState = USART_Handle->busStateTx;

	if(busState != USART_BUS_BUSY_TX)
	{
		USART_Handle->pTxDataAdrr = (uint8_t*)pData;
		USART_Handle->TxDataSize = (uint16_t)sizeOfData;
		USART_Handle->busStateTx = USART_BUS_BUSY_TX;
		USART_Handle->TxISRFunciton = USART_TransmitHelper;

		USART_Handle->Instance->CR1 |= (0x1U << USART_CR1_TXEIE);
	}
}

/*
 * @brief  USART_ReceiveData, Receive data from external world with Interrupt method
 * @param  USART_Handle = User Config Structures
 * @param  pData = Address of data to Send
 * @param  sizeOfData = Length of your data in bytes
 * @retval Void
 */
void USART_ReceiveData_IT(USART_HandleTypeDef_t *USART_Handle, uint8_t *pData, uint16_t sizeOfData)
{
	USART_BusStatus_t busState = USART_Handle->busStateRx;

	if(busState != USART_BUS_BUSY_RX)
	{
		USART_Handle->pTxDataAdrr = (uint8_t*)pData;
		USART_Handle->TxDataSize = (uint16_t)sizeOfData;
		USART_Handle->busStateTx = USART_BUS_BUSY_RX;
		USART_Handle->TxISRFunciton = USART_ReceiveHelper;

		USART_Handle->Instance->CR1 |= (0x1U << USART_CR1_RXNEIE);
	}
}

/*
 * @brief  USART_InterruptHandler, Works when USART interrupt
 * @param  USART_Handle = User Config Structures
 * @retval Void
 */
void USART_InterruptHandler(USART_HandleTypeDef_t *USART_Handle)
{
	uint8_t interruptSource = 0;
	uint8_t interruptFlag = 0;

	interruptSource = (uint8_t)(USART_Handle->Instance->CR1 >> USART_CR1_TXEIE) & 0x1U;
	interruptFlag = (uint8_t)(USART_Handle->Instance->SR >> USART_SR_TXE) & 0x1U;

	if(interruptSource && interruptFlag)
	{
		USART_Handle->TxISRFunciton(USART_Handle);
	}

	interruptSource = (uint8_t)(USART_Handle->Instance->CR1 >> USART_CR1_RXNEIE) & 0x1U;
	interruptFlag = (uint8_t)(USART_Handle->Instance->SR >> USART_SR_RXNE) & 0x1U;

	if(interruptSource && interruptFlag)
	{
		USART_Handle->RxISRFunciton(USART_Handle);
	}
}

/*
 * @brief  USART_GetFlagStatus, Return the flag of SR Register
 * @param  USART_Handle = User Config Structures
 * @param  USART_Flag = Flag name of SR Register
 * @retval USART_Flagstatus_t
 */
USART_Flagstatus_t USART_GetFlagStatus(USART_HandleTypeDef_t *USART_Handle, uint16_t USART_Flag)
{
	return (USART_Handle->Instance->SR & USART_Flag) ? USART_FLAG_SET : USART_FLAG_RESET;
}
