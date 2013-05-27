/*
 * timer.h
 *
 *  Created on: 02.04.2013
 *      Author: Daniel
 */

#ifndef TIMER_GENERIC_H_
#define TIMER_GENERIC_H_

#include "../../../lib/types.h"
#include "../../genarch/arch.h"
#include "../../genarch/interrupts/timer.h"

/* Public Timer API */

/**
 * How many timer listeners can be registered
 */
#define TIMER_COUNT 10

/**
 * How many ticks to wait on the GPTIMER before updating all timers
 */
#define TIMER_TICKS 10

/**
 *  GPTIMER2 for our timer API
 */
#define GPTIMER_TIMER 9

/**
 * A timer wrapper for storing registered timers
 */
typedef struct  {
    /**
     * The listener function to call on interval.
     */
    irq_listener listener;
    /**
     * The tick count which need to be reached to call the listener.
     */
    int32_t targetTicks;
    /**
     * The current tick counter.
     */
    int32_t currentTicks;
} timer_t;

/**
 * Initializes the timer system.
 */
void timer_init();

/**
 * Adds a new listener to the timer system.
 * @param listener the listener function to call on timeout
 * @param ticks the tick interval
 */
void timer_add_listener(irq_listener listener, uint32_t ticks);

/**
 * Removes the given listener from the timer system.
 * @param listener the timer to remove.
 */
void timer_remove_listener(irq_listener listener);

/* General Purpose Timers */

/**
 * Initializes a general purpose timer which is notifies as the given ticks are reached.
 * @param timer the timer to initialize
 * @return the status code
 */
int gptimer_init(uint32_t timer, int ticks);

/**
 * Starts the given general purpose timer.
 * @param timer the timer to start
 * @return the status code
 */
int gptimer_start(uint32_t timer);

/**
 * Stops the given general purpose timer.
 * @param timer the timer to stops
 * @return the status code
 */
int gptimer_stop(uint32_t timer);

/**
 * Resets the given general purpose timer without stopping it.
 * @param timer the timer to reset
 * @return the status code
 */
int gptimer_reset(uint32_t timer);


/**
 * Clears the given general purpose timer.
 * @param timer the timer to clear
 * @return the status code
 */
int gptimer_clear(uint32_t timer);

/**
 * Gets and returns the current counter value of the specified timer
 * @param timer the timer to load the counter value from.
 * @return the counter value of the timer
 */
int gptimer_getcounter(uint32_t timer);

#endif /* TIMER_H_ */
