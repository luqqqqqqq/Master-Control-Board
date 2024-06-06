
#ifndef __BMI_DRV_H
#define __BMI_DRV_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "bmi2_defs.h"
#include "bmi270.h"
#include "gpio_drv.h"
#include "spi_drv.h"

//user set read & write length
#define READ_WRITE_LEN   UINT8_C(46)
//choose accel or gyro 
#define ACCEL          UINT8_C(0x00)
#define GYRO           UINT8_C(0x01)

//bmi270 data struct
typedef struct{
	int16_t acc_x;
	int16_t acc_y;
	int16_t acc_z;
	int16_t gyr_x;
	int16_t gyr_y;
	int16_t gyr_z;
	int16_t temp;
}bmi270_data;

//data storge
static bmi270_data bmi270_raw_data;

//bmi270 init func
int8_t imu_init(void);

//spi read for bmi270
BMI2_INTF_RETURN_TYPE bmi2_spi_read(uint8_t reg_addr, uint8_t *reg_data, uint32_t len, void *intf_ptr);

//spi write for bmi270
BMI2_INTF_RETURN_TYPE bmi2_spi_write(uint8_t reg_addr, const uint8_t *reg_data, uint32_t len, void *intf_ptr);

//config accel gyro for bmi270
int8_t set_accel_gyro_config(struct bmi2_dev *bmi2_dev);

//delay 1us
uint32_t bmi2_1us(void);

//delay xus
void bmi2_delay_us(uint32_t period, void *intf_ptr);

//delay xms
void bmi2_delay_ms(uint32_t ms);

//get accel & gyro & temp
void bmi270_get_data(void);

#endif
