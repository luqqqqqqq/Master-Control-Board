
#ifndef __UART_DRV_H
#define __UART_DRV_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "string.h"

//uart for Enable 
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;
extern UART_HandleTypeDef huart4;
extern UART_HandleTypeDef huart5;
extern UART_HandleTypeDef huart6;

//uart rx buf
#define UART1_BUF_LEN 128
#define UART2_BUF_LEN 128
#define UART3_BUF_LEN 128
#define UART4_BUF_LEN 128
#define UART5_BUF_LEN 128
#define UART6_BUF_LEN 128
static uint8_t uart1_rx_buf[UART1_BUF_LEN];
static uint8_t uart2_rx_buf[UART2_BUF_LEN];
static uint8_t uart3_rx_buf[UART3_BUF_LEN];
static uint8_t uart4_rx_buf[UART4_BUF_LEN];
static uint8_t uart5_rx_buf[UART5_BUF_LEN];
static uint8_t uart6_rx_buf[UART6_BUF_LEN];

//uart Enable func
void UART_Enable(UART_HandleTypeDef* huart, \
	uint32_t buf, \
	uint32_t len);

//handle for idle it func, need to add in stm32f4xx_it.c
void UART_IRQHandler(UART_HandleTypeDef *huart);

//handle need to rewrite
__WEAK void UART1_IDLE_Handler(uint8_t* buf);
__WEAK void UART2_IDLE_Handler(uint8_t* buf);
__WEAK void UART3_IDLE_Handler(uint8_t* buf);
__WEAK void UART4_IDLE_Handler(uint8_t* buf);
__WEAK void UART5_IDLE_Handler(uint8_t* buf);
__WEAK void UART6_IDLE_Handler(uint8_t* buf);

//uart tx func in hal_uart.c, use this func to tx
//HAL_StatusTypeDef HAL_UART_Transmit_DMA(UART_HandleTypeDef *huart, const uint8_t *pData, uint16_t Size);

#endif
