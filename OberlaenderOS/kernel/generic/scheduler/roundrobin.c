/*
 * roundrobin.c
 *
 *  Created on: 20.05.2013
 *      Author: Daniel
 */

#include "scheduler.h"
#include "../../../lib/list.h"
#include "../../../lib/types.h"

void scheduling_algorithm_round_robin(scheduler_t* scheduler)
{
    if (list_empty(scheduler->processes))
        return;

    // load current process
    node_t* currentProcess = scheduler->currentProcess;
    if (currentProcess == NULL)
    {
        currentProcess = list_first(scheduler->processes);
    }

    node_t* processToRun = NULL;

    // search for a new node which is ready
    node_t* newProcess = node_next(currentProcess, scheduler->processes, TRUE);
    while (true)
    {
        process_t* proc = (process_t*) newProcess->member;

        // new process found
        if (proc->state == PROCESS_READY || proc->state == PROCESS_ENTERING)
        {
            processToRun = newProcess;
            break;
        }
        // if we reached the current process again
        else if (currentProcess == newProcess)
        {
            //  we check if it can be run again
            if (proc->state == PROCESS_RUNNING || proc->state == PROCESS_ENTERING || proc->state == PROCESS_READY)
            {
                processToRun = newProcess;
            }
            // if not, we couldn't find a new process, we run the main context again
            // NOTE: shouldn't happen as we will have an idle_task running
            else
            {
                processToRun = NULL;
            }
            break;
        }

        newProcess = node_next(newProcess, scheduler->processes, TRUE);
    }

    // let the old process wait
    if (currentProcess != NULL && ((process_t*) currentProcess->member)->state == PROCESS_RUNNING)
    {
        ((process_t*) currentProcess->member)->state = PROCESS_READY;
    }

    // enable the new process
    if (processToRun != NULL)
    {
        ((process_t*) processToRun->member)->state = PROCESS_RUNNING;
    }
    scheduler->currentProcess = processToRun;
}
