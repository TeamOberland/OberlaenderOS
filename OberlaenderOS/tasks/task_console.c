/*
 * task_console.c
 *
 *  Created on: 04.06.2013
 *      Author: Manuel
 */




#include "../lib/syscalls.h"
#include "../lib/types.h"
#define UART_3 3

void task_console(void)
{
    device_id_t uartDevice = (2<<4)+UART_3;
    syscall(SYSCALL_DEVICE_OPEN,uartDevice,0,0);

}
