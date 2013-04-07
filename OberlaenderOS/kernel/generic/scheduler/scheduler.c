/*
 * scheduler.c
 *
 *  Created on: 21.03.2013
 *      Author: Manuel
 */

#ifndef SCHEDULER_C_
#define SCHEDULER_C_


#include "scheduler.h"


/*
 * Initializes the scheduler, reserving place for queue etc.
 */
scheduler_t* scheduler_init(schedulingAlgorithm_t* algorithm)
{
    scheduler_t* scheduler = (scheduler_t*)malloc(sizeof(scheduler_t));
    scheduler->processList= (list_t*) malloc(sizeof(list_t));
    scheduler->schedulingAlgorithm=algorithm;
    algorithm->processList=scheduler->processList;
    init_list(scheduler->processList);

    return scheduler;
}

void scheduler_start_scheduling(scheduler_t* scheduler)
{
    while(TRUE)
    {
        scheduler->schedulingAlgorithm->get_next_process(scheduler->schedulingAlgorithm)->execute_test();
    }
}

void scheduler_add_Process(scheduler_t* scheduler,uint32_t* context)
{
    node_t* node = (node_t*)malloc(sizeof(node_t));
    node_initialize(node);
    node->member = (process_t*)malloc(sizeof(process_t));
    ((process_t*)node->member)->context=context;
    list_append(node,scheduler->processList);
}

void scheduler_add_Process_Test(scheduler_t* scheduler,callback_function execute_test)
{
    node_t* node = (node_t*)malloc(sizeof(node_t));
    node_initialize(node);
    node->member = (process_t*)malloc(sizeof(process_t));
    ((process_t*)node->member)->execute_test=execute_test;
    ((process_t*)node->member)->id=list_count(scheduler->processList);
    list_append(node,scheduler->processList);

}

/*
 * Releases all the needed memory,
 */
void scheduler_destroy(scheduler_t* scheduler)
{

}


#endif /* SCHEDULER_C_ */
