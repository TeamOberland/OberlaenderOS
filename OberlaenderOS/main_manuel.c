///*
// * main_manuel.c
// *
// *  Created on: 21.03.2013
// *      Author: Daniel
// */
//
////#include "kernel/generic/adt/listHowTo.h"
//
//#include "kernel/generic/kernel.h"
//
//#include "kernel/generic/io/gpio.h"
//
//#include "kernel/generic/interrupts/irq.h"
//#include "kernel/generic/interrupts/timer.h"
//
//#include "kernel/generic/ipc/ipc.h"
//#include "kernel/generic/display/display.h"
//
//#include "kernel/generic/scheduler/scheduler.h"
//
//#include "api/system.h"
//
//#include <stdio.h>
//#include <stdlib.h>
//
//#include "kernel/arch/omap3530/arch.h"
//
///* beagleboard specific gpio pins */
//#define GPIO_USERLED0 149
//#define GPIO_USERLED1 150
//#define GPIO_MMC1_WP 23
//#define GPIO_DVI 170
//#define GPIO_USERBUTTON 7
//
//void idle_task()
//{
//    while (1)
//        ;
//}
//
///**
// * A simple led GPIO test without interrupts
// */
//void led_test1(void)
//{
//    printf("Setup GPIOs\n");
//    gpio_direction_output(GPIO_USERLED0);
//    gpio_direction_output(GPIO_USERLED1);
//    gpio_direction_input(GPIO_USERBUTTON);
//
//    volatile int i, led0 = 0, led1 = 1, led0Mask = 0x00, led1Mask = 0x01;
//
//    while (1)
//    {
//        for (i = 0; i < 150000; i++)
//            ;
//
//        if (gpio_get_value(GPIO_USERBUTTON) == 0x01) /* if button pressed */
//        {
//            printf("Button Press detected, inverting LED masks\n");
//            /* invert leds to blink */
//            led0Mask ^= 1;
//            led1Mask ^= 1;
//
//            /* reset leds */
//            led0 = led0Mask;
//            led1 = led1Mask;
//
//            /* wait for button release */
//            while (gpio_get_value(GPIO_USERBUTTON) == 0x01)
//                ;
//        }
//
//        gpio_set_value(GPIO_USERLED0, led0);
//        gpio_set_value(GPIO_USERLED1, led1);
//
//        led0 ^= led0Mask;
//        led1 ^= led1Mask;
//    }
//}
//
///* TIMER TEST */
//
//void timer_userled0()
//{
//    uint32_t value = gpio_get_value(GPIO_USERLED0) ^ 0x01;
//    gpio_set_value(GPIO_USERLED0, value);
//}
//
//void timer_userled1()
//{
//    uint32_t value = gpio_get_value(GPIO_USERLED1) ^ 0x01;
//    gpio_set_value(GPIO_USERLED1, value);
//}
//
//void timer_test()
//{
//    printf("Setup GPIOs\n");
//    gpio_direction_output(GPIO_USERLED0);
//    gpio_direction_output(GPIO_USERLED1);
//
//    printf("Init Listeners\n");
//    timer_add_listener(timer_userled0, 500);
//    timer_add_listener(timer_userled1, 1000);
//}
//
//void gptimer_test_handler()
//{
//    gptimer_clear(1);
//    uint32_t value = gpio_get_value(GPIO_USERLED0) ^ 0x01;
//    gpio_set_value(GPIO_USERLED0, value);
//}
//
///* GPTIMER TEST */
//void gptimer_test()
//{
//    gpio_direction_output(GPIO_USERLED0);
//    irq_add_listener(GPTIMER2_IRQ, gptimer_test_handler);
//
//    printf("Setup GPIOs\n");
//    gpio_direction_output(GPIO_USERLED0);
//
//    printf("Starting timers\n");
//    gptimer_init(1, 50); /* GPTIMER2 */
//    gptimer_start(1);
//
//    while (1)
//        ;
//    //{
//    //    for(i = 0; i < 500; i++);
//    //    printf("Coutner: %x\n", gptimer_getcounter(1));
//    //    printf("OCR: %i\n", *((memory_mapped_io_t)(GPTIMER2_BASE + GPTIMER_TOCR)));
//    //}
//}
//
//void swi_test()
//{
//    timestamp_t time;
//    char *strtime;
//    volatile int i = 0;
//    while (1)
//    {
//        time = sys_get_time();
//        strtime = sys_format_time(&time);
//        printf("%s", strtime);
//        for (i = 0; i < 1000; i++)
//            ;
//    }
//}
//
//void ipc_test()
//{
//    int i;
//    ipc_message_data_t test1;
//    ipc_message_data_t test2;
//    ipc_message_t* result[2];
//    int* v1;
//    float* v2;
//
//    // setup
//    ipc_init();
//    ipc_register("test", 1);
//
//    //
//    // send test messages
//
//    test1.messageCode = 4711;
//    test1.contentSize = sizeof(int);
//    v1 = malloc(sizeof(int));
//    *(v1) = 4712;
//    test1.content = v1;
//    ipc_send("test", 2, &test1);
//
//    test2.messageCode = 1234;
//    test2.contentSize = sizeof(float);
//    v2 = malloc(sizeof(float));
//    *(v2) = 12.34f;
//    test2.content = v2;
//    ipc_send("test", 2, &test2);
//
//    //
//    // receive messages
//    result[0] = ipc_receive("test", 1);
//    result[1] = ipc_receive("test", 1);
//
//    for (i = 0; i < 2; i++)
//    {
//        printf("IPC from Process %i to Process %i\n", result[i]->sender, result[i]->receiver);
//        switch (result[i]->data->messageCode)
//        {
//            case 4711:
//                printf("   [4711] %i\n", *((int*) result[i]->data->content));
//                break;
//            case 1234:
//                printf("   [1234] %f\n", *((float*) result[i]->data->content));
//                break;
//        }
//    }
//
//    ipc_free_message(result[0]);
//    ipc_free_message(result[1]);
//    free(v1);
//    free(v2);
//}
//
////void display_test()
////{
////    display_init();
////    display_setup(1024,768,32);
////
////    display_context_t *display = display_get_context();
////
////    display_set_color(255,0,0);
////    display_move_to(10,10);
////    display_fill_rect(100,100);
////}
//
//uint32_t proc1(void)
//{
//    int i = 0;
//    while (TRUE)
//    {
//        printf("process1\n");
//        for (i = 0; i < 10000; i++)
//            ;
//    }
//}
//
//uint32_t proc2(void)
//{
//    int i = 0;
//    while (TRUE)
//    {
//        printf("process2\n");
//        for (i = 0; i < 10000; i++)
//            ;
//    }
//}
//
//void scheduler_test()
//{
//    scheduler_init();
//    scheduler_add_process(global_scheduler, proc1);
//    scheduler_add_process(global_scheduler, proc2);
//    scheduler_start(1000);
//}
//
//void main_manuel(void)
//{
//    printf("Setup kernel\n");
//    setup_kernel();
//
//    __enable_interrupts();
//
//    /* led_test1(); */
//
//    /* timer_test(); */
//
//    /* gptimer_test(); */
//
//    /* swi_test(); */
//
//    /* ipc_test(); */
//
//    /* display_test(); */
//    scheduler_test();
//
//    printf("Moving to Idle\n");
//    idle_task();
//}


