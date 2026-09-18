/* Includes ------------------------------------------------------------------*/
#include "gpio_drv.h"

//you can write func for define in here 

void LED_R(GPIO_PinState PinState)
{
	HAL_GPIO_WritePin(GPIOE, LED_R_Pin, PinState);
}

void LED_G(GPIO_PinState PinState)
{
	HAL_GPIO_WritePin(GPIOE, LED_G_Pin, PinState);
}

void LED_B(GPIO_PinState PinState)
{
	HAL_GPIO_WritePin(GPIOE, LED_B_Pin, PinState);
}

void SPI1_CS(GPIO_PinState PinState)
{
	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, PinState);
}

void SPI2_CS(GPIO_PinState PinState)
{
	HAL_GPIO_WritePin(SPI2_CS_GPIO_Port, SPI2_CS_Pin, PinState);
}
