
#ifndef __TIM_DRV_H
#define __TIM_DRV_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

//tim Enable func
void TIM_Enable(void);

//set tim triggle
void TIM1_Channel1_Set(uint32_t triggle);

#endif
