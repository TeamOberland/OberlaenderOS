/*
 * dmx.c
 *
 *  Created on: 19.06.2013
 *      Author: Manuel
 */


#include "dmx.h"
#include "../../genarch/dmx/dmx.h"


uint32_t dmx_init(uint8_t uartPort, uart_protocol_format_t *protocol)
{
    return __dmx_init(uartPort,UART_MDR1_MODE_SELECT_16X,protocol);
}

/*
* Returns 1 if uart transmission fifo queue is empty.
* If the Queue has at least one character the result will be 1.
*/
uint32_t dmx_disable(uint8_t uartPort)
{
    return uart_disable(uartPort);
}

/*
* Returns 1 if uart transmission fifo queue is empty.
* If the Queue has at least one character the result will be 1.
*/
uint32_t dmx_is_empty_write_queue(uint8_t uartPort)
{
    return uart_is_empty_write_queue(uartPort);
}
uint32_t dmx_is_empty_read_queue(uint8_t uartPort)
{
    return  uart_is_empty_read_queue(uartPort);
}
/* writes one character to the UART device */
uint32_t dmx_write(uint8_t uartPort, uint8_t* buffer)
{
   return uart_write(uartPort,buffer);
}
/* reads one character from the UART device */
uint32_t dmx_read(uint8_t uartPort, uint8_t* buffer)
{
    return uart_read(uartPort,buffer);
}
