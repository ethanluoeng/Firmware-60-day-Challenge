/*
 * uart.h
 *
 *  Created on: Jul 6, 2026
 *      Author: ethan
 */

#ifndef UART_H_
#define UART_H_

#include <stdint.h>
#include "stm32f4xx.h"

#define SR_RXNE			(1U<<5)

void uart2_rxtx_init(void);
void uart2_tx_init(void);
void uart2_rx_interrupt_init(void);

char uart2_read(void);

#endif /* UART_H_ */
