/* Includes ------------------------------------------------------------------*/
#include "spi_drv.h"

//you can write func for communicate in here 

HAL_StatusTypeDef SPI1_RX(uint8_t *pData, uint16_t Size)
{
	return HAL_SPI_Receive(&hspi1, pData, Size, 1000);
}

HAL_StatusTypeDef SPI2_RX(uint8_t *pData, uint16_t Size)
{
	return HAL_SPI_Receive(&hspi2, pData, Size, 1000);
}

HAL_StatusTypeDef SPI1_TX(uint8_t *pData, uint16_t Size)
{
	return HAL_SPI_Transmit(&hspi1, pData, Size, 1000);
}

HAL_StatusTypeDef SPI2_TX(uint8_t *pData, uint16_t Size)
{
	return HAL_SPI_Transmit(&hspi2, pData, Size, 1000);
}
