#include "exti.h"

#define GPIOCEN				(1U<<2)
#define SYSCFGEN			(1U<<14)

void pc13_exti_init(void)
{
	// Disable global interrupt - good practice
	__disable_irq();

	// Enable clock for GPIOC
	RCC->AHB1ENR |= GPIOCEN;

	// Enable access to SYSCFG
	RCC->APB2ENR |= SYSCFGEN;

	// Set pc13 as input
	GPIOC->MODER &=~ (1U<<26);
	GPIOC->MODER &=~ (1U<<27);

	// Select port 13 for exti13
	SYSCFG->EXTICR[3] |= (1U<<5);

	// Unmask exti13
	EXTI->IMR |= (1U<<13);

	// Select falling edge trigger
	EXTI->FTSR |= (1U<<13);

	// Enable exti13 line in NVIC
	NVIC_EnableIRQ(EXTI15_10_IRQn);

	// Enable global interrupts
	__enable_irq();
}
