# Mikrodenetleyici Driver Gelistirme

### **Harici Led Yakma** <br>
```c
#include "stm32f407xx.h"

static void GPIO_LedConfig();

int main(void)
{
	GPIO_LedConfig();
	GPIO_WritePin(GPIOD, GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15, GPIO_Pin_Set);

	for(;;);
}

static void GPIO_LedConfig()
{
	GPIO_InitTypedef_t GPIO_LedStruct = { 0 };

	RCC_GPIOD_CLK_ENABLE();

	GPIO_LedStruct.Pin = GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
	GPIO_LedStruct.Mode = GPIO_MODE_OUTPUT;
	GPIO_LedStruct.Speed = GPIO_SPEED_LOW;
	GPIO_LedStruct.Otype = GPIO_OTYPE_PP;
	GPIO_LedStruct.Pull = GPIO_PUPD_NOPULL;

	GPIO_Init(GPIOD, &GPIO_LedStruct);
}
```

<br>

### **Buton ile Led Yakma** <br> 
```c
#include "stm32f407xx.h"

static void GPIO_Config();

int main(void)
{
	GPIO_Config();

	if(GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_Pin_Set)
	{
		GPIO_WritePin(GPIOD, GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15, GPIO_Pin_Set);
	}
	else
	{
		GPIO_WritePin(GPIOD, GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15, GPIO_Pin_Reset);
	}

	for(;;);
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
```

<br>

### **External Interrupt** <br>
```c
#include "stm32f407xx.h"

static void GPIO_Config();
static void EXTI_Config();

void EXTI0_IRQHandler()
{
	if(EXTI->PR & 0x01)
	{
		EXTI->PR |= (0x01 << 0U);

		GPIO_WritePin(GPIOD, GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15, GPIO_Pin_Set);
	}
}

int main(void)
{
	GPIO_Config();
	EXTI_Config();

	for(;;)
	{

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
```

<br>

### **SPI Kullanimi** <br>
```c
#include "stm32f407xx.h"

static void GPIO_Config();
static void EXTI_Config();
static void SPI_GPIO_Config();
static void SPI_Config();

SPI_HandleTypedef_t SPI_Handle;

void EXTI0_IRQHandler()
{
	char msgToSend[] = "Hello World!\n";

	if(EXTI->PR & 0x01)
	{
		EXTI->PR |= (0x01 << 0U);

		SPI_TransmitData(&SPI_Handle, (uint8_t*)msgToSend, strlen(msgToSend));
	}
}

int main(void)
{
	GPIO_Config();
	EXTI_Config();
	SPI_GPIO_Config();
	SPI_Config();

	for(;;)
	{

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
	SPI_Handle.Init.BaudRate = SPI_BAUDRATE_DIV8;  //2 MHz
	SPI_Handle.Init.SSM_Cmd = SPI_SSM_ENABLE;
	SPI_Handle.Init.DFF_Format = SPI_DFF_8BITS;
	SPI_Handle.Init.CRC_Cmd = SPI_CRC_DISABLE;
	SPI_Handle.Init.FrameFormat = SPI_FF_MSB;
	SPI_Handle.Init.BusConfig = SPI_BUS_FullDuplex;
	SPI_Handle.Init.Mode = SPI_MODE_MASTER;

	SPI_Init(&SPI_Handle);

	SPI_PeriphCmd(&SPI_Handle, ENABLE);
}

static void SPI_GPIO_Config()
{
	GPIO_InitTypedef_t GPIO_InitStruct = { 0 };

	GPIO_InitStruct.Pin = GPIO_PIN_5 | GPIO_PIN_7;  //SCK = PA5, MOSI = PA7
	GPIO_InitStruct.Mode = GPIO_MODE_AF;
	GPIO_InitStruct.Otype = GPIO_OTYPE_PP;
	GPIO_InitStruct.Pull = GPIO_PUPD_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_VERY;
	GPIO_InitStruct.Alternate = GPIO_AF5;

	GPIO_Init(GPIOA, &GPIO_InitStruct);
}
```
<br>

### **SPI Interrupt** <br>
```c
#include "stm32f407xx.h"

static void GPIO_Config();
static void EXTI_Config();
static void SPI_Config();
static void SPI_GPIO_Config();

SPI_HandleTypedef_t SPI_Handle;

void EXTI0_IRQHandler()
{
	char msgToSend[] = "Hello World\n";

	if(EXTI->PR & 0x01)
	{
		EXTI->PR |= (0x01 << 0U);

		SPI_TransmitData_IT(&SPI_Handle, (uint8_t *)msgToSend, strlen(msgToSend));
	}
}

void SPI1_IRQHandler()
{
	SPI_InterruptHandler(&SPI_Handle);
}

int main(void)
{
	GPIO_Config();
	EXTI_Config();
	SPI_GPIO_Config();
	SPI_Config();

	for(;;)
	{

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
```

