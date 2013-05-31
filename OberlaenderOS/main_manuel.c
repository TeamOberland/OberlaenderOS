/*
 * main_daniel.c
 *
 *  Created on: 21.03.2013
 *      Author: Daniel
 */

#include "kernel/generic/kernel.h"

#include "kernel/generic/scheduler/scheduler.h"
#include "lib/scheduler.h"
#include "kernel/generic/driver/driver.h"
#include "kernel/generic/driver/device_manager.h"
#include "kernel/arch/omap3530/uart/uart.h"

#include "driver/gpio_driver.h"

extern void task_blink_led0(void);
extern void task_blink_led1(void);

extern void task_ipc_server(void);
extern void task_ipc_client(void);
extern void task_blink_dmx_led(void);

void setup_device_manager()
{
    global_device_manager = device_manager_init();

    // load drivers
    device_manager_register_driver(global_device_manager, &gpio_driver);
//    device_manager_register_driver(global_device_manager, &uart_driver);
}

#define LOG(type, format) { \
        va_list arglist; \
        va_start(arglist, format); \
        log(type, format, arglist); \
        va_end(arglist); \
    }

void log(char* type, char* format, va_list arglist) {

    static char buffer[1024];
    #define LOGGER_BUFFER_SIZE sizeof(buffer)

    int l = vsnprintf(buffer, LOGGER_BUFFER_SIZE, format, arglist);

    if (l < 0 || l >= (LOGGER_BUFFER_SIZE - 3)) {
        l = (LOGGER_BUFFER_SIZE - 3);
    }
    buffer[l] = '\r';
    buffer[l + 1] = '\n';
    buffer[l + 2] = '\0';

    serial_service_write(type, strlen(type));
    serial_service_write(buffer, (l + 2));
}

void logger_debug(char* format, ...) {
    LOG("DEBUG:\t", format)
}

void main_manuel(void)
{
    printf("Setup kernel\n");
    setup_kernel();

    logger_debug("\r\n\r\nSystem init...");


    setup_device_manager();

    __enable_interrupts();
    __switch_to_user_mode();

    scheduler_add_process(global_scheduler, task_blink_led0);
    scheduler_add_process(global_scheduler, task_blink_led1);
    scheduler_add_process(global_scheduler, task_blink_dmx_led);
//    scheduler_add_process(global_scheduler, task_ipc_server);
//    scheduler_add_process(global_scheduler, task_ipc_client);
    scheduler_start(30);
    api_scheduler_run();

    /* led_test1(); */

    /* timer_test(); */

    /* gptimer_test(); */

    /* swi_test();*/

    /* ipc_test(); */

    /* display_test(); */
}


