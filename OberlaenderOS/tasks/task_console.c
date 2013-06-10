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
    uint8_t toRead[255];
    memset(&toRead,0,255);
    uint8_t* position = &toRead[0];
    device_id_t uartDevice = (1<<4)+UART_3;
    device_handle_t handle= api_device_open(uartDevice);
    api_device_write(handle,"hallo\r\n\0",8);
    api_device_write(handle,"hallo\r\n\0",8);
    api_device_write(handle,"hallo\r\n\0",8);
    api_device_write(handle,"hallo\r\n\0",8);
    api_device_write(handle,"hallo\r\n\0",8);
    api_device_write(handle,"hallo\r\n\0",8);
    api_device_write(handle,"hallo\r\n\0",8);
    api_device_write(handle,"hallo\r\n\0",8);
    api_device_write(handle,"hallo\r\n\0",8);
    api_device_write(handle,"hallo\r\n\0",8);

    while((position!="\n"&&(position+1)!="\r")||&toRead[254]==position)
    {
        api_device_read(handle,&position,1);
        api_device_write(handle,&position,1);
        position++;
    }


    api_device_close(handle);
    while(TRUE);
}
