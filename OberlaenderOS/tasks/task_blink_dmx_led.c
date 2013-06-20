/*
 * task_blink_led0.c
 *
 *  Created on: 27.05.2013
 *      Author: Daniel
 */
#include "task_blink.h"
#include <oos/types.h>
#include "../kernel/generic/io/gpio.h"
#include <oos/device.h>
#include <oos/syscalls.h>
#include <oos/device.h>
#include <oos/uart.h>
#include <oos/gpio.h>
#include <oos/device.h>
#include "stdlib.h"
#define UART_2 2
#define UART_3 3

void task_blink_dmx_led(void)
{


//    expansion header
//    1 -> 1.8V
//    2 -> 5V
//    4 -> LED uart pwm1
//    6 -> LED uart pwm2
//    10 -> LED uart pwm3
//
//    8 -> UART-RX
//
//    2 parity
//    0 stop
//
//
//    22k baudrate
//    bit manuell up setzen




    uint32_t i = 0;
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

    device_id_t uartDevice = api_device_build_id(DEVICE_TYPE_UART, UART_2);
    device_handle_t handle= api_device_open(uartDevice);
//    api_device_ioctl(handle,UART_DRIVER_INIT,(uint32_t)&uart_protocol_rs232);
    char* message = "\r\n welcome to oberlaenderOS\r\n\0";

    while(TRUE)
    {
        log_debug("x sending message");
        api_device_write(handle,message,strlen(message));
        log_debug("x message sent");
        for (i = 0; i < 10000; i++);
    }
}
