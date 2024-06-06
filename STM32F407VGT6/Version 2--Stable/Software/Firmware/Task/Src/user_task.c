/* Includes ------------------------------------------------------------------*/
#include "user_task.h"
#include "iwdg.h"//use for refresh iwdg

//task handler
osThreadId Task1_Handler;

//define task func 
void Start_Task1(void const * argument);

//user task init
void User_Task_Init(void)
{
  //config task 
  osThreadDef(Task1, Start_Task1, osPriorityNormal, 0, 128);
  //create task
  Task1_Handler = osThreadCreate(osThread(Task1), NULL);
  //you can define your task here
}

//task func 
void Start_Task1(void const * argument)
{
	while(1){
//		uint8_t test[5]="test\n";
//		LED_R_ON
//		Set_tx_ID(0);
//		HAL_CAN_AddTxMessage(&hcan1, &pheader, test, NULL);
//		HAL_CAN_AddTxMessage(&hcan2, &pheader, test, NULL);
//		HAL_IWDG_Refresh(&hiwdg);
//		osDelay(500);
//		LED_G_ON
//		HAL_UART_Transmit_DMA(&huart1, test, 5);
//		HAL_UART_Transmit_DMA(&huart3, test, 5);
//		HAL_UART_Transmit_DMA(&huart4, test, 5);
//		HAL_UART_Transmit_DMA(&huart5, test, 5);
//		HAL_UART_Transmit_DMA(&huart6, test, 5);
//		HAL_IWDG_Refresh(&hiwdg);
//		osDelay(500);
//		LED_B_ON
		bmi270_get_data();
//		HAL_IWDG_Refresh(&hiwdg);
//		osDelay(500);
//		LED_R_OFF
//		HAL_IWDG_Refresh(&hiwdg);
//		osDelay(500);
//		LED_G_OFF
//		HAL_IWDG_Refresh(&hiwdg);
//		osDelay(500);
//		LED_B_OFF
//		HAL_IWDG_Refresh(&hiwdg);
//		osDelay(500);
	}
}
