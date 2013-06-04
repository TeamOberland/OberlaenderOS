/*
 * gpio_driver.c
 *
 *  Created on: 28.05.2013
 *      Author: Daniel
 */

#include "gpio_driver.h"
#include "../kernel/generic/io/gpio.h"
#include "../kernel/generic/driver/device_manager.h"

driver_t gpio_driver = {
    NULL,
    0,
    gpio_driver_init,
    gpio_driver_open,
    gpio_driver_close,
    gpio_driver_read,
    gpio_driver_write
};


/**
 * The gpio lookup which maps device ids to the according gpio number
 */
static registered_gpio_t registered_gpios[MAX_GPIO_DEVICES];

static device_id_t gpio_driver_export(uint32_t gpio, bool_t output)
{
    int i;
    int freeSlot = -1;
    // prevent duplicate exporting
    for (i = 0; i < MAX_GPIO_DEVICES; i++)
    {
        if (!registered_gpios[i].used)
        {
            freeSlot = i;
        }
        // GPIO already exported
        else if (registered_gpios[i].gpio == gpio)
        {
            return -1;
        }
    }

    if (freeSlot >= 0)
    {
        // create device info for later lookup
        registered_gpios[freeSlot].used = TRUE;
        registered_gpios[freeSlot].output = output;
        registered_gpios[freeSlot].gpio = gpio;

        // register new device node in device manager
        registered_gpios[freeSlot].device = device_manager_add_device(gpio_driver.deviceManager, &gpio_driver, &registered_gpios[freeSlot]);

        return registered_gpios[freeSlot].device;
    }
    return -1;
}

static int32_t gpio_driver_unexport(uint32_t gpio)
{
    int i;
    // prevent duplicate exporting
    for (i = 0; i < MAX_GPIO_DEVICES; i++)
    {
        if (registered_gpios[i].used && registered_gpios[i].gpio == gpio)
        {
            registered_gpios[i].used = FALSE;
            return 0;
        }
    }
    return -1;
}

static gpio_exporter_t gpio_driver_exporter = { gpio_driver_export, gpio_driver_unexport };

void gpio_driver_init(void)
{
    int i;
    gpio_init_device_exporter(&gpio_driver_exporter);
    for (i = 0; i < MAX_GPIO_DEVICES; i++)
    {
        registered_gpios[i].used = FALSE;
    }
}

static registered_gpio_t* gpio_get_registered(device_id_t device)
{
    int i;
    for (i = 0; i < MAX_GPIO_DEVICES; i++)
    {
        if (registered_gpios[i].used && registered_gpios[i].device == device)
        {
            return &registered_gpios[i];
        }
    }
    return NULL;
}

int16_t gpio_driver_open(device_id_t device)
{
    registered_gpio_t* reg = gpio_get_registered(device);
    if (reg != NULL)
    {
        if (reg->output)
        {
            gpio_direction_output(reg->gpio);
        }
        else
        {
            gpio_direction_input(reg->gpio);
        }
    }
    return 0;
}

int16_t gpio_driver_close(device_id_t device)
{
    // nothing to do
    return 0;
}

int16_t gpio_driver_read(device_id_t device, void* buffer, uint32_t count)
{
    registered_gpio_t* reg = gpio_get_registered(device);
    if (reg != NULL)
    {
        int32_t val = gpio_get_value(reg->gpio);
        *((uint8_t*)buffer) = (uint8_t) val;
        return 0;
    }
    return -1;
}

int16_t gpio_driver_write(device_id_t device, void* buffer, uint32_t count)
{
    registered_gpio_t* reg = gpio_get_registered(device);
    if (reg != NULL)
    {
        uint8_t val = *((uint8_t*)buffer);
        gpio_set_value(reg->gpio, val);
        return 0;
    }
    return -1;
}
