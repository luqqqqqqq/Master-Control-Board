
#ifndef __DEV_DRV_H
#define __DEV_DRV_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "can_drv.h"
#include "uart_drv.h"
#include "tim_drv.h"
#include "gpio_drv.h"
#include "spi_drv.h"
#include "bmi_drv.h"

//Enable all configured peripherals
void Device_init(void);

#endif
