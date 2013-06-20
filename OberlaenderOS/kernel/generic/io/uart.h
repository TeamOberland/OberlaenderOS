/*
 * uart.h
 *
 *  Created on: 03.06.2013
 *      Author: Manuel
 */

#ifndef UART_GENERIC_H_
#define UART_GENERIC_H_
#include "../../genarch/uart/uart.h"
/*
* Returns 1 if uart transmission fifo queue is empty.
* If the Queue has at least one character the result will be 1.
*/
uint32_t uart_is_empty_write_queue(uint8_t uartPort);
uint32_t uart_is_empty_read_queue(uint8_t uartPort);
uint32_t uart_activate_pin(uint8_t uartPort);
/* writes one character to the UART device */
uint32_t uart_write(uint8_t uartPort, uint8_t* buffer);
/* reads one character from the UART device */
uint32_t uart_read(uint8_t uartPort, uint8_t* buffer);
uint32_t uart_disable(uint8_t uartPort);
uint32_t uart_init(uint8_t uartPort, uart_protocol_format_t *protocol);


#endif /* UART_GENERIC_H_ */
