/*
 * uart.h
 *
 *  Created on: 29.05.2013
 *      Author: Manuel
 */

#ifndef UART_H_Genarch
#define UART_H_Genarch

#include <oos/types.h>
#include <oos/uart.h>



/*
* Returns 1 if uart transmission fifo queue is empty.
* If the Queue has at least one character the result will be 1.
*/
bool_t __uart_is_empty_write_queue(uint8_t uartPort);
bool_t __uart_is_empty_read_queue(uint8_t uartPort);


/* writes one character to the UART device */
uint32_t __uart_write(uint8_t uartPort, uint8_t* buffer);
/* reads one character from the UART device */
uint32_t __uart_read(uint8_t uartPort, uint8_t* buffer);
bool_t __uart_is_valid_port(uint8_t uartPort);
bool_t __uart_init(uint8_t uartPort,uint8_t uartMode, uart_protocol_format_t* config);

#endif /* UART_H_Genarch */
