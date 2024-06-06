
#ifndef __GPIO_DRV_H
#define __GPIO_DRV_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "gpio.h"

//you can define written func in here 
//note!!!!! C99 invalid
#define LED_R_ON LED_R(GPIO_PIN_SET);
#define LED_G_ON LED_G(GPIO_PIN_SET);
#define LED_B_ON LED_B(GPIO_PIN_SET);
#define LED_R_OFF LED_R(GPIO_PIN_RESET);
#define LED_G_OFF LED_G(GPIO_PIN_RESET);
#define LED_B_OFF LED_B(GPIO_PIN_RESET);
#define SPI1_CS_ON SPI1_CS(GPIO_PIN_RESET);
#define SPI2_CS_ON SPI2_CS(GPIO_PIN_RESET);
#define SPI1_CS_OFF SPI1_CS(GPIO_PIN_SET);
#define SPI2_CS_OFF SPI2_CS(GPIO_PIN_SET);


void LED_R(GPIO_PinState PinState);
void LED_G(GPIO_PinState PinState);
void LED_B(GPIO_PinState PinState);
void SPI1_CS(GPIO_PinState PinState);
void SPI2_CS(GPIO_PinState PinState);

//GPIO it handle need to rewrite
__weak void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);

#endif
