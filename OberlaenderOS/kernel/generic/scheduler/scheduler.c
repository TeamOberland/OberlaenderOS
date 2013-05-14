/*
 * scheduler.c
 *
 *  Created on: 21.03.2013
 *      Author: Manuel
 */

#include "scheduler.h"
#include <stdlib.h>

#include "../interrupts/irq.h"
#include "../../arch/omap3530/interrupts/interrupts.h"
#include "../../arch/omap3530/scheduler/pcb.h"
#include "../interrupts/timer.h"

extern scheduler_t* _scheduler=NULL;

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
    _scheduler = scheduler;
    return scheduler;
}


void scheduler_start_scheduling(scheduler_t* scheduler)
{
    int i;
    _scheduler=scheduler;
    printf("Setup IRQ\n");
    irq_add_listener(GPTIMER3_IRQ, context_switch);

    printf("Starting timers\n");
    gptimer_init(2, 500); /* GPTIMER3 */
    gptimer_start(2);

    /* Check out the counter register */
    while(1)
    {
        for(i = 0; i < 10000; i++);

        printf("Counter: 0x%x\n", gptimer_getcounter(2));
    }
}

//void scheduler_add_Process(scheduler_t* scheduler,uint32_t context)
//{
//    node_t* node = (node_t*)malloc(sizeof(node_t));
//    node_initialize(node);
//    node->member = (process_t*)malloc(sizeof(process_t));
//    ((process_t*)node->member)->context=context;
//    list_append(node,scheduler->processList);
//}

void scheduler_add_Process_Test(scheduler_t* scheduler,uint32_t methodPointer)
{
    node_t* node = (node_t*)malloc(sizeof(node_t));
    node_initialize(node);
    node->member = (process_t*)malloc(sizeof(process_t));
    pcb_init(&((process_t*)node->member)->pcb);
    ((process_t*)node->member)->pcb.functionPointer = methodPointer;
    ((process_t*)node->member)->id=list_count(scheduler->processList);
    list_append(node,scheduler->processList);

}

/*
 * Releases all the needed memory,
 */
void scheduler_destroy(scheduler_t* scheduler)
{

}

