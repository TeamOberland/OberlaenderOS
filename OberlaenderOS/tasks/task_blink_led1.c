/*
 * task_blink_led1.c
 *
 *  Created on: 27.05.2013
 *      Author: Daniel
 */
#include "task_blink.h"
#include "../lib/types.h"

void task_blink_led1(void)
{
    gpio_direction_output(GPIO_USERLED1);
    uint32_t i = 0;
    uint32_t value = 0;

    while (TRUE)
    {
        value ^= 0x01;
        gpio_set_value(GPIO_USERLED1, value);
        for (i = 0; i < 50000; i++)
            ;
    }
}
