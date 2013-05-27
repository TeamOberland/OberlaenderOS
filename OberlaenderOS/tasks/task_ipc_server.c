/*
 * task_ipc_server.c
 *
 *  Created on: 27.05.2013
 *      Author: Daniel
 */
#include "../lib/ipc.h"
#include "../lib/types.h"
#include "task_ipc.h"

void task_ipc_server(void)
{
    api_ipc_register(TASK_IPC_NS);

    while (TRUE)
    {
        printf("Reading IPC message\n");
        ipc_message_data_t* message = api_ipc_receive(TASK_IPC_NS);

        printf("MessageCode: %i\n", message->messageCode);

        api_ipc_message_free(&message);
    }

    api_ipc_unregister(TASK_IPC_NS);
}
