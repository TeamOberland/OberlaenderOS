/*
 * SchedulingRoundRobin.c
 *
 *  Created on: 03.04.2013
 *      Author: Manuel
 */


#ifndef SCHEDULING_ROUND_ROBIN_C
#define SCHEDULING_ROUND_ROBIN_C
#include "SchedulingAlogirthm.h"
#include <stdlib.h>

/*
 * Initalizes the node by setting its pointers to null
 */
process_t* scheduling_algorithm_get_next_process_round_robin(schedulingAlgorithm_t* data)
{
    if(data->currentProcess==NULL)
    {
        data->currentProcessNode=list_first(data->processList);
    }
    else
    {
        data->currentProcessNode= node_next(data->currentProcessNode,data->processList);
    }
    data->currentProcess=(process_t*) data->currentProcessNode->member;
    return (process_t*)data->currentProcess;
}

schedulingAlgorithm_t* scheduling_algorithm_initialize()
{
    schedulingAlgorithm_t* algorithm = (schedulingAlgorithm_t*)malloc(sizeof(schedulingAlgorithm_t));
    algorithm->additionalInfo=NULL;
    algorithm->currentProcess=NULL;
    algorithm->get_next_process=scheduling_algorithm_get_next_process_round_robin;
    algorithm->processList=NULL;
    return algorithm;
}



#endif
