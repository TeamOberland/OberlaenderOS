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
void* current_context;


#define GPTIMER_SCHEDULER 2


void global_scheduler_context_switch()
{
    gptimer_clear(GPTIMER_SCHEDULER);
    scheduler_run(global_scheduler);
}


void scheduler_init(uint32_t speed)
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

    irq_add_listener(GPTIMER3_IRQ, global_scheduler_context_switch);

    gptimer_init(GPTIMER_SCHEDULER, speed);
    gptimer_start(GPTIMER_SCHEDULER);
}

void scheduler_add_process(scheduler_t* scheduler, process_callback_t callback)
{
    node_t* node = (node_t*) malloc(sizeof(node_t));
    node_initialize(node);

    process_t* process = (process_t*) malloc(sizeof(process_t));
    process->callback = callback;
    __context_init(process);

    node->member = (process_t*) malloc(sizeof(process_t));
}

void scheduler_run(scheduler_t* scheduler)
{
    scheduler->algorithm(scheduler);
}


void scheduler_free(scheduler_t* scheduler)
{
    // TODO: free all processes
    // TODO: free scheduler
}

