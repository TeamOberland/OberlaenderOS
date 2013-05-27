/*
 * ipc.h
 *
 *  Created on: 27.05.2013
 *      Author: Daniel
 */

#ifndef IPC_API_H_
#define IPC_API_H_

#include "types.h"

/**
 * This is the data which can be sent from one process to all receivers
 * in a namespace;
 */
typedef struct
{
    uint32_t messageCode; /**< a message code for the target process to identify what to do */
    uint32_t contentSize; /**< the amount of bytes stored in the content pointer */
    void* content; /**< the pointer to the message data */
} ipc_message_data_t;

void api_ipc_register(const char* ns);
void api_ipc_unregister(const char* ns);
void api_ipc_send(const char* ns, ipc_message_data_t* message);
ipc_message_data_t* api_ipc_receive(const char* ns);
void api_ipc_message_free(ipc_message_data_t** message);

#endif /* IPC_API_H_ */
