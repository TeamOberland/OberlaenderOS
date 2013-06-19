/*
 * expansion.c
 *
 *  Created on: 14.06.2013
 *      Author: Manuel
 */

#include <oos/types.h>
#include "../../genarch/io/expansion.h"

int8_t set_expansion_pin_mode(uint32_t pinNumber, uint8_t mode)
{
    return __set_expansion_pin_mode(pinNumber,mode);
}


