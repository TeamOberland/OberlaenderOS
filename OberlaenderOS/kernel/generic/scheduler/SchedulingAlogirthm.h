/*
 * SchedulingAlogirthm.h
 *
 *  Created on: 03.04.2013
 *      Author: Manuel
 */

#ifndef SCHEDULINGALOGIRTHM_H_
#define SCHEDULINGALOGIRTHM_H_

#include "process.h"
#include "../adt/list.h"
#include "../../types.h"

typedef struct _schedulingAlgorithm schedulingAlgorithm_t;

typedef process_t* (*scheduling_algorithm_get_next_process)(schedulingAlgorithm_t* algorithm);

struct _schedulingAlgorithm
{
    node_t *currentProcessNode;
    process_t *currentProcess;
    list_t *processList;
    scheduling_algorithm_get_next_process get_next_process;
    void* additionalInfo;
};

schedulingAlgorithm_t* scheduling_algorithm_initialize();




#endif /* SCHEDULINGALOGIRTHM_H_ */
