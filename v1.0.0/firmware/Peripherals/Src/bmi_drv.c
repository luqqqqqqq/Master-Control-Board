/* Includes ------------------------------------------------------------------*/
#include "bmi_drv.h"
//init result
int8_t rslt=BMI2_OK;
//bmi270 init
int8_t imu_init(void)
{	
	//init struct
	struct bmi2_dev bmi270;
	//Assign interface pointer
	//holds SPI chip selection
	static uint8_t dev_addr = 0x69;
	bmi270.intf_ptr = &dev_addr;
	//Pointer to the configuration data buffer address
	bmi270.config_file_ptr = NULL;
	//SPI communicate 
	bmi270.intf = BMI2_SPI_INTF;
	//bmi270 read & write & delay func
	bmi270.read = bmi2_spi_read;
	bmi270.write = bmi2_spi_write;
	bmi270.delay_us = bmi2_delay_us;
	//user set read & write length
	bmi270.read_write_len = READ_WRITE_LEN;
	//blind init struct with bmi270
	rslt=bmi270_init(&bmi270);
	if(rslt!=BMI2_OK)return rslt;
	//Accel and gyro configuration settings
	rslt=set_accel_gyro_config(&bmi270);
	if(rslt!=BMI2_OK)return rslt;
	//enable bmi270
	uint8_t sensor_list[2] = { BMI2_ACCEL, BMI2_GYRO};
	rslt=bmi270_sensor_enable(sensor_list, 2, &bmi270);
	return rslt;
}

//spi read for bmi270
BMI2_INTF_RETURN_TYPE bmi2_spi_read(uint8_t reg_addr, uint8_t *reg_data, uint32_t len, void *intf_ptr)
{
	//spi2 cs on
	SPI2_CS_ON
	//wait
	bmi2_delay_us(10, NULL);
	//tx what i need
	SPI2_TX(&reg_addr, 1);
	//rx msg that i need
	int8_t res = SPI2_RX(reg_data, len);
	//wait
	bmi2_delay_us(10, NULL);
	//spi2 cs on
	SPI2_CS_OFF
	return res;
}

//spi write for bmi270
BMI2_INTF_RETURN_TYPE bmi2_spi_write(uint8_t reg_addr, const uint8_t *reg_data, uint32_t len, void *intf_ptr)
{
	//spi2 cs on
	SPI2_CS_ON
	//wait
	bmi2_delay_us(10, NULL);
	//tx what i want to set
	SPI2_TX(&reg_addr, 1);
	//tx msg
	int8_t res = SPI2_TX((uint8_t*)reg_data, len);
	//wait
	bmi2_delay_us(10, NULL);
	//spi2 cs on
	SPI2_CS_OFF
	return res;
}

//delay 1us
uint32_t btick = 0;
uint32_t bmi2_1us(void)
{
	register uint32_t bms, bus;
	bms = HAL_GetTick();
	bus = TIM2->CNT;
	btick = bms*1000 + bus;
	return btick;
} 

//delay xus
void bmi2_delay_us(uint32_t period, void *intf_ptr)
{
	uint32_t now = bmi2_1us();
	while((bmi2_1us() - now) < period);
}

//delay xms
void bmi2_delay_ms(uint32_t ms)
{
	while(ms--)bmi2_delay_us(1000,NULL);
}

//This internal API is used to set configurations for accel and gyro.
int8_t set_accel_gyro_config(struct bmi2_dev *bmi2_dev)
{
    /* Status of api are returned to this variable. */
    int8_t rslt;
    /* Structure to define accelerometer and gyro configuration. */
    struct bmi2_sens_config config[2];
    /* Configure the type of feature. */
    config[ACCEL].type = BMI2_ACCEL;
    config[GYRO].type  = BMI2_GYRO;
    /* Get default configurations for the type of feature selected. */
    rslt = bmi270_get_sensor_config(config, 2, bmi2_dev);
    /* Map data ready interrupt to interrupt pin. */
    rslt = bmi2_map_data_int(BMI2_DRDY_INT, BMI2_INT1, bmi2_dev);
    if (rslt == BMI2_OK)
    {
        /* NOTE: The user can change the following configuration parameters according to their requirement. */
        /* Set Output Data Rate */
        config[ACCEL].cfg.acc.odr = BMI2_ACC_ODR_1600HZ;
        /* Gravity range of the sensor (+/- 2G, 4G, 8G, 16G). */
        config[ACCEL].cfg.acc.range = BMI2_ACC_RANGE_2G;
        /* The bandwidth parameter is used to configure the number of sensor samples that are averaged
         * if it is set to 2, then 2^(bandwidth parameter) samples
         * are averaged, resulting in 4 averaged samples.
         * Note1 : For more information, refer the datasheet.
         * Note2 : A higher number of averaged samples will result in a lower noise level of the signal, but
         * this has an adverse effect on the power consumed.
         */
        config[ACCEL].cfg.acc.bwp = BMI2_ACC_NORMAL_AVG4;
        /* Enable the filter performance mode where averaging of samples
         * will be done based on above set bandwidth and ODR.
         * There are two modes
         *  0 -> Ultra low power mode
         *  1 -> High performance mode(Default)
         * For more info refer datasheet.
         */
        config[ACCEL].cfg.acc.filter_perf = BMI2_PERF_OPT_MODE;
        /* The user can change the following configuration parameters according to their requirement. */
        /* Set Output Data Rate */
        config[GYRO].cfg.gyr.odr = BMI2_GYR_ODR_1600HZ;
        /* Gyroscope Angular Rate Measurement Range.By default the range is 2000dps. */
        config[GYRO].cfg.gyr.range = BMI2_GYR_RANGE_2000;
        /* Gyroscope bandwidth parameters. By default the gyro bandwidth is in normal mode. */
        config[GYRO].cfg.gyr.bwp = BMI2_GYR_NORMAL_MODE;
        /* Enable/Disable the noise performance mode for precision yaw rate sensing
         * There are two modes
         *  0 -> Ultra low power mode(Default)
         *  1 -> High performance mode
         */
        config[GYRO].cfg.gyr.noise_perf = BMI2_POWER_OPT_MODE;
        /* Enable/Disable the filter performance mode where averaging of samples
         * will be done based on above set bandwidth and ODR.
         * There are two modes
         *  0 -> Ultra low power mode
         *  1 -> High performance mode(Default)
         */
        config[GYRO].cfg.gyr.filter_perf = BMI2_PERF_OPT_MODE;
        /* Set the accel and gyro configurations. */
        rslt = bmi270_set_sensor_config(config, 2, bmi2_dev);
    }
    return rslt;
}

//get accel & gyro & temp
void bmi270_get_data(void)
{
	//get accel & gyro
	uint8_t reg = 0x0c|0x80;
	uint8_t data[13];
	SPI2_CS_ON	
	SPI2_TX(&reg, 1);
	SPI2_RX(data, 13);
	SPI2_CS_OFF
	for(uint8_t i=0;i<13;i++)data[i] = data[i+1];
	bmi270_raw_data.acc_x	= ((int16_t)(data[0]))  | ((int16_t)(data[1]) << 8);
	bmi270_raw_data.acc_y	= ((int16_t)(data[2]))  | ((int16_t)(data[3]) << 8);
	bmi270_raw_data.acc_z	= ((int16_t)(data[4]))  | ((int16_t)(data[5]) << 8);
	bmi270_raw_data.gyr_x	= ((int16_t)(data[6]))  | ((int16_t)(data[7]) << 8);
	bmi270_raw_data.gyr_y	= ((int16_t)(data[8]))  | ((int16_t)(data[9]) << 8);
	bmi270_raw_data.gyr_z	= ((int16_t)(data[10])) | ((int16_t)(data[11])<< 8);	
	//get temp
	reg = 0x22|0x80;
	SPI2_CS_ON	
	SPI2_TX(&reg, 1);
	SPI2_RX(data, 3);
	SPI2_CS_OFF
	for(uint8_t i=0;i<3;i++)data[i] = data[i+1];
	bmi270_raw_data.temp	 = (int16_t)data[0] | ( (int16_t)data[1] << 8);
}
