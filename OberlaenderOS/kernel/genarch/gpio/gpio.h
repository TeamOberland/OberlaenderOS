/*
 * gpio.h
 *  This file defines the platform specific API signatures
 *
 *  Created on: 21.03.2013
 *      Author: Daniel
 */

#ifndef GPIO_GENARCH_H_
#define GPIO_GENARCH_H_

#include "../../types.h"
#include "../../errno.h"

/**
 * Gets a value indicating whether the given GPIO is valid
 * @param gpio the gpio to check
 * @return true if the value is valid, otherwise false
 */
bool_t __gpio_isvalid(uint32_t gpio);

/**
 * Configures the specified gpio pin to be an input
 * @param gpio the gpio pin to configure
 * @return the success or error code.
 */
int32_t __gpio_direction_input(uint32_t gpio);

/**
 * Configures the specified gpio pin to be an output
 * @param gpio the gpio pin to configure
 * @return the success or error code.
 */
int32_t __gpio_direction_output(uint32_t gpio);


/*
 * GPIO Access
 */

/**
 * Reads the current value from the specified gpio pin.
 * @param gpio the number of the gpio pin to read from
 * @return the current value stored at the specified gpio pin
 */
int32_t __gpio_get_value(uint32_t gpio);


/**
 * Reads the current value from the specified gpio pin.
 * @param gpio the number of the gpio pin to read from
 * @param value the value to store at the specified gpio pin
 */
void __gpio_set_value(uint32_t gpio, uint32_t value);



#endif /* GPIO_GENARCH_H_ */
