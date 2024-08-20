#include "spi.h"

/*
 * @brief  SPI_CloseISR_TX, Disables the interrupt for Transmission
 * @param  SPI_Handle = User Config Structures
 * @retval Void
 */
static void SPI_CloseISR_TX(SPI_HandleTypedef_t *SPI_Handle)
{
	SPI_Handle->Instance->CR2 &= ~(0x1U << SPI_CR2_TXEIE);
	SPI_Handle->TxDataSize = 0;
	SPI_Handle->pTxDataAdrr = NULL;
	SPI_Handle->busStateTx = SPI_BUS_FREE;
}

/*
 * @brief  SPI_CloseISR_RX, Disables the interrupt for Reception
 * @param  SPI_Handle = User Config Structures
 * @retval Void
 */
static void SPI_CloseISR_RX(SPI_HandleTypedef_t *SPI_Handle)
{
	SPI_Handle->Instance->CR2 &= ~(0x1U << SPI_CR2_RXNEIE);
	SPI_Handle->RxDataSize = 0;
	SPI_Handle->pRxDataAdrr = NULL;
	SPI_Handle->busStateRx = SPI_BUS_FREE;
}

/*
 * @brief  SPI_TransmitHelper_16Bits, Stores the user data into the DR register for 16 bits format
 * @param  SPI_Handle = User Config Structures
 * @retval Void
 */
static void SPI_TransmitHelper_16Bits(SPI_HandleTypedef_t *SPI_Handle)
{
	SPI_Handle->Instance->DR = *((uint16_t*)(SPI_Handle->pTxDataAdrr));
	SPI_Handle->pTxDataAdrr += sizeof(uint16_t);
	SPI_Handle->TxDataSize -= 2;

	if(SPI_Handle->TxDataSize == 0)
	{
		SPI_CloseISR_TX(SPI_Handle);
	}
}

/*
 * @brief  SPI_TransmitHelper_8Bits, Stores the user data into the DR register for 8 bits format
 * @param  SPI_Handle = User Config Structures
 * @retval Void
 */
static void SPI_TransmitHelper_8Bits(SPI_HandleTypedef_t *SPI_Handle)
{
	SPI_Handle->Instance->DR = *((uint8_t*)(SPI_Handle->pTxDataAdrr));
	SPI_Handle->pTxDataAdrr += sizeof(uint8_t);
	SPI_Handle->TxDataSize --;

	if(SPI_Handle->TxDataSize == 0)
	{
		SPI_CloseISR_TX(SPI_Handle);
	}
}

/*
 * @brief  SPI_ReceiveHelper_16Bits, Reads the data register and stores into the user variable for 16 bits format
 * @param  SPI_Handle = User Config Structures
 * @retval Void
 */
static void SPI_ReceiveHelper_16Bits(SPI_HandleTypedef_t *SPI_Handle)
{
	*((uint16_t*)(SPI_Handle->pRxDataAdrr)) = (uint16_t)SPI_Handle->Instance->DR;
	SPI_Handle->pRxDataAdrr += sizeof(uint16_t);
	SPI_Handle->RxDataSize -= 2;

	if(SPI_Handle->RxDataSize == 0)
	{
		SPI_CloseISR_TX(SPI_Handle);
	}
}

/*
 * @brief  SPI_ReceiveHelper_8Bits, Reads the data register and stores into the user variable for 8 bits format
 * @param  SPI_Handle = User Config Structures
 * @retval Void
 */
static void SPI_ReceiveHelper_8Bits(SPI_HandleTypedef_t *SPI_Handle)
{
	*((uint8_t*)SPI_Handle->pRxDataAdrr) = *((__IO uint8_t*)&SPI_Handle->Instance->DR);
	SPI_Handle->pRxDataAdrr += sizeof(uint8_t);
	SPI_Handle->RxDataSize--;

	if(SPI_Handle->RxDataSize == 0)
	{
		SPI_CloseISR_TX(SPI_Handle);
	}
}

/*
 * @brief  SPI_Init, Configures the SPI peripheral
 * @param  SPI_Handle = User Config Structures
 * @retval Void
 */
void SPI_Init(SPI_HandleTypedef_t *SPI_Handle)
{
	uint32_t tempValue = 0;

	tempValue = SPI_Handle->Instance->CR1;

	tempValue |= (SPI_Handle->Init.Mode)     | (SPI_Handle->Init.CPHA)      | (SPI_Handle->Init.CPOL) |
		         (SPI_Handle->Init.BaudRate) | (SPI_Handle->Init.SSM_Cmd)   | (SPI_Handle->Init.DFF_Format) |
				 (SPI_Handle->Init.CRC_Cmd)  | (SPI_Handle->Init.BusConfig) | (SPI_Handle->Init.FrameFormat) ;

	SPI_Handle->Instance->CR1 = tempValue;
}


/*
 * @brief  SPI_PeriphCmd, Enable or Disable SPI peripheral
 * @param  SPI_Handle = User Config Structures
 * @param  stateOfSPI = ENABLE or DISABLE
 * @retval Void
 */
void SPI_PeriphCmd(SPI_HandleTypedef_t *SPI_Handle, FunctionalState_t stateOfSPI)
{
	if(stateOfSPI == ENABLE)
	{
		SPI_Handle->Instance->CR1 |=  (0x1U << GPIO_CR1_SPE);
	}
	else
	{
		SPI_Handle->Instance->CR1 &= ~(0x1U << GPIO_CR1_SPE);
	}
}

/*
 * @brief  SPI_TransmitData, Transmits data to the Slave
 * @param  SPI_Handle = User Config Structures
 * @param  pData = Address of data to Send
 * @param  sizeOfData = Length of your data in bytes
 * @retval Void
 */
void SPI_TransmitData(SPI_HandleTypedef_t *SPI_Handle, uint8_t *pData, uint16_t sizeOfData)
{
	if(SPI_Handle->Init.DFF_Format == SPI_DFF_16BITS)
	{
		while(sizeOfData > 0)
		{
			if(SPI_GetFlagStatus(SPI_Handle, SPI_TXE_Flag))
			{
				SPI_Handle->Instance->DR = *((uint16_t*)pData);
				pData += sizeof(uint16_t);
				sizeOfData -= 2;
			}
		}
	}
	else
	{
		while(sizeOfData > 0)
		{
			if(SPI_GetFlagStatus(SPI_Handle, SPI_TXE_Flag))
			{
				SPI_Handle->Instance->DR = *pData;
				pData += sizeof(uint8_t);
				sizeOfData--;
			}
		}
	}
	while(SPI_GetFlagStatus(SPI_Handle, SPI_BSY_Flag));
}

/*
 * @brief  SPI_ReceiveData, Receive data from the Slave
 * @param  SPI_Handle = User Config Structures
 * @param  pData = Address of data to store the values that I get
 * @param  sizeOfData = Length of your data in bytes
 * @retval Void
 */
void SPI_ReceiveData(SPI_HandleTypedef_t *SPI_Handle, uint8_t *pData, uint16_t sizeOfData)
{
	if(SPI_Handle->Init.DFF_Format == SPI_DFF_16BITS)
	{
		while(sizeOfData > 0)
		{
			if(SPI_GetFlagStatus(SPI_Handle, SPI_RXNE_Flag))
			{
				*((uint16_t*)pData) = (uint16_t)SPI_Handle->Instance->DR;
				pData += sizeof(uint16_t);
				sizeOfData -= 2;
			}
		}
	}
	else
	{
		while(sizeOfData > 0)
		{
			if(SPI_GetFlagStatus(SPI_Handle, SPI_RXNE_Flag))
			{
				*(pData) = *((__IO uint8_t*)&SPI_Handle->Instance->DR);
				pData += sizeof(uint8_t);
				sizeOfData--;
			}
		}
	}
}

/*
 * @brief  SPI_TransmitData_IT, Read the data from external world with Interrupt method
 * @param  SPI_Handle = User Config Structures
 * @param  pData = Address of data to Send
 * @param  sizeOfData = Length of your data in bytes
 * @retval Void
 */
void SPI_TransmitData_IT(SPI_HandleTypedef_t *SPI_Handle, uint8_t *pData, uint16_t sizeOfData)
{
	SPI_BusStatus_t busState = SPI_Handle->busStateTx;

	if(busState != SPI_BUS_BUSY_TX)
	{
		SPI_Handle->pTxDataAdrr = (uint8_t*)pData;
		SPI_Handle->TxDataSize = (uint16_t)sizeOfData;
		SPI_Handle->busStateTx = SPI_BUS_BUSY_TX;

		if(SPI_Handle->Instance->CR1 & (0x1U << SPI_CR1_DFF))
		{
			SPI_Handle->TxISRFunciton = SPI_TransmitHelper_16Bits;
		}
		else
		{
			SPI_Handle->TxISRFunciton = SPI_TransmitHelper_8Bits;
		}

		SPI_Handle->Instance->CR2 |= (0x1U << SPI_CR2_TXEIE);
	}
}

/*
 * @brief  SPI_ReceiveData_IT, Send the data from external world with Interrupt method
 * @param  SPI_Handle = User Config Structures
 * @param  pData = Address of data to Send
 * @param  sizeOfData = Length of your data in bytes
 * @retval Void
 */
void SPI_ReceiveData_IT(SPI_HandleTypedef_t *SPI_Handle, uint8_t *pData, uint16_t sizeOfData)
{
	SPI_BusStatus_t busState = SPI_Handle->busStateRx;

	if(busState != SPI_BUS_BUSY_RX)
	{
		SPI_Handle->pRxDataAdrr = (uint8_t*)pData;
		SPI_Handle->RxDataSize = (uint16_t)sizeOfData;
		SPI_Handle->busStateRx = SPI_BUS_BUSY_RX;

		if(SPI_Handle->Instance->CR1 & (0x1U << SPI_CR1_DFF))
		{
			SPI_Handle->RxISRFunciton = SPI_ReceiveHelper_16Bits;
		}
		else
		{
			SPI_Handle->RxISRFunciton = SPI_ReceiveHelper_8Bits;
		}

		SPI_Handle->Instance->CR2 |= (0x1U << SPI_CR2_RXNEIE);
	}
}

/*
 * @brief  SPI_InterruptHandler, Works when SPI interrupt
 * @param  SPI_Handle = User Config Structures
 * @retval Void
 */
void SPI_InterruptHandler(SPI_HandleTypedef_t *SPI_Handle)
{
	uint8_t interruptSource = 0;
	uint8_t interruptFlag = 0;

	interruptSource = SPI_Handle->Instance->CR2 & (0x1U << SPI_CR2_TXEIE);
	interruptFlag = SPI_Handle->Instance->SR & (0x1U << SPI_SR_TXE);

	if((interruptSource != 0) && (interruptFlag != 0))
	{
		SPI_Handle->TxISRFunciton(SPI_Handle);
	}

	interruptSource = SPI_Handle->Instance->CR2 & (0x1U << SPI_CR2_RXNEIE);
	interruptFlag = SPI_Handle->Instance->SR & (0x1U << SPI_SR_RXNE);

	if((interruptSource != 0) && (interruptFlag != 0))
	{
		SPI_Handle->RxISRFunciton(SPI_Handle);
	}
}

/*
 * @brief  SPI_GetFlagStatus, Return the flag of SR Register
 * @param  SPI_Handle = User Config Structures
 * @param  SPI_Flag = Flag name of SR Register
 * @retval SPI_Flagstatus_t
 */
SPI_Flagstatus_t SPI_GetFlagStatus(SPI_HandleTypedef_t *SPI_Handle, uint16_t SPI_Flag)
{
	return (SPI_Handle->Instance->SR & SPI_Flag) ? SPI_FLAG_SET : SPI_FLAG_RESET;
}

