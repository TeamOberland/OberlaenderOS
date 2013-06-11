/*
 * gpio.h
 *  This file defines the high level API for GPIO acccess
 *  Created on: 21.03.2013
 *      Author: Daniel
 */
#include "gpio.h"
#include "../../genarch/gpio/gpio.h"
#include "../../errno.h"
#include "../../../lib/types.h"
#include "../driver/driver.h"

static gpio_exporter_t* main_exporter = NULL;
void gpio_init_device_exporter(gpio_exporter_t* exporter)
{
    main_exporter = exporter;
}

device_id_t gpio_export(uint32_t gpio)
{
    if (main_exporter != NULL)
    {
        return main_exporter->exportGpio(gpio);
    }
    return -1;
}

int32_t gpio_unexport(uint32_t gpio)
{
    if (main_exporter != NULL)
    {
        return main_exporter->unexportGpio(gpio);
    }
    return -1;
}

/**
 * Configures the specified gpio pin to be an input
 * @param gpio the gpio pin to configure
 * @return the success or error code.
 */
int32_t gpio_direction_input(uint32_t gpio)
{
    if (!__gpio_isvalid(gpio))
    {
        // invalid gpio port
        return E_FAULT;
    }

    return __gpio_direction_input(gpio);
}

/**
 * Configures the specified gpio pin to be an output
 * @param gpio the gpio pin to configure
 * @return the success or error code.
 */
int32_t gpio_direction_output(uint32_t gpio)
{
    if (!__gpio_isvalid(gpio))
    {
        // invalid gpio port
        return E_FAULT;
    }

    return __gpio_direction_output(gpio);
}

/*
 * GPIO Access
 */

/**
 * Reads the current value from the specified gpio pin.
 * @param gpio the number of the gpio pin to read from
 * @return the current value stored at the specified gpio pin
 */
int32_t gpio_get_value(uint32_t gpio)
{
    if (!__gpio_isvalid(gpio))
    {
        return 0;
    }
    return __gpio_get_value(gpio);
}

/**
 * Reads the current value from the specified gpio pin.
 * @param gpio the number of the gpio pin to read from
 * @param value the value to store at the specified gpio pin
 */
void gpio_set_value(uint32_t gpio, int32_t value)
{
    if (!__gpio_isvalid(gpio))
    {
        return;
    }
    __gpio_set_value(gpio, value);
}
