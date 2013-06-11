/*
 * task_blink_led0.c
 *
 *  Created on: 27.05.2013
 *      Author: Daniel
 */
#include "task_blink.h"
#include "../lib/types.h"
#include "../kernel/generic/io/gpio.h"
#include "../lib/syscalls.h"
#include "../lib/device.h"
#include "stdlib.h"
#define UART_2 2

void task_blink_dmx_led(void)
{
//    uint32_t i = 0;
//    uint32_t value = 0;
//    gpio_direction_output(144);
//    gpio_direction_output(145);
//    gpio_direction_output(146);
//
//    while (TRUE)
//    {
//        gpio_set_value(144,rand()%2);
//        gpio_set_value(145,rand()%2);
//        gpio_set_value(146,rand()%2);
//
//        for (i = 0; i < 1000; i++)
//            ;
//    }

    device_id_t uartDevice = (1<<4)+UART_2;
    device_handle_t handle= api_device_open(uartDevice);
    char* message = "\r\n welcome to oberlaenderOS\r\n\0";

    while(TRUE)
    api_device_write(handle,message,strlen(message));
}
