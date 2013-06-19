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
#include "kernel/genarch/io/expansion.h"
#include "lib/logger.h"
#include "lib/device.h"
#include <string.h>

extern void task_blink_led0(void);
extern void task_blink_led1(void);
extern void task_console(void);
extern void task_gpio_led0(void);

extern void task_ipc_server(void);
extern void task_ipc_client(void);
extern void task_blink_dmx_led(void);



void setup_device_manager()
{
    global_device_manager = device_manager_init();

    // load drivers
    device_manager_register_driver(global_device_manager, &gpio_driver);
    device_manager_register_driver(global_device_manager, &uart_driver);
}

void dmx_wait(uint32_t bits)
{
    while(bits--)
    {
    }
}


void dmx_sending_signal()
{
    int i,a;
    i=a=0;
    uint8_t channels[6];
    device_id_t uart_pin11 = gpio_export(135);
    device_id_t uart_pin6 = gpio_export(146);
    device_handle_t uart_pin11_handle = device_open(global_device_manager,uart_pin11);
     device_handle_t uart_pin6_handle = device_open(global_device_manager,uart_pin6);
//
    device_ioctl(global_device_manager,uart_pin11_handle, GPIO_DRV_IOCTL_SET_DIR, GPIO_DRV_IOCTL_DIR_OUT);
    device_ioctl(global_device_manager,uart_pin6_handle, GPIO_DRV_IOCTL_SET_DIR, GPIO_DRV_IOCTL_DIR_OUT);
//
//    device_ioctl(global_device_manager,uart_pin11_handle, GPIO_DRV_IOCTL_SET_EXPPIN_MODE, 0);
//    device_ioctl(global_device_manager,uart_pin6_handle, GPIO_DRV_IOCTL_SET_EXPPIN_MODE, 0);
    __set_expansion_pin_mode(6,MODE_GPIO);
    __set_expansion_pin_mode(11,MODE_GPIO);

    uint8_t one = 1;
    uint8_t cero =0;
    device_write(global_device_manager,uart_pin11_handle, &one, 1);
    device_write(global_device_manager,uart_pin6_handle, &one, 1);

    __set_expansion_pin_mode(6,MODE_UART);
    //__set_expansion_pin_mode(11,MODE_UART);



    device_id_t uartDevice = api_device_build_id(DEVICE_TYPE_UART, 2);
    device_handle_t handle= device_open(global_device_manager,uartDevice);
    device_ioctl(global_device_manager,handle,UART_DRIVER_INIT,(uint32_t)&uart_protocol_dmx);
    __set_expansion_pin_mode(6,MODE_UART);
    while(one==1)
    {
        __set_expansion_pin_mode(6,MODE_GPIO);
        //reset
        device_write(global_device_manager,uart_pin6_handle, &cero, 1);
        a = 2400; //~204 microseconds during testing
        for(i = 0; i < a; i++);
        a = 100; //~10 microseconds
        device_write(global_device_manager,uart_pin6_handle, &one, 1);
        for(i = 0; i < a; i++);


        __set_expansion_pin_mode(6,MODE_UART);

//        //Omap3530x.pdf, modes on page 780
//        //Chosen modes: page 96 in BBSRM_latest.pdf
//        unsigned int scm_rx_tx = *((volatile unsigned int*)0x48002178);
//        scm_rx_tx &= ~0x70007;
//        scm_rx_tx |= 0;
//        scm_rx_tx |= (1 << 16);
//        *((volatile unsigned int*)0x48002178) = scm_rx_tx;
//
//        unsigned int scm_rts_cts = *((volatile unsigned int*)0x48002174);
//        scm_rts_cts &= ~0x70007;
//        scm_rts_cts |= 0;
//        scm_rts_cts |= (0 << 16);
//        *((volatile unsigned int*)0x48002174) = scm_rts_cts;


        channels[0] = 0x0;  //start byte
        channels[1] = 0x2;  //set to RGB
        channels[2] = 0;  //red
        channels[3] = 0x11;  //green
        channels[4] = 255;  //blue
        channels[5] = 0x0;  //no function - no speed


        for (i = 0; i < 6; i++) {
            device_write(global_device_manager,handle,&channels, 6);
        }

        for (i = 0; i < 100000; ++i) {

        }
    }
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


