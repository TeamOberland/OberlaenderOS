/*
 * scheduler.h
 *
 *  Created on: 27.03.2013
 *      Author: Manuel
 */

#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include "../../types.h"
#include "process.h"
#include "scheduler.h"
#include "SchedulingAlogirthm.h"
#include "../adt/list.h"

typedef struct _scheduler
{
    schedulingAlgorithm_t* schedulingAlgorithm;
    list_t* processList;
}scheduler_t;

/*
 * Initializes the scheduler, reserving place for queue etc.
 */
scheduler_t*  scheduler_init(schedulingAlgorithm_t* algorithm);

void scheduler_start_scheduling(scheduler_t* scheduler);

void scheduler_add_Process(scheduler_t* scheduler,uint32_t* context);

void scheduler_add_Process_Test(scheduler_t* scheduler,callback_function);

/*
 * Releases all the needed memory,
 */
void scheduler_destroy(scheduler_t* scheduler);


#endif /* SCHEDULER_H_ */
