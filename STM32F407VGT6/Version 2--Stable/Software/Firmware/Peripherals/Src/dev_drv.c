/* Includes ------------------------------------------------------------------*/
#include "dev_drv.h"

//Enable all configured peripherals
void Device_init(void)
{
	CAN_Enable(&hcan1);
	CAN_Enable(&hcan2);
	UART_Enable(&huart1, (uint32_t)uart1_rx_buf, UART1_BUF_LEN);
	UART_Enable(&huart2, (uint32_t)uart2_rx_buf, UART2_BUF_LEN);
	UART_Enable(&huart3, (uint32_t)uart3_rx_buf, UART3_BUF_LEN);
	UART_Enable(&huart4, (uint32_t)uart4_rx_buf, UART4_BUF_LEN);
	UART_Enable(&huart5, (uint32_t)uart5_rx_buf, UART5_BUF_LEN);
	UART_Enable(&huart6, (uint32_t)uart6_rx_buf, UART6_BUF_LEN);
	if(imu_init()!=BMI2_OK)while(1);
}
