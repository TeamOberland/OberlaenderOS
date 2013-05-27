/*
 * swi.c
 *
 *  Created on: 07.04.2013
 *      Author: Daniel
 */

#include "swi.h"
#include "../../../lib/types.h"
#include "../../../lib/syscalls.h"
#include "../../../lib/ipc.h"
#include "../ipc/ipc.h"
#include "../scheduler/scheduler.h"
#include "../../genarch/scheduler/context.h"

void swi_ipc_register(const char* ns)
{
    process_t* proc = scheduler_current_process(global_scheduler);
    if(proc != NULL)
    {
        ipc_register(ns, proc->id);
    }
}

void swi_ipc_unregister(const char* ns)
{
    process_t* proc = scheduler_current_process(global_scheduler);
    if(proc != NULL)
    {
        ipc_unregister(ns, proc->id);
    }
}

void swi_ipc_send(const char* ns, ipc_message_data_t* message)
{
    process_t* proc = scheduler_current_process(global_scheduler);
    if(proc != NULL)
    {
        ipc_send(ns, proc->id, message);
    }
}

void swi_ipc_receive(const char* ns, ipc_message_data_t** message)
{
    process_t* proc = scheduler_current_process(global_scheduler);
    if(proc != NULL)
    {
        ipc_message_data_t* received = ipc_receive(ns, proc->id);
        *message = received;
    }
    else
    {
        *message = NULL;
    }
}

void swi_ipc_wait(const char* ns)
{
    process_t* proc = scheduler_current_process(global_scheduler);
    if(proc != NULL)
    {
        ipc_wait(ns, proc->id);
    }
}


void swi_scheduler_run(void)
{
    scheduler_run(global_scheduler);
}

void swi_dispatch(uint32_t swiNumber, uint32_t arg1, uint32_t arg2)
{
//    printf("[SWI] Handle %i\n", swiNumber);
    switch (swiNumber)
    {
        case SYSCALL_IPC_REGISTER:
            swi_ipc_register((const char*)arg1);
            break;
        case SYSCALL_IPC_UNREGISTER:
            swi_ipc_unregister((const char*)arg1);
            break;
        case SYSCALL_IPC_SEND:
            swi_ipc_send((const char*)arg1, (ipc_message_data_t*)arg2);
            break;
        case SYSCALL_IPC_RECEIVE:
            swi_ipc_receive((const char*)arg1, (ipc_message_data_t**)arg2);
            break;
        case SYSCALL_IPC_WAIT:
            swi_ipc_wait((const char*)arg1);
            break;
        case SYSCALL_SCHEDULER_RUN:
            swi_scheduler_run();
            break;
    }
}

#pragma INTERRUPT(swi_handle, SWI)
#pragma TASK(swi_handle)
interrupt void swi_handle(uint32_t swiNumber, uint32_t arg1, uint32_t arg2)
{
    asm(" SUB R13, R13, #4");
    asm(" STR R14, [R13]");
    __context_save();
    asm(" ADD R13, R13, #4");

    swi_dispatch(swiNumber, arg1, arg2);

    __context_load();
}
