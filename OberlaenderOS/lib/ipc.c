/*
 * ipc.c
 *
 *  Created on: 27.05.2013
 *      Author: Daniel
 */

#include "ipc.h"
#include "syscalls.h"
#include <stdlib.h>

void api_ipc_register(const char* ns)
{
    syscall(SYSCALL_IPC_REGISTER, (uint32_t)ns, 0);
}

void api_ipc_unregister(const char* ns)
{
    syscall(SYSCALL_IPC_REGISTER, (uint32_t)ns, 0);
}

void api_ipc_send(const char* ns, ipc_message_data_t* message)
{
    syscall(SYSCALL_IPC_SEND, (uint32_t)ns, (uint32_t)message);
}

ipc_message_data_t* api_ipc_receive(const char* ns)
{
    syscall(SYSCALL_IPC_WAIT, (uint32_t)ns, 0);

    ipc_message_data_t* message = NULL;

    syscall(SYSCALL_IPC_RECEIVE, (uint32_t)ns, (uint32_t)&message);

    return message;
}

void api_ipc_message_free(ipc_message_data_t** message)
{
    free((*message)->content);
    *message = NULL;
}
