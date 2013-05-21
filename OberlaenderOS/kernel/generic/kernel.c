/*
 * boot.c
 *
 *  Created on: 27.03.2013
 *      Author: Daniel
 */

#include "kernel.h"
#include "../genarch/arch.h"
#include "interrupts/irq.h"
#include "interrupts/timer.h"

void setup_kernel()
{
    setup_arch();

    /* Init IRQ and timer system */
    __disable_interrupts();
    irq_disable();
    irq_init();
//    timer_init();
    irq_enable();
}
