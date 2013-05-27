/*
 * task_ipc_client.c
 *
 *  Created on: 27.05.2013
 *      Author: Daniel
 */
#include "../lib/ipc.h"
#include "../lib/types.h"
#include "../lib/scheduler.h"
#include "task_ipc.h"


void task_ipc_client(void)
{
    int i = 0;

    ipc_message_data_t message;
    gpio_direction_input(GPIO_USERBUTTON);

    api_scheduler_run(); // ensure the server is run first (just in case)

    while (TRUE)
    {
        for (i = 0; i < 150000; i++)
            ;

        if (gpio_get_value(GPIO_USERBUTTON) == 0x01)
        {
            while (gpio_get_value(GPIO_USERBUTTON) == 0x01)
                ;

            message.messageCode = 4711;
            message.contentSize = 0;
            printf("Sending Message\n");
            api_ipc_send(TASK_IPC_NS, &message);
        }
    }
}
