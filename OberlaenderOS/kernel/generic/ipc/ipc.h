/*
 * ipc.h
 *
 *  Created on: 07.05.2013
 *      Author: Daniel
 */

#ifndef IPC_H_
#define IPC_H_

#include "../../types.h"
#include "../adt/list.h"
#include "../scheduler/process.h"

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

/**
 * This is an IPC message. It is used
 * to send a message from one process to another.
 */
typedef struct
{
    process_id_t sender; /**< the process who sent this message */
    process_id_t receiver; /**< the process who will receive this */
    ipc_message_data_t* data; /**< the data of the ipc message */
} ipc_message_t;

/**
 * Represents a single receiver of messages within the IPC system.
 */
typedef struct
{
    process_id_t pid;
    list_t messages; /**< the list of messages which the receivers will receive on read (ipc_message_t*) */
} ipc_receiver_t;

/**
 * A IPC namespace is like a container for
 * messages. IPC clients can hook into namespaces
 * to receive messages from other processes.
 */
typedef struct
{
    const char* name; /**< the string representation of the namespace */
    list_t receivers; /**< the list of processes which whant to receive the message */
} ipc_namespace_t;

/**
 * Setups the IPC environment.
 */
void ipc_init();

/**
 * Registers a process to receive messages of a IPC namespace
 * @param ns the namespace to listen on
 * @param pid the process to add as receiver for messages
 */
void ipc_register(const char* ns, process_id_t pid);
/**
 * Unregisters a process from receiving messages.
 * @param ns the namespace to unregister from
 * @param pid the process to unregister
 */
void ipc_unregister(const char* ns, process_id_t pid);

/**
 * Untergisters a process from all his namespaces.
 * @param pid the process to unregister
 */
void ipc_unregister_all(process_id_t pid);

/**
 * Sends a message to all receivers of a namespace. This task will not block the process.
 * The message data gets copied.
 * @param ns the namespace to sent the message to
 * @param pid the process sending the message
 * @param message the message to send
 */
void ipc_send(const char* ns, process_id_t pid, ipc_message_data_t* message);

/**
 * Receives a message from a namespace. This task will block the process until a message is received.
 * @param ns the namespace to read a message from.
 * @param pid the receiver PID to load the messages for.
 * @return
 */
ipc_message_t* ipc_receive(const char* ns, process_id_t pid);

/**
 * Cleans up all resources allocated by this message
 * @param msg the message to release
 */
void ipc_free_message(ipc_message_t* msg);

#endif /* IPC_H_ */
