/*
 * dmx.h
 *
 *  Created on: 19.06.2013
 *      Author: Manuel
 */

#ifndef dmx_GENERIC_H_
#define dmx_GENERIC_H_

#include <oos/types.h>
#include "uart.h"
#include "../../genarch/uart/uart.h"

/*
* Returns 1 if uart transmission fifo queue is empty.
* If the Queue has at least one character the result will be 1.
*/
uint32_t dmx_is_empty_write_queue(uint8_t uartPort);
uint32_t dmx_is_empty_read_queue(uint8_t uartPort);
uint32_t dmx_activate_pin(uint8_t uartPort);
/* writes one character to the UART device */
uint32_t dmx_write(uint8_t uartPort, uint8_t* buffer);
/* reads one character from the UART device */
uint32_t dmx_read(uint8_t uartPort, uint8_t* buffer);
uint32_t dmx_disable(uint8_t uartPort);
uint32_t dmx_init(uint8_t uartPort, uart_protocol_format_t *protocol);
uint32_t dmx_send_start_sequence(uint8_t uartPort);

#endif
