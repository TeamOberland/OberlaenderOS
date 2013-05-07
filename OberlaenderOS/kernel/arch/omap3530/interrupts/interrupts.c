/*
 * interrupts.c
 *
 *  Created on: 11.04.2013
 *      Author: Daniel
 */

#include "interrupts.h"

void __enable_irqid(uint32_t irq)
{
    printf("Enabling irq %i (reg: %i, bit %i)\n", irq, irq/32, irq%32);
    *((memory_mapped_io_t)(MPU_INTC + INTCPS_MIR_CLEAR(irq/32))) |= (1 << (irq % 32));
}

