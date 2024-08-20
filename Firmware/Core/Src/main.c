#include "stm32f407xx.h"

static void GPIO_Config();
static void EXTI_Config();
static void SPI_Config();
static void SPI_GPIO_Config();
static void UART_Config();
static void UART_GPIO_Config();
static void I2C_Config();

SPI_HandleTypedef_t SPI_Handle;
USART_HandleTypeDef_t USART_Handle;
I2C_HandleTypeDef_t I2C_Handle;

void EXTI0_IRQHandler()
{
	char msgToSend[] = "Hello World\n";

	if(EXTI->PR & 0x01)
	{
		EXTI->PR |= (0x01 << 0U);

		SPI_ReceiveData_IT(&SPI_Handle, (uint8_t *)msgToSend, strlen(msgToSend));
	}
}

void SPI1_IRQHandler()
{
	SPI_InterruptHandler(&SPI_Handle);
}

void USART2_IRQHandler()
{
	USART_InterruptHandler(&USART_Handle);
}

int main(void)
{
	char msgToSend[] = "Hello World\n";
	char msgGet[20] = "";

	GPIO_Config();
	EXTI_Config();
	SPI_GPIO_Config();
	SPI_Config();
	UART_Config();
	UART_GPIO_Config();

	USART_TransmitData(&USART_Handle, (uint8_t*)msgToSend, strlen(msgToSend));

	for(;;)
	{
		USART_ReceiveData(&USART_Handle, (uint8_t*)msgGet, strlen(msgGet));
	}
}

static void GPIO_Config()
{
	GPIO_InitTypedef_t GPIO_InitStruct = { 0 };

	RCC_GPIOD_CLK_ENABLE();
	RCC_GPIOA_CLK_ENABLE();

	GPIO_InitStruct.Pin = GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT;
	GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
	GPIO_InitStruct.Otype = GPIO_OTYPE_PP;
	GPIO_InitStruct.Pull = GPIO_PUPD_NOPULL;

	GPIO_Init(GPIOD, &GPIO_InitStruct);

	memset(&GPIO_InitStruct, 0, sizeof(GPIO_InitStruct));

	GPIO_InitStruct.Pin = GPIO_PIN_0;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PUPD_PULLDOWN;

	GPIO_Init(GPIOA, &GPIO_InitStruct);
}

static void EXTI_Config()
{
	EXTI_InitTypeDef_t EXTI_InitStruct = { 0 };

	RCC_SYSCFG_CLK_ENABLE();

	EXTI_LineConfig(EXTI_GPIOA, EXTI_LINE_0);

	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct.EXTI_LineNumber = EXTI_LINE_0;
	EXTI_InitStruct.EXTI_Mode = EXTI_MODE_INTERRUPT;
	EXTI_InitStruct.TriggerSelection = EXTI_TRIGGER_RISING;

	EXTI_Init(&EXTI_InitStruct);

	NVIC_EnableInterrupt(EXTI0_IRQn);

}

static void SPI_Config()
{
	RCC_SPI1_CLK_ENABLE();

	SPI_Handle.Instance = SPI1;
	SPI_Handle.Init.CPHA = SPI_CPHA_FIRST;
	SPI_Handle.Init.CPOL = SPI_CPOL_LOW;
	SPI_Handle.Init.BaudRate = SPI_BAUDRATE_DIV2; //2 MHz
	SPI_Handle.Init.SSM_Cmd = SPI_SSM_ENABLE;
	SPI_Handle.Init.DFF_Format = SPI_DFF_8BITS;
	SPI_Handle.Init.CRC_Cmd = SPI_CRC_DISABLE;
	SPI_Handle.Init.FrameFormat = SPI_FF_MSB;
	SPI_Handle.Init.BusConfig = SPI_BUS_FullDuplex;

	SPI_Init(&SPI_Handle);

	NVIC_EnableInterrupt(SPI1_IRQn);

	SPI_PeriphCmd(&SPI_Handle, ENABLE);
}

static void SPI_GPIO_Config()
{
	GPIO_InitTypedef_t GPIO_InitStruct = { 0 };

	GPIO_InitStruct.Pin = GPIO_PIN_5 | GPIO_PIN_7; //SCK = PA5, MOSI = PA7
	GPIO_InitStruct.Mode = GPIO_MODE_AF;
	GPIO_InitStruct.Otype = GPIO_OTYPE_PP;
	GPIO_InitStruct.Pull = GPIO_PUPD_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_VERY;
	GPIO_InitStruct.Alternate = GPIO_AF5;

	GPIO_Init(GPIOA, &GPIO_InitStruct);
}

static void UART_Config()
{
	RCC_USART2_CLK_ENABLE();

	USART_Handle.Instance = USART2;
	USART_Handle.Init.BaudRate = 115200;
	USART_Handle.Init.HardwareFlowControl = USART_HW_NONE;
	USART_Handle.Init.Mode = USART_MODE_Tx_Rx;
	USART_Handle.Init.OverSampling = USART_OVERSAMPLING_16;
	USART_Handle.Init.Parity = USART_PARITY_NONE;
	USART_Handle.Init.StopBits = USART_STOP_1;
	USART_Handle.Init.WordLength = USART_WORDLENGTH_8Bits;

	USART_Init(&USART_Handle);

	NVIC_EnableInterrupt(USART2_IRQn);

	USART_PeriphCmd(&USART_Handle, ENABLE);
}

static void UART_GPIO_Config()
{
	GPIO_InitTypedef_t GPIO_InitStruct = { 0 };

	GPIO_InitStruct.Pin = GPIO_PIN_2 | GPIO_PIN_2; //TX = PA2, RX = PA3
	GPIO_InitStruct.Mode = GPIO_MODE_AF;
	GPIO_InitStruct.Otype = GPIO_OTYPE_PP;
	GPIO_InitStruct.Pull = GPIO_PUPD_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_VERY;
	GPIO_InitStruct.Alternate = GPIO_AF7;

	GPIO_Init(GPIOA, &GPIO_InitStruct);
}

static void I2C_Config()
{
	I2C_Handle.Instance = I2C1;

	I2C_Init(&I2C_Handle);

	I2C_PeriphCmd(I2C_Handle.Instance, ENABLE);
}


