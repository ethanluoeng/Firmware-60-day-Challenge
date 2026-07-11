#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "uart.h"
#include "adc.h"
#include "systick.h"
#include "timer.h"


int main(void)
{
	tim_pa5_output_compare();
	while (1) {}
}
