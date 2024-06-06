/* Includes ------------------------------------------------------------------*/
#include "uart_drv.h"

//uart Enable
void UART_Enable(UART_HandleTypeDef* huart, uint32_t buf, uint32_t len)
{
	//clean idle it flag
	__HAL_UART_CLEAR_IDLEFLAG(huart);
	//enable idle it
	__HAL_UART_ENABLE_IT(huart, UART_IT_IDLE);
	//enable DMA stream(com to dma)
	SET_BIT(huart->Instance->CR3, USART_CR3_DMAR);	
	//enable DMA transmitter(dma to mem)
	if(HAL_DMA_Start(huart->hdmarx, huart->Instance->DR, buf, len)!=HAL_OK)while(1);
}

//handle for idle it, need to add in stm32f4xx_it.c
void UART_IRQHandler(UART_HandleTypeDef *huart)
{
    //judge idle it
	if( __HAL_UART_GET_FLAG(huart, UART_FLAG_IDLE) &&__HAL_UART_GET_IT_SOURCE(huart, UART_IT_IDLE))
	{
		//disable DMA
		__HAL_DMA_DISABLE(huart->hdmarx);
		
		//clean idle it
		__HAL_UART_CLEAR_IDLEFLAG(huart);	
		
		//handle, need to rewrite idle handle func
		if(huart == &huart1){UART1_IDLE_Handler(uart1_rx_buf);memset(uart1_rx_buf, 0, UART1_BUF_LEN);}
		if(huart == &huart2){UART2_IDLE_Handler(uart2_rx_buf);memset(uart2_rx_buf, 0, UART2_BUF_LEN);}
		if(huart == &huart3){UART3_IDLE_Handler(uart3_rx_buf);memset(uart3_rx_buf, 0, UART3_BUF_LEN);}
		if(huart == &huart4){UART4_IDLE_Handler(uart4_rx_buf);memset(uart4_rx_buf, 0, UART4_BUF_LEN);}
		if(huart == &huart5){UART5_IDLE_Handler(uart5_rx_buf);memset(uart5_rx_buf, 0, UART5_BUF_LEN);}
		if(huart == &huart6){UART6_IDLE_Handler(uart6_rx_buf);memset(uart6_rx_buf, 0, UART6_BUF_LEN);}
		
		//enable DMA	  
		__HAL_DMA_ENABLE(huart->hdmarx);
	}
}


