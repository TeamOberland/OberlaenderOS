/*
 * ipc.c
 *
 *  Created on: 27.05.2013
 *      Author: Daniel
 */

#include <oos/ipc.h>
#include <oos/syscalls.h>
#include <stdlib.h>

void api_ipc_register(const char* ns)
{
    syscall_data_t data;
    data.swiNumber=SYSCALL_IPC_REGISTER;
    data.arg1 = (uint32_t) ns;
    data.arg2 = 0;
    data.arg3= 0;
    data.arg4 = 0;
    data.arg5 = 0;
    syscall(&data);
}

void api_ipc_unregister(const char* ns)
{
    syscall_data_t data;
    data.swiNumber=SYSCALL_IPC_REGISTER;
    data.arg1 = (uint32_t) ns;
    data.arg2 = 0;
    data.arg3= 0;
    data.arg4 = 0;
    data.arg5 = 0;
    syscall(&data);
}

void api_ipc_send(const char* ns, ipc_message_data_t* message)
{
    syscall_data_t data;
    data.swiNumber=SYSCALL_DEVICE_WRITE;
    data.arg1 = (uint32_t) ns;
    data.arg2 =(uint32_t)message;
    data.arg3= 0;
    data.arg4 = 0;
    data.arg5 = 0;
    syscall(&data);
}

ipc_message_data_t* api_ipc_receive(const char* ns)
{
    syscall_data_t data1;
    data1.swiNumber=SYSCALL_IPC_WAIT;
    data1.arg1 = (uint32_t) ns;
    data1.arg2 =0;
    data1.arg3= 0;
    data1.arg4 = 0;
    data1.arg5 = 0;
    syscall(&data1);

    ipc_message_data_t* message = NULL;

    syscall_data_t data2;
    data2.swiNumber=SYSCALL_IPC_RECEIVE;
    data2.arg1 = (uint32_t) ns;
    data2.arg2 =(uint32_t)&message;
    data2.arg3= 0;
    data2.arg4 = 0;
    data2.arg5 = 0;
    syscall(&data2);

    return message;
}

void api_ipc_message_free(ipc_message_data_t** message)
{
    free((*message)->content);
    *message = NULL;
}
