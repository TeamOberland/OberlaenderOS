/*
 * boot.c
 *
 *  Created on: 27.03.2013
 *      Author: Daniel
 */

#include "kernel.h"
#include "../genarch/arch.h"
#include "ipc/ipc.h"
#include "interrupts/irq.h"
#include "interrupts/timer.h"
#include "scheduler/scheduler.h"
#include "mmu/mmu.h"

void setup_kernel()
{
    setup_arch();

    /* Init IRQ and timer system */
    __disable_interrupts();
    irq_disable();
    irq_init();
    scheduler_init();
    /* timer_init(); */
    ipc_init();
    irq_enable();

    //mmu_init();
}


void kernel_sleep(uint32_t ms)
{
    // https://code.google.com/p/puppybits/source/browse/lib/ksleep.c
    int i;
    while(ms--)
    {
        for(i = 0; i < 1000; i++)
        {
            asm("\t mov r0, r0");
            asm("\t mov r0, r0");
            asm("\t mov r0, r0");
        }
    }
}
