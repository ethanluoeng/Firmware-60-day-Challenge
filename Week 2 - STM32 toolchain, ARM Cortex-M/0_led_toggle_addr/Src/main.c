// Where is LED connected?
// Port: A
// Pin: 5

#include <stdint.h>
#define PERIPH_BASE            (0x40000000UL)

#define AHB1PERIPH_OFFSET      (0x00020000UL)
#define AHB1PERIPH_BASE        (PERIPH_BASE + AHB1PERIPH_OFFSET)

#define GPIOA_OFFSET           (0x0000UL)
#define GPIOA_BASE             (AHB1PERIPH_BASE + GPIOA_OFFSET)

#define RCC_OFFSET             (0x3800UL)
#define RCC_BASE               (AHB1PERIPH_BASE + RCC_OFFSET)
// We need RCC to enable clock access to GPIOA
// RCC has registers for enabling the AHBs and APBs

#define GPIOAEN                (1U<<0)

#define PIN5                   (1U<<5)
#define LED_PIN                PIN5


#define IO volatile

typedef struct {
	volatile uint32_t DUMMY[12];
	volatile uint32_t AHB1ENR;
} RCC_Typedef;

typedef struct {
	volatile uint32_t MODER;			// GPIO port mode register,		Address offset: 0x00
	volatile uint32_t DUMMY[4];
	volatile uint32_t ODR;				// GPIO port output data register,		Address: 0x14
} GPIO_Typedef;

#define RCC						((RCC_Typedef*) RCC_BASE)
#define GPIOA					((GPIO_Typedef*) GPIOA_BASE)

int main(void)
{
	// Enable clock access to GPIOA
	RCC->AHB1ENR |= GPIOAEN;

	// Set PAS as output pin
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &=~ (1U<<11);


	while(1) {
		GPIOA->ODR ^= LED_PIN;
		for (int i = 0; i < 100000; i++) {}
	}

}

