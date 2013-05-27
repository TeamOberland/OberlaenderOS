/*
 * ipc.c
 *
 *  Created on: 07.05.2013
 *      Author: Daniel
 */

#include "ipc.h"
#include "../../../api/list.h"
#include "../../../api/system.h"
#include <stdlib.h>
#include <cstring>

static list_t ipc_namespace_list;

void ipc_init()
{
    init_list(&ipc_namespace_list);
}

static node_t* ipc_get_namespace(const char* ns)
{
    node_t* n = list_first(&ipc_namespace_list);
    while (n != NULL )
    {
        if (strcmp(((ipc_namespace_t*) n->member)->name, ns) == 0)
        {
            return n;
        }
        n = node_next(n, &ipc_namespace_list, FALSE);
    }
    return NULL ;
}

static ipc_receiver_t* ipc_get_recevier(ipc_namespace_t* namespace, process_id_t pid)
{
    node_t* r = list_first(&namespace->receivers);
    while (r != NULL )
    {
        if (((ipc_receiver_t*) r->member)->pid == pid)
        {
            return (ipc_receiver_t*) r->member;
        }
    }

    return NULL ;
}

static ipc_namespace_t* ipc_get_or_create_namespace(const char* ns)
{
    ipc_namespace_t *namespace;
    node_t* nsNode;

    nsNode = ipc_get_namespace(ns);
    if (nsNode == NULL )
    {
        // create namespace
        namespace = (ipc_namespace_t*) malloc(sizeof(ipc_namespace_t));
        namespace->name = ns;
        init_list(&namespace->receivers);

        nsNode = (node_t*) malloc(sizeof(node_t));
        node_initialize(nsNode);
        nsNode->member = namespace;
        list_append(nsNode, &ipc_namespace_list);
    }
    else
    {
        namespace = (ipc_namespace_t*) nsNode->member;
    }
    return namespace;
}

void ipc_register(const char* ns, process_id_t pid)
{
    ipc_namespace_t* namespace;
    ipc_receiver_t* receiver;
    node_t* receiverNode;

    namespace = ipc_get_or_create_namespace(ns);
    receiver = ipc_get_recevier(namespace, pid);
    if (receiver == NULL )
    {
        receiver = (ipc_receiver_t*) malloc(sizeof(ipc_receiver_t));
        receiver->pid = pid;
        init_list(&receiver->messages);

        receiverNode = (node_t*) malloc(sizeof(node_t));
        node_initialize(receiverNode);
        receiverNode->member = receiver;
        list_append(receiverNode, &namespace->receivers);
    }
}

static ipc_unregister_internal(node_t* nsNode, process_id_t pid)
{
    ipc_namespace_t* namespace;
    node_t* receiveNode;
    ipc_receiver_t* receiver;
    node_t* msgNode;

    namespace = (ipc_namespace_t*) nsNode->member;
    receiveNode = list_first(&namespace->receivers);
    while (receiveNode != NULL )
    {
        node_t* next = node_next(receiveNode, &namespace->receivers, FALSE);

        if (((ipc_receiver_t*) receiveNode->member)->pid == pid)
        {
            receiver = (ipc_receiver_t*) receiveNode->member;

            // delete all messages
            msgNode = list_first(&receiver->messages);
            while (msgNode != NULL )
            {
                ipc_free_message((ipc_message_t*) msgNode->member);
            }

            list_remove(receiveNode);
            free(receiveNode->member);
            free(receiveNode);
        }
        receiveNode = next;
    }

    if (list_empty(&namespace->receivers))
    {
        list_remove(nsNode);
        free(nsNode->member);
        free(nsNode);
    }
}

void ipc_unregister(const char* ns, process_id_t pid)
{
    node_t* namespace = ipc_get_namespace(ns);

    if (namespace != NULL )
    {
        ipc_unregister_internal(namespace, pid);
    }
}

void ipc_unregister_all(process_id_t pid)
{
    node_t* nsNode;
    node_t* nextNs;

    nsNode = list_first(&ipc_namespace_list);
    while (nsNode != NULL )
    {
        nextNs = node_next(nsNode, &ipc_namespace_list, FALSE);

        ipc_unregister_internal(nsNode, pid);
        nsNode = nextNs;
    }
}

void ipc_send(const char* ns, process_id_t sender, ipc_message_data_t* message)
{
    node_t* nsNode;
    ipc_namespace_t* namespace;
    node_t* rec;
    ipc_message_t* copy;
    node_t* copyNode;
    ipc_receiver_t* receiver;

    nsNode = ipc_get_namespace(ns);
    if (nsNode == NULL )
    {
        return;
    }

    namespace = (ipc_namespace_t*) nsNode->member;
    rec = list_first(&namespace->receivers);
    while (rec != NULL )
    {
        receiver = (ipc_receiver_t*) rec->member;

        copy = (ipc_message_t*) malloc(sizeof(ipc_message_t));
        copy->sender = sender;
        copy->receiver = receiver->pid;
        copy->data = (ipc_message_data_t*) malloc(sizeof(ipc_message_data_t));
        copy->data->messageCode = message->messageCode;
        copy->data->contentSize = message->contentSize;
        copy->data->content = malloc(message->contentSize);
        memcpy(copy->data->content, message->content, message->contentSize);

        copyNode = (node_t*) malloc(sizeof(node_t));
        node_initialize(copyNode);
        copyNode->member = copy;
        list_append(copyNode, &receiver->messages);

        sys_semaphore_notify(receiver->semaphore);

        rec = node_next(rec, &namespace->receivers, FALSE);
    }
}

ipc_message_t* ipc_receive(const char* ns, process_id_t pid)
{
    node_t* nsNode;
    ipc_namespace_t* namespace;
    ipc_receiver_t* receiver;
    ipc_message_t* copy;

    node_t* receivedNode;
    ipc_message_t* received;

    nsNode = ipc_get_namespace(ns);
    if (nsNode == NULL )
    {
        return NULL ;
    }

    namespace = (ipc_namespace_t*) nsNode->member;
    receiver = ipc_get_recevier(namespace, pid);
    if (receiver == NULL )
    {
        return NULL ;
    }

    receivedNode = list_first(&receiver->messages);
    received = NULL;

    while (receivedNode == NULL )
    {
        sys_semaphore_wait(receiver->semaphore);
        receivedNode = list_first(&receiver->messages);
    }

    received = (ipc_message_t*)receivedNode->member;

    // clone again for return
    copy = (ipc_message_t*) malloc(sizeof(ipc_message_t));
    copy->sender = received->sender;
    copy->receiver = received->receiver;
    copy->data = (ipc_message_data_t*) malloc(sizeof(ipc_message_data_t));
    copy->data->messageCode = received->data->messageCode;
    copy->data->contentSize = received->data->contentSize;
    copy->data->content = malloc(copy->data->contentSize);
    memcpy(copy->data->content, received->data->content, copy->data->contentSize);

    // remove message from list
    list_remove(receivedNode);
    ipc_free_message(received);

    return copy;
}

void ipc_free_message(ipc_message_t* msg)
{
    free(msg->data->content);
    free(msg->data);
    free(msg);
}
