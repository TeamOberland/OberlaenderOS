/*
 * timer.h
 *
 *  Created on: 02.04.2013
 *      Author: Daniel
 */

#ifndef TIMER_GENERIC_H_
#define TIMER_GENERIC_H_

/* TODO: as soon we have IRQ implemented we need a handler here */

/* TODO: a timer abstraction to have an api for creating interval-based timers */

/**
 * Initializes a general purpose timer which is notifies as the given ticks are reached.
 * @param timer the timer to initialize
 * @return the status code
 */
int gptimer_init(uint32_t timer, int ticks, int loadTicks);

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

#endif /* TIMER_H_ */
