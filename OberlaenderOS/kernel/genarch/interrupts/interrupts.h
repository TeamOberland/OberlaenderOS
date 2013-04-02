/*
 * interrupts.h
 *
 *  Created on: 02.04.2013
 *      Author: Daniel
 */

#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

/**
 * Enables global interrupts on the system.
 */
void enable_interrupts();

/**
 * Disables global interrupts on the system.
 */
void disable_interrupts();


/**
 * Enables IRQ.
 */
void enable_irq();

/**
 * Disables IRQ.
 */
void disable_irq();


#endif /* INTERRUPTS_H_ */
