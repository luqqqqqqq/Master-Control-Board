
#ifndef __SPI_DRV_H
#define __SPI_DRV_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

//spi for communicate
extern SPI_HandleTypeDef hspi1;
extern SPI_HandleTypeDef hspi2;

//CS choose in gpio_drv.h low voltage is enable spi 

//func for spi tx & rx
HAL_StatusTypeDef SPI1_RX(uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef SPI2_RX(uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef SPI1_TX(uint8_t *pData, uint16_t Size);
HAL_StatusTypeDef SPI2_TX(uint8_t *pData, uint16_t Size);

#endif
