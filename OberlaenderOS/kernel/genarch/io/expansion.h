/*
 * expansion.h
 *
 *  Created on: 14.06.2013
 *      Author: Manuel
 */

#ifndef EXPANSION_GENARCH_H_
#define EXPANSION_GENARCH_H_
#include <oos/types.h>

#define MODE_GPIO  4
#define MODE_UART  0

uint8_t __set_expansion_pin_mode(uint32_t pinNumber, uint8_t mode);

#endif /* EXPANSION_H_ */
