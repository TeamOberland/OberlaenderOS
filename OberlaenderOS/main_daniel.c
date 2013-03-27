/*
 * main_daniel.c
 *
 *  Created on: 21.03.2013
 *      Author: Daniel
 */
#ifdef Daniel

#include "kernel/generic/io/gpio.h"

/* beagleboard specific gpio pins */
#define GPIO_USERLED0 149
#define GPIO_USERLED1 150
#define GPIO_MMC1_WP 23
#define GPIO_DVI 170
#define GPIO_USERBUTTON 7


void main_daniel(void)
{
    gpio_direction_output(GPIO_USERLED0);
    gpio_direction_output(GPIO_USERLED1);

    int i, led0 = 0, led1 = 1;
    while(1)
    {
        for(i = 0; i < 300000; i++);

        gpio_set_value(GPIO_USERLED0, led0);
        gpio_set_value(GPIO_USERLED1, led1);

        led0 ^= 1;
        led1 ^= 1;
    }
}
#endif
