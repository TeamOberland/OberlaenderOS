/*
 * task_console.c
 *
 *  Created on: 04.06.2013
 *      Author: Manuel
 */




#include "../lib/syscalls.h"
#include "../lib/types.h"
#include "../lib/device.h"
#include <string.h>
#define UART_3 3

void task_console(void)
{
    uint8_t toRead[64];
    uint8_t index = 0;
    memset(&toRead,0,64);
    device_id_t uartDevice = api_device_build_id(DEVICE_TYPE_UART, UART_3);
    device_handle_t handle= api_device_open(uartDevice);
    api_device_write(handle,"hallo\r\n\0",8);
//    api_device_write(handle,"hallo\r\n\0",8);
//    api_device_write(handle,"hallo\r\n\0",8);
//    api_device_write(handle,"hallo\r\n\0",8);
//    api_device_write(handle,"hallo\r\n\0",8);
//    api_device_write(handle,"hallo\r\n\0",8);
//    api_device_write(handle,"hallo\r\n\0",8);
//    api_device_write(handle,"hallo\r\n\0",8);
//    api_device_write(handle,"hallo\r\n\0",8);
//    api_device_write(handle,"hallo\r\n\0",8);
    while(TRUE)
    {
        api_device_read(handle,&toRead,64);
        api_device_write(handle,&toRead,64);
    }


    api_device_close(handle);
    while(TRUE);
}
