/*
 * main_daniel.c
 *
 *  Created on: 21.03.2013
 *      Author: Daniel
 */
#ifdef Daniel

#include "kernel/generic/boot.h"
#include "kernel/generic/io/gpio.h"

#include <stdio.h>

/* beagleboard specific gpio pins */
#define GPIO_USERLED0 149
#define GPIO_USERLED1 150
#define GPIO_MMC1_WP 23
#define GPIO_DVI 170
#define GPIO_USERBUTTON 7

/**
 * A simple led GPIO test without interrupts
 */
void led_test1(void)
{
    printf("Setup GPIOs\n");
    gpio_direction_output(GPIO_USERLED0);
    gpio_direction_output(GPIO_USERLED1);
    gpio_direction_input(GPIO_USERBUTTON);

    volatile int i, led0 = 0, led1 = 1, led0Mask = 0x00, led1Mask = 0x01;

    while(1)
    {
        for(i = 0; i < 150000; i++);

        if(gpio_get_value(GPIO_USERBUTTON) == 0x01) /* if button pressed */
        {
           printf("Button Press detected, inverting LED masks\n");
           /* invert leds to blink */
           led0Mask ^= 1;
           led1Mask ^= 1;

           /* reset leds */
           led0 = led0Mask;
           led1 = led1Mask;

           /* wait for button release */
           while(gpio_get_value(GPIO_USERBUTTON) == 0x01);
        }

        gpio_set_value(GPIO_USERLED0, led0);
        gpio_set_value(GPIO_USERLED1, led1);

        led0 ^= led0Mask;
        led1 ^= led1Mask;
    }
}

void main_daniel(void)
{
    printf("Setup kernel\n");
    setup_kernel();

    led_test();

    //
}
#endif
