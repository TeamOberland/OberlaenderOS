/*
 * irq.c
 *
 *  Created on: 07.04.2013
 *      Author: Daniel
 */

#include "irq.h"
#include "../../../lib/types.h"
#include "../../genarch/scheduler/context.h"
#include "../../genarch/interrupts/interrupts.h"
#include "../scheduler/scheduler.h"

static irq_listener irq_listeners[IRQ_COUNT];

extern scheduler_t* _scheduler;

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
    asm(" SUB R14, R14, #4");
    asm(" SUB R13, R13, #4");
    asm(" STR R14, [R13]");
    __context_save();
    asm(" ADD R13, R13, #4");

    irq_dispatch();

    __context_load();
}

/**
 * Is called on any undefined error which caused an abort
 */
#pragma INTERRUPT(udef_handle, UDEF)
interrupt void udef_handle()
{
    __disable_interrupts();
    printf("Undefined Error occured\n");
}

/**
 * Is called on any prefetch abort.
 */
#pragma INTERRUPT(pabt_handle, PABT)
interrupt void pabt_handle()
{
    /* TODO: Tell MMU about prefetch abort */
    printf("Prefetch abort\n");
}

/**
 * Is called on any data abort.
 */
#pragma INTERRUPT(dabt_handle, DABT)
interrupt void dabt_handle()
{
    /* TODO: Tell MMU about data abort */
    printf("Data abort\n");
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
