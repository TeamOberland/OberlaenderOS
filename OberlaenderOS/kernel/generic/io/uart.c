/*
 * uart.c
 *
 *  Created on: 03.06.2013
 *      Author: Manuel
 */


#include <oos/uart.h>
#include "uart.h"

/*
* Returns 1 if uart transmission fifo queue is empty.
* If the Queue has at least one character the result will be 1.
*/
uint32_t uart_init(uint8_t uartPort, uart_protocol_format_t *protocol)
{
    return __uart_init(uartPort,UART_MDR1_MODE_SELECT_16X,protocol);
}

/*
* Returns 1 if uart transmission fifo queue is empty.
* If the Queue has at least one character the result will be 1.
*/
uint32_t uart_disable(uint8_t uartPort)
{
    if(__uart_is_valid_port(uartPort))
    return __uart_disable(uartPort);

    return 0;
}

/*
* Returns 1 if uart transmission fifo queue is empty.
* If the Queue has at least one character the result will be 1.
*/
uint32_t uart_is_empty_write_queue(uint8_t uartPort)
{
    if(__uart_is_valid_port(uartPort))
    return __uart_is_empty_write_queue(uartPort);

    return 0;
}
uint32_t uart_is_empty_read_queue(uint8_t uartPort)
{
    if(__uart_is_valid_port(uartPort))
    return __uart_is_empty_read_queue(uartPort);

    return 0;
}
/* writes one character to the UART device */
uint32_t uart_write(uint8_t uartPort, uint8_t* buffer)
{
    if(__uart_is_valid_port(uartPort))
    return __uart_write(uartPort, buffer);
    return 0;
}
/* reads one character from the UART device */
uint32_t uart_read(uint8_t uartPort, uint8_t* buffer)
{
    if(__uart_is_valid_port(uartPort))
    return __uart_read(uartPort, buffer);

    return 0;
}


