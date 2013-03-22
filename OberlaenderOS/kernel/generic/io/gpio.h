/*
 * gpio.h
 *  This file defines the high level API for GPIO acccess
 *  Created on: 21.03.2013
 *      Author: Daniel
 */

#ifndef GPIO_GENERIC_H_
#define GPIO_GENERIC_H_

#include "../../types.h"

/**
 * Configures the specified gpio pin to be an input
 * @param gpio the gpio pin to configure
 * @return the success or error code.
 */
extern int32_t gpio_direction_input(uint32_t gpio);

/**
 * Configures the specified gpio pin to be an output
 * @param gpio the gpio pin to configure
 * @return the success or error code.
 */
extern int32_t gpio_direction_output(uint32_t gpio);


/*
 * GPIO Access
 */

/**
 * Reads the current value from the specified gpio pin.
 * @param gpio the number of the gpio pin to read from
 * @return the current value stored at the specified gpio pin
 */
extern int32_t gpio_get_value(uint32_t gpio);


/**
 * Reads the current value from the specified gpio pin.
 * @param gpio the number of the gpio pin to read from
 * @param value the value to store at the specified gpio pin
 */
extern void gpio_set_value(uint32_t gpio, uint32_t value);


#endif /* GPIO_H_ */
