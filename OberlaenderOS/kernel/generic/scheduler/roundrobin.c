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
        scheduler->currentProcess = node_next(scheduler->currentProcess, scheduler->processes,TRUE);
    }
}
