/*
 * main_manuel.c
 *
 *  Created on: 21.03.2013
 *      Author: Manuel
 */

#include "kernel/generic/kernel.h"

#include "kernel/generic/scheduler/scheduler.h"
#include <oos/scheduler.h>
#include "kernel/generic/driver/driver.h"
#include "kernel/generic/driver/device_manager.h"

#include "driver/gpio/gpio_driver.h"
#include "driver/uart/uart_driver.h"
#include "kernel/generic/log/logger.h"
#include <oos/device.h>
#include <string.h>

extern void task_blink_led0(void);
extern void task_blink_led1(void);
extern void task_console(void);
extern void task_gpio_led0(void);

extern void task_ipc_server(void);
extern void task_ipc_client(void);
extern void task_blink_dmx_led(void);



void manuel_setup_device_manager()
{
    global_device_manager = device_manager_init();

    // load drivers
    device_manager_register_driver(global_device_manager, &gpio_driver);
    device_manager_register_driver(global_device_manager, &uart_driver);
}


void dmx_sending_signal()
{
//    device_id_t uart_pin11 = gpio_export(135);
    device_id_t uart_pin6 = gpio_export(146);
//    device_handle_t uart_pin11_handle = device_open(global_device_manager,uart_pin11);
    device_handle_t uart_pin6_handle = device_open(global_device_manager,uart_pin6);
//
//    device_ioctl(global_device_manager,uart_pin11_handle, GPIO_DRV_IOCTL_SET_DIR, GPIO_DRV_IOCTL_DIR_OUT);
    device_ioctl(global_device_manager,uart_pin6_handle, GPIO_DRV_IOCTL_SET_DIR, GPIO_DRV_IOCTL_DIR_OUT);
//
//    device_ioctl(global_device_manager,uart_pin11_handle, GPIO_DRV_IOCTL_SET_EXPPIN_MODE, 0);
    device_ioctl(global_device_manager,uart_pin6_handle, GPIO_DRV_IOCTL_SET_EXPPIN_MODE, 0);
//
    uint8_t value = 1;
//    device_write(global_device_manager,uart_pin11_handle, &value, 1);
    device_write(global_device_manager,uart_pin6_handle, &value, 1);
    int i = 0;
//
//    while(TRUE)
//    {
//        value^=1;
//        device_write(global_device_manager,uart_pin11_handle, &value, 1);
//        device_write(global_device_manager,uart_pin6_handle, &value, 1);
//        for (i = 0; i < 1000000; i++);
//    }

    device_id_t uartDevice = api_device_build_id(DEVICE_TYPE_UART, 2);
    device_handle_t handle= device_open(global_device_manager,uartDevice);
    device_ioctl(global_device_manager,handle,UART_DRIVER_INIT,(uint32_t)&uart_protocol_rs232);
    char* message = "\r\n welcome to oberlaenderOS\r\n\0";

    while(TRUE)
    {
        device_write(global_device_manager,handle,message,strlen(message));
        for (i = 0; i < 100000; i++);
    }


}


uint32_t saved_R14;
void main_manuel(void)
{
    saved_R14=0;
    printf("Setup kernel\n");
    setup_kernel();
    manuel_setup_device_manager();
    loggerInit();

    log_debug("\r\n\r\nSystem init...");

    dmx_sending_signal();

//    __enable_interrupts();
//    __switch_to_user_mode();

//    scheduler_add_process(global_scheduler, task_blink_led0);
//    scheduler_add_process(global_scheduler, task_blink_led1);
//    scheduler_add_process(global_scheduler, task_gpio_led0);
//    scheduler_add_process(global_scheduler, task_blink_dmx_led);
//    scheduler_add_process(global_scheduler, task_console);
//    scheduler_add_process(global_scheduler, task_ipc_server);
//    scheduler_add_process(global_scheduler, task_ipc_client);
    //scheduler_start(10000000);
    //api_scheduler_run();

    /* led_test1(); */

    /* timer_test(); */

    /* gptimer_test(); */

    /* swi_test();*/

    /* ipc_test(); */

    /* display_test(); */
}


