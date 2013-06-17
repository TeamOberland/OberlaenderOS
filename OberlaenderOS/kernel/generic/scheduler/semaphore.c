/*
 * semaphore.c
 *
 *  Created on: 27.05.2013
 *      Author: Daniel
 */

#include <oos/semaphore.h>
#include "semaphore.h"
#include "scheduler.h"
#include "../../genarch/interrupts/interrupts.h"
#include <stdlib.h>

void semaphore_wait(semaphore_t* semaphore)
{
    semaphore->counter = semaphore->counter - 1;
    if(semaphore->counter < 0)
    {
        // get current process
        process_t* proc = scheduler_current_process(global_scheduler);
        // add it to the waiting queue
        node_t* procNode = malloc(sizeof(node_t));
        node_initialize(procNode);
        procNode->member = proc;
        list_append(procNode, semaphore->waitingTasks);
        // suspend current process
        scheduler_suspend(proc);
        // run scheduler
        scheduler_run(global_scheduler);
    }
}

void semaphore_notify(semaphore_t* semaphore)
{
    semaphore->counter = semaphore->counter + 1;
    if(semaphore->counter <= 0)
    {
        node_t* procNode = list_last(semaphore->waitingTasks);
        if(procNode != NULL)
        {
            process_t* proc = (process_t*)procNode->member;
            list_remove(procNode);
            // TODO: does not work,
//            free(procNode);
            scheduler_resume(proc);
        }
    }
}

