/*
 * scheduler.c
 *
 *  Created on: 21.03.2013
 *      Author: Manuel
 */

#include "scheduler.h"
#include <stdlib.h>

#include "../../genarch/scheduler/context.h"
#include "../../../lib/list.h"
#include "../interrupts/irq.h"
#include "../interrupts/timer.h"
#include "../mmu/mmu.h"
#include "../loader/loader.h"

scheduler_t* global_scheduler;

// a temporary context to store the process for kernel-boot procedure
static DECLARE_PROCESS_CONTEXT(tmp_context)
void* current_context = tmp_context;

#define GPTIMER_SCHEDULER 1

void global_scheduler_context_switch()
{
    gptimer_clear(GPTIMER_SCHEDULER);
    scheduler_run(global_scheduler);
}

void scheduler_init()
{
    if (global_scheduler != NULL)
    {
        scheduler_free(global_scheduler);
    }

    scheduler_t* scheduler = (scheduler_t*) malloc(sizeof(scheduler_t));

    scheduler->processes = (list_t*) malloc(sizeof(list_t));
    init_list(scheduler->processes);

    scheduler->currentProcess = NULL;
    scheduler->algorithm = SCHEDULING_ALGORITHM;

    global_scheduler = scheduler;
}

void scheduler_start(uint32_t speed)
{
    irq_add_listener(GPTIMER2_IRQ, global_scheduler_context_switch);
    gptimer_init(GPTIMER_SCHEDULER, speed);
    gptimer_start(GPTIMER_SCHEDULER);
}

process_t* scheduler_current_process(scheduler_t* scheduler)
{
    if (scheduler->currentProcess == NULL)
        return NULL;
    return (process_t*) (scheduler->currentProcess->member);
}

void scheduler_kill_current(scheduler_t* scheduler)
{
    if (scheduler->currentProcess == NULL)
        return;

    node_t* node = scheduler->currentProcess;
    process_t* proc = (process_t*) node->member;
    list_remove(node);
    free(node);

    // TODO: cleanup the ipc stuff
    proc->state = PROCESS_EXITING;
    mmu_delete_process_memory(proc);
    free(proc);

    scheduler->currentProcess = NULL;
}

void scheduler_add_process_from_intel_hex(scheduler_t* scheduler, const char* data)
{
    irq_disable();
    __disable_interrupts();

    node_t* node = (node_t*) malloc(sizeof(node_t));
    node_initialize(node);

    process_t* process = (process_t*) malloc(sizeof(process_t));
    process->id = scheduler->nextProcessId;
    process->masterTable = mmu_create_master_table();
    node->member = process;

    __context_init(process);

    loader_load_intel_from_string(process, data);

    scheduler->nextProcessId++;
    list_append(node, scheduler->processes);

    irq_enable();
    __enable_interrupts();
}

//void scheduler_add_process(scheduler_t* scheduler, process_callback_t callback)
//{
//    irq_disable();
//    __disable_interrupts();
//
//    node_t* node = (node_t*) malloc(sizeof(node_t));
//    node_initialize(node);
//
//    process_t* process = (process_t*) malloc(sizeof(process_t));
//    process->id = scheduler->nextProcessId;
//    process->callback = callback;
//    process->masterTableAddress = mmu_create_master_table();
//    node->member = process;
//
//    __context_init(process);
//
//    scheduler->nextProcessId++;
//    list_append(node,scheduler->processes);
//
//    irq_enable();
//    __enable_interrupts();
//}

void scheduler_run(scheduler_t* scheduler)
{
    process_t* previous = scheduler_current_process(scheduler);
    scheduler->algorithm(scheduler);

    process_t* current = scheduler_current_process(scheduler);

    // let the old process wait
    if (previous != NULL && previous->state == PROCESS_RUNNING)
    {
        previous->state = PROCESS_READY;
    }

    // enable the new process
    if (current != NULL)
    {
        current_context = current->context;
        mmu_switch_to_process(current);
        current->state = PROCESS_RUNNING;
    }
    else
    {
        current_context = tmp_context; // continue with main without task (should not happen)
    }
}

void scheduler_free(scheduler_t* scheduler)
{
    // TODO: free all processes
    // TODO: free scheduler
}

void scheduler_suspend(process_t* process)
{
    if (process != NULL)
    {
        process->state = PROCESS_SLEEPING;
    }
}

void scheduler_resume(process_t* process)
{
    if (process != NULL)
    {
        process->state = PROCESS_READY;
    }
}
