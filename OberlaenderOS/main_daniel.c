/*
 * main_daniel.c
 *
 *  Created on: 21.03.2013
 *      Author: Daniel
 */
#ifdef Daniel

#include "kernel/generic/kernel.h"

#include "kernel/generic/scheduler/scheduler.h"
#include "lib/scheduler.h"
#include "kernel/generic/driver/driver.h"
#include "kernel/generic/driver/device_manager.h"
#include "kernel/generic/io/file.h"

#include "driver/gpio/gpio_driver.h"
#include "driver/video/video_driver.h"
#include <stdlib.h>
#include <string.h>

#include "tasks/task_hello_world.h"

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

/* GPTIMER TEST */
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

//void display_test()
//{
//    display_init();
//    display_setup(1024,768,32);
//
//    display_context_t *display = display_get_context();
//
//    display_set_color(255,0,0);
//    display_move_to(10,10);
//    display_fill_rect(100,100);
//}

extern void task_blink_led0(void);
extern void task_blink_led1(void);

extern void task_ipc_server(void);
extern void task_ipc_client(void);

void setup_device_manager()
{
    global_device_manager = device_manager_init();

    // load drivers
    device_manager_register_driver(global_device_manager, &gpio_driver);
    device_manager_register_driver(global_device_manager, &video_driver);
}

//
//void file_test(void)
//{
//    api_file_dir_t dir;
//    if(!file_opendir(TEST_DIR, &dir))
//    {
//        printf("Opendir failed!\n");
//        return;
//    }
//
//    api_file_direntry_t entry;
//    file_handle_t f;
//    int32_t c;
//    char* fname;
//    while(file_readdir(&dir, &entry) == 0)
//    {
//        printf("Found file: %s\n", entry.filename);
//        printf("   Size: 0x%x", entry.size);
//        printf("~~~~ Contents\n");
//
//        fname = concat(TEST_DIR, entry.filename);
//        f = file_open(fname, "r");
//        free(fname);
//        if(!f)
//        {
//            printf("  Could not open file\n");
//        }
//        else
//        {
//            while(!file_eof(f))
//            {
//                c = file_getc(f);
//                printf("%c", c);
//                fflush(stdout);
//            }
//        }
//
//        printf("\n~~~~ Contents END\n");
//    }
//
//    file_closedir(&dir);
//}




void main_daniel(void)
{
    printf("Setup kernel\n");
    setup_kernel();

    setup_device_manager();
    mount_init();

    __enable_interrupts();
    __switch_to_user_mode();

    scheduler_add_process_from_intel_hex(global_scheduler, task_hello_world);
//    scheduler_add_process(global_scheduler, task_file);
//    scheduler_add_process(global_scheduler, task_blink_led0);
//    scheduler_add_process(global_scheduler, task_blink_led1);
//    scheduler_add_process(global_scheduler, task_ipc_server);
//    scheduler_add_process(global_scheduler, task_ipc_client);
//    scheduler_add_process(global_scheduler, task_gpio_led0);
//    scheduler_add_process(global_scheduler, task_video);
    scheduler_start(1000);
    api_scheduler_run();

//    file_test();

    /* led_test1(); */

    /* timer_test(); */

    /* gptimer_test(); */

    /* swi_test();*/

    /* ipc_test(); */

    /* display_test(); */
}
#endif
