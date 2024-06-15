
#ifndef __USER_HANDLER_H
#define __USER_HANDLER_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "can_drv.h"

//all handler
__WEAK void CAN1_RX_Handler(uint32_t rxId, uint8_t *rxBuf);
__WEAK void CAN2_RX_Handler(uint32_t rxId, uint8_t *rxBuf);
__WEAK void UART1_IDLE_Handler(uint8_t* buf);
__WEAK void UART2_IDLE_Handler(uint8_t* buf);
__WEAK void UART3_IDLE_Handler(uint8_t* buf);
__WEAK void UART4_IDLE_Handler(uint8_t* buf);
__WEAK void UART5_IDLE_Handler(uint8_t* buf);
__WEAK void UART6_IDLE_Handler(uint8_t* buf);
__weak void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);

#endif
