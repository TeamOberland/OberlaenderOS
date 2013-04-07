/*
 * boot.c
 *
 *  Created on: 27.03.2013
 *      Author: Daniel
 */

#include "kernel.h"
#include "../genarch/arch.h"
#include "interrupts/irq.h"

void setup_kernel()
{
    setup_arch();
}
