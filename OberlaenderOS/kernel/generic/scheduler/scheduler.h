/*
 * scheduler.h
 *
 *  Created on: 27.03.2013
 *      Author: Manuel
 */

#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include "../../../lib/types.h"
#include "../../../lib/list.h"
#include "process.h"
#include "scheduler.h"




struct _scheduler;
typedef void (*scheduler_algorithm)(struct _scheduler* scheduler);

#ifdef SCHEDULER_ROUND_ROBIN
#define SCHEDULING_ALGORITHM scheduling_algorithm_round_robin
#else
#error Scheduling Algorithm not specified
#endif


typedef struct _scheduler
{
    process_id_t nextProcessId;

    list_t* processes;
    node_t* currentProcess;

    scheduler_algorithm algorithm;
} scheduler_t;

void SCHEDULING_ALGORITHM(scheduler_t* scheduler);


extern scheduler_t* global_scheduler;

void scheduler_init();

void scheduler_start(uint32_t speed);

process_t* scheduler_current_process(scheduler_t* scheduler);

//void scheduler_add_process(scheduler_t* scheduler, process_callback_t callback);
void scheduler_add_process_from_intel_hex(scheduler_t* scheduler, const char* data);

void scheduler_run(scheduler_t* scheduler);

void scheduler_free(scheduler_t* scheduler);

void scheduler_suspend(process_t* process);
void scheduler_resume(process_t* process);

void scheduler_kill_current(scheduler_t* scheduler);

#endif /* SCHEDULER_H_ */
