#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "uart.h"
#include "adc.h"


uint32_t sensor_value;

void adc_callback(void);

int main(void)
{

	uart2_tx_init();					// For the printf to work
	pa1_adc_interrupt_init();
	start_conversion();

	while (1) {}
}


void adc_callback(void)
{
	sensor_value = ADC1->DR;
	printf("Sensor value : %d \n\r",(int)sensor_value);
}


void ADC_IRQHandler(void)
{
	if (ADC1->SR & SR_EOC) {
		adc_callback();
	}
}
