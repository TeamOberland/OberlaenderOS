/*
 * main_daniel.c
 *
 *  Created on: 21.03.2013
 *      Author: Daniel
 */
#ifdef Daniel

#include "kernel/generic/kernel.h"

#include "kernel/generic/io/gpio.h"

#include "kernel/generic/interrupts/irq.h"
#include "kernel/generic/interrupts/timer.h"

#include "api/system.h"

#include <stdio.h>

#include "kernel/arch/omap3530/arch.h"

/* beagleboard specific gpio pins */
#define GPIO_USERLED0 149
#define GPIO_USERLED1 150
#define GPIO_MMC1_WP 23
#define GPIO_DVI 170
#define GPIO_USERBUTTON 7


void idle_task()
{
    while(1);
}

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


/* TIMER TEST */

void timer_userled0()
{
    uint32_t value = gpio_get_value(GPIO_USERLED0) ^ 0x01;
    gpio_set_value(GPIO_USERLED0, value);
}

void timer_userled1()
{
    uint32_t value = gpio_get_value(GPIO_USERLED1) ^ 0x01;
    gpio_set_value(GPIO_USERLED1, value);
}

void timer_test()
{
    printf("Setup GPIOs\n");
    gpio_direction_output(GPIO_USERLED0);
    gpio_direction_output(GPIO_USERLED1);

    printf("Init Listeners\n");
    timer_add_listener(timer_userled0, 500);
    timer_add_listener(timer_userled1, 1);
}


void gptimer_test_handler() {
    gptimer_clear(1);
    uint32_t value = gpio_get_value(GPIO_USERLED0) ^ 0x01;
    gpio_set_value(GPIO_USERLED0, value);
}

/* GPTIMER TEST */
void gptimer_test()
{
    int i;
    printf("Setup IRQ\n");
    gpio_direction_output(GPIO_USERLED0);
    irq_add_listener(GPTIMER2_IRQ, gptimer_test_handler);

    printf("Setup GPIOs\n");
    gpio_direction_output(GPIO_USERLED0);

    printf("Starting timers\n");
    gptimer_init(1, 50); /* GPTIMER2 */
    gptimer_start(1);

    while(1);
    //{
    //    for(i = 0; i < 500; i++);
    //    printf("Coutner: %x\n", gptimer_getcounter(1));
    //    printf("OCR: %i\n", *((memory_mapped_io_t)(GPTIMER2_BASE + GPTIMER_TOCR)));
    //}
}

void swi_test()
{
    timestamp_t time;
    char *strtime;
    volatile int i = 0;
    while(1)
    {
        time = sys_get_time();
        strtime = sys_format_time(&time);
        printf("%s", strtime);
        for(i = 0; i < 1000; i++);
    }
}


void main_daniel(void)
{
    printf("Setup kernel\n");
    setup_kernel();

    __enable_interrupts();

    /* led_test1(); */

    /* timer_test(); */

    gptimer_test();

    /* swi_test(); */

    printf("Moving to Idle\n");
    idle_task();
}
#endif
