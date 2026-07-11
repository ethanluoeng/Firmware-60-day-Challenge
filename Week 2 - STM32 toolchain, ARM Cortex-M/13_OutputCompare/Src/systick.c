#include "stm32f4xx.h"



#define SYSTICK_LOAD_VAL			16000
#define CTRL_ENABLE					(1U<<0)
#define CTRL_CLKSOURCE				(1U<<2)
#define CTRL_COUNTFLAG				(1U<<16)


void systickDelayMs(int delay)
{
	/*Reload with number of clocks per millisecond*/
	SysTick->LOAD = SYSTICK_LOAD_VAL;

	// Clear Systick current value register
	SysTick->VAL = 0;

	/*Enable systick and select internal clk src*/
	SysTick->CTRL = CTRL_ENABLE	| CTRL_CLKSOURCE;

	for (int i = 0; i < delay; i++) {

		// Stays in the loop when COUNTFLAG hasn't returned a 1 yet
		while((SysTick->CTRL & CTRL_COUNTFLAG) == 0) {}

	}

	SysTick->CTRL = 0;

}

