#include "adxl345.h"




char data;
 uint8_t data_rec[6];

void adxl_read_address (uint8_t reg)
{
	 I2C1_byteRead(MPU_DEVICE_ADDR, reg, &data);

}

void adxl_write (uint8_t reg, char value)
{
	char data[1];
	data[0] = value;

	I2C1_burstWrite(MPU_DEVICE_ADDR, reg,1, data) ;
}

void adxl_read_values (uint8_t reg)
{
	I2C1_burstRead(MPU_DEVICE_ADDR, reg, 6,(char *)data_rec);

}


// I have the MPU6050 instead
void mpu_init(void)
{
	// Enable I2C
	I2C1_init();

	// Read the WHO_AM_I, this should return 0x68
	adxl_read_address(WHO_AM_I);

	// to +-4g
	adxl_write(MPU_ACCEL_CONFIG, MPU_FOUR_G);

	// Wake it up
	adxl_write(PWR_MGMT_1, MPU_WAKE_UP);


}


void adxl_init (void)
{
	/*Enable I2C*/
	I2C1_init();

	/*Read the DEVID, this should return 0xE5*/
	adxl_read_address(DEVID_R);

	/*Set data format range to +-4g*/
	adxl_write (DATA_FORMAT_R, FOUR_G);

	/*Reset all bits*/
	adxl_write (POWER_CTL_R, RESET);

	/*Configure power control measure bit*/
	adxl_write (POWER_CTL_R, SET_MEASURE_B);
}
