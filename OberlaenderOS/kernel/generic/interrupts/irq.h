/*
 * irq.h
 *
 *  Created on: 02.04.2013
 *      Author: Daniel
 */

#ifndef IRQ_H_
#define IRQ_H_

#include "../../types.h"

/**
 * Initializes the IRQ environment.
 */
void irq_init();

/**
 * Enables the IRQ environment
 */
void irq_enable();

/**
 * Disables the IRQ environment
 */
void irq_disable();

/**
 * Registers a new listener to an IRQ.
 * @param irq the irq to listen on
 * @param listener the listener function to call upon irq.
 */
void irq_add_listener(uint32_t irq, irq_listener listener);

#endif /* IRQ_H_ */
