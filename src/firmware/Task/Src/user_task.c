/* Includes ------------------------------------------------------------------*/
#include "user_task.h"
#include "iwdg.h"//use for refresh iwdg

//task handler
osThreadId Task1_Handler;

//define task func 
void Test_Task(void const * argument);
void Train_Task(void const * argument);
//user task init
void User_Task_Init(void)
{
  //config task 
  osThreadDef(Task1, Test_Task, osPriorityNormal, 0, 128);
  //create task
  Task1_Handler = osThreadCreate(osThread(Task1), NULL);
  //you can define your task here
}

//test task func 
void Test_Task(void const * argument)
{	
	while(1){
		uint8_t test[5]="test\n";
		LED_R_ON
		Set_tx_ID(0);
		HAL_CAN_AddTxMessage(&hcan1, &pheader, test, NULL);
		HAL_CAN_AddTxMessage(&hcan2, &pheader, test, NULL);
		HAL_IWDG_Refresh(&hiwdg);
		osDelay(500);
		LED_G_ON
		HAL_UART_Transmit_DMA(&huart1, test, 5);
		HAL_UART_Transmit_DMA(&huart3, test, 5);
		HAL_UART_Transmit_DMA(&huart4, test, 5);
		HAL_UART_Transmit_DMA(&huart5, test, 5);
		HAL_UART_Transmit_DMA(&huart6, test, 5);
		HAL_IWDG_Refresh(&hiwdg);
		osDelay(500);
		LED_B_ON
		bmi270_get_data();
		HAL_IWDG_Refresh(&hiwdg);
		osDelay(500);
		LED_R_OFF
		HAL_IWDG_Refresh(&hiwdg);
		osDelay(500);
		LED_G_OFF
		HAL_IWDG_Refresh(&hiwdg);
		osDelay(500);
		LED_B_OFF
		HAL_IWDG_Refresh(&hiwdg);
		osDelay(500);
	}
}

void Train_Task(void const * argument)
{
	uint8_t train_data[2]={0};
	train_data[0]=bmi270_raw_data.acc_x;
	train_data[1]=bmi270_raw_data.acc_x>>8;
	HAL_UART_Transmit_DMA(&huart1, train_data, 2);
	train_data[0]=bmi270_raw_data.acc_y;
	train_data[1]=bmi270_raw_data.acc_y>>8;
	HAL_UART_Transmit_DMA(&huart1, train_data, 2);
	train_data[0]=bmi270_raw_data.acc_z;
	train_data[1]=bmi270_raw_data.acc_z>>8;
	HAL_UART_Transmit_DMA(&huart1, train_data, 2);
	train_data[0]=bmi270_raw_data.gyr_x;
	train_data[1]=bmi270_raw_data.gyr_x>>8;
	HAL_UART_Transmit_DMA(&huart1, train_data, 2);
	train_data[0]=bmi270_raw_data.gyr_y;
	train_data[1]=bmi270_raw_data.gyr_y>>8;
	HAL_UART_Transmit_DMA(&huart1, train_data, 2);
	train_data[0]=bmi270_raw_data.gyr_z;
	train_data[1]=bmi270_raw_data.gyr_z>>8;
	HAL_UART_Transmit_DMA(&huart1, train_data, 2);
	train_data[0]=bmi270_raw_data.temp ;
	train_data[1]=bmi270_raw_data.temp >>8;
	HAL_UART_Transmit_DMA(&huart1, train_data, 2);
}
