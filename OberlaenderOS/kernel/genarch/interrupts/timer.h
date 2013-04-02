/*
 * timer.h
 *
 *  Created on: 02.04.2013
 *      Author: Daniel
 */

#ifndef TIMER_GENARCH_H_
#define TIMER_GENARCH_H_

#include "../../types.h"

/**
 * Gets a value indicating whether the givne GPTIMER is valid.
 * @param timer the timer number
 */
bool_t __gptimer_isvalid(uint32_t timer);

/**
 * Initializes a general purpose timer which is notifies as the given ticks are reached.
 * @param timer the timer to initialize
 */
int __gptimer_init(uint32_t timer, int ticks, int loadTicks);

/**
 * Starts the given general purpose timer.
 * @param timer the timer to start
 */
int __gptimer_start(uint32_t timer);

/**
 * Stops the given general purpose timer.
 * @param timer the timer to stops
 */
int __gptimer_stop(uint32_t timer);

/**
 * Resets the given general purpose timer without stopping it.
 * @param timer the timer to reset
 */
int __gptimer_reset(uint32_t timer);


#endif /* TIMER_H_ */
