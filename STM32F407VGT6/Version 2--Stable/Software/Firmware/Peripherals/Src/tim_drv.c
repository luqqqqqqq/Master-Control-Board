/* Includes ------------------------------------------------------------------*/
#include "tim_drv.h"

//tim for Enable 
//extern TIM_HandleTypeDef htim1;

//tim Enable
//tim2 is used for freertos
void TIM_Enable(void)
{
	//HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
}

//set TIM 1 channel 1 capture/compare register
void TIM1_Channel1_Set(uint32_t triggle){
	//TIM1->CCR1 = triggle;
}

