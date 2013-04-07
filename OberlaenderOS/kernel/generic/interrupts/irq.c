/*
 * irq.c
 *
 *  Created on: 07.04.2013
 *      Author: Daniel
 */

#include "../../types.h"
#include "irq.h"
#include "../../genarch/arch.h"
#include <stdio.h>

static irq_listener irq_listeners[IRQ_COUNT];

/**
 * Initializes the IRQ environment.
 */
void irq_init()
{
    int i = 0;
    for(i = 0; i < IRQ_COUNT; i++)
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
 * Handles any notified IRQ
 */
void irq_handle()
{
    int irq =__get_irqid();
    printf("[IRQ] %i Invoked\n", irq);
    if(irq_listeners[irq] != NULL)
    {
        printf("[IRQ] %i Handler available, calling it\n", irq);
        irq_listeners[irq]();
    }
}

/**
 * Registers a new listener to an IRQ.
 * @param irq the irq to listen on
 * @param listener the listener function to call upon irq.
 */
void irq_add_listener(uint32_t irq, irq_listener listener)
{
    if(irq >= IRQ_COUNT) return;

    irq_listeners[irq] = listener;
    __enable_irqid(irq);
}
