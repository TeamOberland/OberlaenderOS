/*
 * irq.c
 *
 *  Created on: 07.04.2013
 *      Author: Daniel
 */

#include "irq.h"
#include <oos/types.h>
#include "../../genarch/scheduler/context.h"
#include "../../genarch/interrupts/interrupts.h"
#include "../scheduler/scheduler.h"
#include "../mmu/mmu.h"

static irq_listener irq_listeners[IRQ_COUNT];
volatile uint32_t last_interrupt_source;

/**
 * Initializes the IRQ environment.
 */
void irq_init()
{
    int i = 0;
    for (i = 0; i < IRQ_COUNT; i++)
    {
        irq_listeners[i] = NULL;
    }
}

/**
 * Enables the IRQ environment
 */
void irq_enable()
{
    __enable_irq();
}

/**
 * Disables the IRQ environment
 */
void irq_disable()
{
    __disable_irq();
}

/**
 * Is called on any fast interrupt request.
 */
#pragma INTERRUPT(fiq_handle, FIQ)
interrupt void fiq_handle()
{
    int fiq = __get_fiqid();
    //printf("[FIQ] %i Invoked\n", fiq);
    __mark_interrupts();
}

void irq_dispatch()
{
    int irq = __get_irqid();
    if (irq_listeners[irq] != NULL)
    {
        irq_listeners[irq]();
    }
    __mark_interrupts();
}

/**
 * Is called on any interrupt request.
 */
#pragma INTERRUPT(irq_handle, IRQ)
#pragma TASK(irq_handle)
interrupt void irq_handle()
{
    asm(" SUB R14, R14, #4"); // calculate address where we come from
    asm(" STMFD R13!, {R12, R14}"); // store R12 and R14 on stack (R12 in case of tramping)
    __context_save();
    asm(" LDMFD R13!, {R12, R14}"); // restore R12 and R14 from stack

    irq_dispatch();

    process_t* proc = scheduler_current_process(global_scheduler);
    if(proc != NULL)
    {
        mmu_switch_to_process(proc);
    }

    __context_load();
}

/**
 * Is called on any undefined error which caused an abort
 */
#pragma INTERRUPT(udef_handle, UDEF)
interrupt void udef_handle()
{
    printf("Undefined Error occured\n");
}

/**
 * Is called on any prefetch abort.
 */
#pragma INTERRUPT(pabt_handle, PABT)
interrupt void pabt_handle()
{
    asm(" SUB R14, R14, #4"); // calculate address where we come from
    asm(" STMFD R13!, {R12, R14}"); // store R12 and R14 on stack (R12 in case of tramping)
    __context_save();
    asm(" LDMFD R13!, {R12, R14}"); // restore R12 and R14 from stack

    if(!mmu_handle_prefetch_abort())
    {
        scheduler_run(global_scheduler);
    }

    process_t* proc = scheduler_current_process(global_scheduler);
    if(proc != NULL)
    {
        mmu_switch_to_process(proc);
    }

    __context_load();
}

/**
 * Is called on any data abort.
 */
#pragma INTERRUPT(dabt_handle, DABT)
interrupt void dabt_handle()
{
    asm(" SUB R14, R14, #8");
    asm(" STMFD R13!, {R12, R14}");
    __context_save();
    asm(" LDMFD R13!, {R12, R14}");

    if(!mmu_handle_data_abort())
    {
        scheduler_run(global_scheduler);
    }

    process_t* proc = scheduler_current_process(global_scheduler);
    if(proc != NULL)
    {
        mmu_switch_to_process(proc);
    }


    __context_load();
}

/**
 * Registers a new listener to an IRQ.
 * @param irq the irq to listen on
 * @param listener the listener function to call upon irq.
 */
void irq_add_listener(uint32_t irq, irq_listener listener)
{
    if (irq >= IRQ_COUNT)
        return;

    irq_listeners[irq] = listener;
    __enable_irqid(irq);
}
