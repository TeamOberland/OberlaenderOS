/*
 * main_manuel.c
 *
 *  Created on: 21.03.2013
 *      Author: Manuel
 */

#include "kernel/generic/kernel.h"

#include "kernel/generic/scheduler/scheduler.h"
#include "lib/scheduler.h"
#include "kernel/generic/driver/driver.h"
#include "kernel/generic/driver/device_manager.h"

#include "driver/gpio/gpio_driver.h"
#include "driver/uart/uart_driver.h"
#include "lib/device.h"
#include <string.h>

extern void task_blink_led0(void);
extern void task_blink_led1(void);
extern void task_console(void);
extern void task_gpio_led0(void);

extern void task_ipc_server(void);
extern void task_ipc_client(void);
extern void task_blink_dmx_led(void);

device_handle_t logger;

void setup_device_manager()
{
    global_device_manager = device_manager_init();

    // load drivers
    device_manager_register_driver(global_device_manager, &gpio_driver);
    device_manager_register_driver(global_device_manager, &uart_driver);
}


void loggerInit()
{
    device_id_t uartDevice = api_device_build_id(DEVICE_TYPE_UART, 3);
    logger= device_open(global_device_manager,uartDevice);
}



void log(char* type, char* buffer)
{
    char* lineFeed = "\r\n";
    device_write(global_device_manager,logger,type,strlen(type));
    device_write(global_device_manager,logger,lineFeed,strlen(lineFeed));
    device_write(global_device_manager,logger,buffer,strlen(buffer));
    device_write(global_device_manager,logger,lineFeed,strlen(lineFeed));
}

void  log_debug(char* buffer)
{
    log("debug:",  buffer);
}
uint32_t saved_R14;
void main_manuel(void)
{
    saved_R14=0;
    printf("Setup kernel\n");
    setup_kernel();
    setup_device_manager();
    loggerInit();

    log_debug("\r\n\r\nSystem init...");

    __enable_interrupts();
    __switch_to_user_mode();

//    scheduler_add_process(global_scheduler, task_blink_led0);
//    scheduler_add_process(global_scheduler, task_blink_led1);
     // scheduler_add_process(global_scheduler, task_gpio_led0);
      scheduler_add_process(global_scheduler, task_blink_dmx_led);
//      scheduler_add_process(global_scheduler, task_console);
//    scheduler_add_process(global_scheduler, task_ipc_server);
//    scheduler_add_process(global_scheduler, task_ipc_client);
    scheduler_start(10000000);
    api_scheduler_run();

    /* led_test1(); */

    /* timer_test(); */

    /* gptimer_test(); */

    /* swi_test();*/

    /* ipc_test(); */

    /* display_test(); */
}


