/*
 * task_gpio_led0.c
 *
 *  Created on: 28.05.2013
 *      Author: Daniel
 */


#include "../lib/types.h"
#include "../lib/gpio.h"
#include "../lib/device.h"

#define GPIO_USERLED0 149

void task_gpio_led0(void)
{
    device_id_t gpioDevice = api_gpio_export(GPIO_USERLED0, TRUE);

    device_handle_t handle = api_device_open(gpioDevice);
    if(!handle)
    {
        printf("Could not open device\n");
    }

    uint32_t i = 0;
    uint8_t value = 0;

    while (TRUE)
    {
        value ^= 0x01;
        api_device_write(handle, &value, 1);
        for (i = 0; i < 100000; i++)
            ;
    }
}
