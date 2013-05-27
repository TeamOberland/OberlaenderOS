/*
 * task_ipc_client.c
 *
 *  Created on: 27.05.2013
 *      Author: Daniel
 */
#include "../lib/ipc.h"
#include "../lib/types.h"
#include "task_ipc.h"

void task_ipc_client(void)
{
    int i = 0;

    ipc_message_data_t message;

    while(TRUE)
    {
        message.messageCode = 4711;
        message.contentSize = 0;
        api_ipc_send(TASK_IPC_NS, &message);
        for(i = 0; i < 100000; i++);
        message.messageCode = 4712;
        message.contentSize = 0;
        api_ipc_send(TASK_IPC_NS, &message);
        for(i = 0; i < 100000; i++);
    }
}
