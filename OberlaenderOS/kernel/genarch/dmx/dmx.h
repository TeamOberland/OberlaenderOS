/*
 * dmx.h
 *
 *  Created on: 19.06.2013
 *      Author: Manuel
 */

#ifndef dmx_H_GENARCH
#define dmx_H_GENARCH

#include "../uart/uart.h"


bool_t __dmx_init(uint8_t uartPort,uint8_t uartMode, uart_protocol_format_t* config);

#endif /* dmx_H_ */
