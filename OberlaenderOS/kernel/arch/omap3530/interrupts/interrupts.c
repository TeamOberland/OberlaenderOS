/*
 * interrupts.c
 *
 *  Created on: 02.04.2013
 *      Author: Daniel
 */

#include "../../../genarch/interrupts/interrupts.h"


void inline enable_interrupts()
{
    ASM("CPSIE fi");
}

void inline disable_interrupts()
{
    ASM("CPSID fi");
}


void inline enable_irq()
{
    ASM("CPSIE i");
}

void inline disable_irq()
{
    ASM("CPSIE f");
}
