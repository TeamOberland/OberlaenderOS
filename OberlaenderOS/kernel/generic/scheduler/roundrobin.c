/*
 * roundrobin.c
 *
 *  Created on: 20.05.2013
 *      Author: Daniel
 */

#include "scheduler.h"
#include "../adt/list.h"
#include "../../types.h"

void scheduling_algorithm_round_robin(scheduler_t* scheduler)
{
    if(scheduler->currentProcess == NULL)
    {
        scheduler->currentProcess = list_first(scheduler->processes);
    }
    else
    {
        node_t* current = scheduler->currentProcess;
        node_t* next = node_next(scheduler->currentProcess, scheduler->processes,TRUE);
        // try to find a new process which is ready
        while(next != NULL && ((process_t*)next->member)->state != PROCESS_READY)
        {
            next = node_next(scheduler->currentProcess, scheduler->processes,TRUE);
            // ensure we don't run in endless loops
            if(current == next)
            {
                next = NULL;
            }
        }

        scheduler->currentProcess = next;
    }
}
