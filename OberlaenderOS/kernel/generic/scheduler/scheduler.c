/*
 * scheduler.c
 *
 *  Created on: 21.03.2013
 *      Author: Manuel
 */

#include "scheduler.h"
#include <stdlib.h>

#include "../../genarch/scheduler/context.h"
#include "../adt/list.h"
#include "../interrupts/irq.h"
#include "../interrupts/timer.h"

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
    if(global_scheduler != NULL)
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
    if(scheduler->currentProcess == NULL) return NULL;
    return (process_t*)(scheduler->currentProcess->member);
}

void scheduler_add_process(scheduler_t* scheduler, process_callback_t callback)
{
    irq_disable();
    __disable_interrupts();

    node_t* node = (node_t*) malloc(sizeof(node_t));
    node_initialize(node);

    process_t* process = (process_t*) malloc(sizeof(process_t));
    process->id = scheduler->nextProcessId;
    process->callback = callback;
    node->member = process;

    __context_init(process);

    scheduler->nextProcessId++;
    list_append(node,scheduler->processes);

    irq_enable();
    __enable_interrupts();
}

void scheduler_run(scheduler_t* scheduler)
{
    process_t* previous = scheduler_current_process(scheduler);
    scheduler->algorithm(scheduler);

    process_t* current = scheduler_current_process(scheduler);
    if(previous != NULL)
    {
        previous->state = PROCESS_READY;
    }

    if(current != NULL)
    {
        current_context = current->context;
        current->state = PROCESS_RUNNING;
    }
}


void scheduler_free(scheduler_t* scheduler)
{
    // TODO: free all processes
    // TODO: free scheduler
}

