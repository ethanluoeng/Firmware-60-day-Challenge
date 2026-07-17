#include "adxl345.h"


// Just realized that the MPU6050 does not support SPI at all so this will remain unfinished...
void mpu_read(uint8_t address, uint8_t* rxdata)
{


	  /*Pull cs line low to enable slave*/
	  cs_enable();

      /*Send address*/
	  spi1_transmit(&address,1);

	  /*Read 6 bytes */
	  spi1_receive(rxdata,6);

	  /*Pull cs line high to disable slave*/
	  cs_disable();
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
