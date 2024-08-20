#ifndef INC_USART_H_
#define INC_USART_H_

#include "stm32f407xx.h"

/*
 * @defgroup Mode_Types
 */
#define USART_MODE_Rx                   ((uint32_t)(0x00000004))
#define USART_MODE_Tx                   ((uint32_t)(0x00000008))
#define USART_MODE_Tx_Rx                ((uint32_t)(0x0000000C))

/*
 * @defgroup WordLength_Types
 */
#define USART_WORDLENGTH_8Bits          ((uint32_t)(0x00000000))
#define USART_WORDLENGTH_9Bits          ((uint32_t)(0x00001000))

/*
 * @defgroup Parity_Types
 */
#define USART_PARITY_NONE          		((uint32_t)(0x00000000))
#define USART_PARITY_EVEN          		((uint32_t)(0x00000400))
#define USART_PARITY_ODD           		((uint32_t)(0x00000600))

/*
 * @defgroup Stop_Types
 */
#define USART_STOP_1          		    ((uint32_t)(0x00000000))
#define USART_STOP_HALF          		((uint32_t)(0x00001000))
#define USART_STOP_2           		    ((uint32_t)(0x00002000))
#define USART_STOP_1_HALF               ((uint32_t)(0x00003000))

/*
 * @defgroup OverSampling_Types
 */
#define USART_OVERSAMPLING_16          	((uint32_t)(0x00000000))
#define USART_OVERSAMPLING_8          	((uint32_t)(0x00008000))

/*
 * @defgroup HardwareFlowControl_Types
 */
#define USART_HW_NONE         			((uint32_t)(0x00000000))
#define USART_HW_RTS         			((uint32_t)(0x00000100))
#define USART_HW_CTS         			((uint32_t)(0x00000200))
#define USART_HW_RTS_CTS            	((uint32_t)(0x00000300))

#define __USART_DIV_VALUE_8(_CLOCK_, __BAUDRATE__) \
			(25U * (uint32_t)(_CLOCK_)) / (4U * (uint32_t)(__BAUDRATE__))

#define __USART_DIV_VALUE_16(_CLOCK_, __BAUDRATE__) \
			(25U * (uint32_t)(_CLOCK_)) / (2U * (uint32_t)(__BAUDRATE__))

typedef enum
{
	USART_FLAG_RESET = 0x0U,
	USART_FLAG_SET   = !USART_FLAG_RESET

}USART_Flagstatus_t;

typedef enum
{
	USART_BUS_FREE 	  = 0x0U,
	USART_BUS_BUSY_TX = 0x1U,
	USART_BUS_BUSY_RX = 0x2U

}USART_BusStatus_t;

typedef struct
{
	uint32_t Mode;						/*!> Transmission and Reception Modes @def_group Mode_Types 		*/
	uint32_t BaudRate;					/*!> User Value for UART Baudrate                                   */
	uint32_t WordLength;				/*!> 8 Bits & 9 Bits Modes @def_group WordLength_Types      		*/
	uint32_t Parity;					/*!> Even & 9 Odd Parity Modes @def_group Parity_Types      		*/
	uint32_t StopBits;					/*!> Stop Bits Modes @def_group Stop_Types                  		*/
	uint32_t OverSampling;				/*!> OverSampling Modes @def_group OverSampling_Types     			*/
	uint32_t HardwareFlowControl;		/*!> HardwareFlowControl Modes @def_group HardwareFlowControl_Types */

}USART_InitTypeDef_t;

typedef struct __USART_HandleTypedef_t
{
	USART_TypeDef_t *Instance;
	USART_InitTypeDef_t Init;
	uint8_t *pTxDataAdrr;
	uint16_t TxDataSize;
	uint8_t busStateTx;
	void(*TxISRFunciton)(struct __USART_HandleTypedef_t *USART_Handle);
	uint8_t *pRxDataAdrr;
	uint16_t RxDataSize;
	uint8_t busStateRx;
	void(*RxISRFunciton)(struct __USART_HandleTypedef_t *USART_Handle);

}USART_HandleTypeDef_t;

void USART_Init(USART_HandleTypeDef_t *USART_Handle);
void USART_PeriphCmd(USART_HandleTypeDef_t *USART_Handle, FunctionalState_t stateOfUSART);
void USART_TransmitData(USART_HandleTypeDef_t *USART_Handle, uint8_t *pData, uint16_t sizeOfData);
void USART_ReceiveData(USART_HandleTypeDef_t *USART_Handle, uint8_t *pData, uint16_t sizeOfData);
void USART_TransmitData_IT(USART_HandleTypeDef_t *USART_Handle, uint8_t *pData, uint16_t sizeOfData);
void USART_ReceiveData_IT(USART_HandleTypeDef_t *USART_Handle, uint8_t *pData, uint16_t sizeOfData);
void USART_InterruptHandler(USART_HandleTypeDef_t *USART_Handle);
USART_Flagstatus_t USART_GetFlagStatus(USART_HandleTypeDef_t *USART_Handle, uint16_t USART_Flag);

#endif /* INC_USART_H_ */
