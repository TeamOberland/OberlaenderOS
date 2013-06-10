/*
 * gpio.h
 *  This file defines the high level API for GPIO acccess
 *  Created on: 21.03.2013
 *      Author: Daniel
 */

#ifndef GPIO_GENERIC_H_
#define GPIO_GENERIC_H_

#include "../../../lib/types.h"
#include "../driver/driver.h"

typedef struct {
    device_id_t (*exportGpio)(uint32_t gpio);
    int32_t (*unexportGpio)(uint32_t gpio);
} gpio_exporter_t;

/**
 * Initializes the gpio exporter which allows the GPIO system
 * to create new device nodes.
 * @param exporter
 */
void gpio_init_device_exporter(gpio_exporter_t* exporter);

/**
 * Exports the given GPIO port as device node.
 * @param gpio the gpio port to export
 * @return the device id which can be used to create a file handle.
 */
device_id_t gpio_export(uint32_t gpio);

/**
 * Removes the device node associated with the given gpio.
 * @param gpio
 * @return
 */
int32_t gpio_unexport(uint32_t gpio);

/**
 * Configures the specified gpio pin to be an input
 * @param gpio the gpio pin to configure
 * @return the success or error code.
 */
int32_t gpio_direction_input(uint32_t gpio);

/**
 * Configures the specified gpio pin to be an output
 * @param gpio the gpio pin to configure
 * @return the success or error code.
 */
int32_t gpio_direction_output(uint32_t gpio);


/*
 * GPIO Access
 */

/**
 * Reads the current value from the specified gpio pin.
 * @param gpio the number of the gpio pin to read from
 * @return the current value stored at the specified gpio pin
 */
int32_t gpio_get_value(uint32_t gpio);


/**
 * Reads the current value from the specified gpio pin.
 * @param gpio the number of the gpio pin to read from
 * @param value the value to store at the specified gpio pin
 */
void gpio_set_value(uint32_t gpio, int32_t value);


#endif /* GPIO_H_ */
