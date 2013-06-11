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
    char toRead[64];
    memset(&toRead,0,64);
    device_id_t uartDevice = api_device_build_id(DEVICE_TYPE_UART, UART_3);
    device_handle_t handle= api_device_open(uartDevice);
    char* message = "\r\n welcome to oberlaenderOS\r\n\0";
    api_device_write(handle,message,strlen(message));
    message="possible commands are:\r\n\0";
    api_device_write(handle,message,strlen(message));
    message ="echo\r\n pwd\r\n\0";
    api_device_write(handle,message,strlen(message));
    uint8_t i = 0;

    while(TRUE)
    {
        if(i>=64)
        {
            i=0;
        }


        api_device_read(handle,&toRead[i],1);
        i++;
        //line ending
        if(toRead[i-1]==13&&toRead[i]==10)
        {
            message="trying to execute your command:\r\n\0";
            api_device_write(handle,message,strlen(message));
        }

        api_device_write(handle,&toRead[i-1],1);
    }




    api_device_close(handle);
    while(TRUE);
}
