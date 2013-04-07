

/*
 * main_manuel.c
 *
 *  Created on: 21.03.2013
 *      Author: Daniel
 */


//#include "kernel/generic/adt/listHowTo.h"
#include "kernel/generic/scheduler/scheduler.h"
#include "stdio.h"
#include "kernel/generic/scheduler/SchedulingAlogirthm.h"

void process1()
{
    printf("process1");
}

void process2()
{
    printf("process2");
}


void main_manuel(void)
{
    scheduler_t* scheduler = scheduler_init(scheduling_algorithm_initialize());
    scheduler_add_Process_Test(scheduler,*process1);
    scheduler_add_Process_Test(scheduler,*process2);
    scheduler_start_scheduling(scheduler);
    scheduler_destroy(scheduler);
}


