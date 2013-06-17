/*
 * driver_shared.c
 *
 *  Created on: 14.06.2013
 *      Author: Manuel
 */

#include "driver_shared.h"
#include "../../kernel/generic/io/expansion.h"

uint8_t driver_set_expansion_pin_mode(uint32_t pinNumber, uint8_t mode)
{
   return set_expansion_pin_mode(pinNumber,mode);
}

