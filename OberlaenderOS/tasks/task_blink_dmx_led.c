/*
 * task_blink_led0.c
 *
 *  Created on: 27.05.2013
 *      Author: Daniel
 */
#include "task_blink.h"
#include "../lib/types.h"
#include "../kernel/generic/io/gpio.h"
#include "stdlib.h"

void task_blink_dmx_led(void)
{
    uint32_t i = 0;
    uint32_t value = 0;
    gpio_direction_output(144);
    gpio_direction_output(145);
    gpio_direction_output(146);

    while (TRUE)
    {
        gpio_set_value(144,rand()%2);
        gpio_set_value(145,rand()%2);
        gpio_set_value(146,rand()%2);

        for (i = 0; i < 100000; i++)
            ;
    }
}
