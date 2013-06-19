/*
 * interrupts.h
 *
 *  Created on: 02.04.2013
 *      Author: Daniel
 */

#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

#include <oos/types.h>

/**
 * Enables global interrupts on the system.
 */
void __enable_interrupts();

/**
 * Disables global interrupts on the system.
 */
void __disable_interrupts();


/**
 * Enables IRQ.
 */
void __enable_irq();

/**
 * Disables IRQ.
 */
void __disable_irq();

/**
 * Gets the current IRQ id if in IRQ mode.
 */
uint32_t __get_irqid();


/**
 * Gets the current FIQ id if in FIQ mode.
 */
uint32_t __get_fiqid();

/**
 * Mark the interrupts as handled
 */
void __mark_interrupts();

/**
 * enables the interrupts of a specific irq
 * @param irq the irq id
 */
void __enable_irqid(uint32_t irq);

#endif /* INTERRUPTS_H_ */
