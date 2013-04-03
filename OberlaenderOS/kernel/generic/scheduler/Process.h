
/*
 * Thread.h
 *
 *  Created on: 21.03.2013
 *      Author: Manuel
 */

#ifndef PROCESS_H_
#define PROCESS_H_
#include "../../types.h"

typedef void (*callback_function)(void);

typedef enum process_state
{
	//Process is put to the scheduler
	PROCESS_ENTERING,
	//Process is currently running
	PROCESS_RUNNING,
	//Process is preemted by the scheduler and can be run again
	PROCESS_READY,
	//Process is waiting for wake up
	PROCESS_SLEEPING,
	//Process will be stopped
	PROCESS_EXITING
}process_state_t;

typedef struct _process
{
    process_state_t state;
	uint32_t id;
	uint32_t priority;
	uint32_t* context;
	callback_function execute_test;
} process_t;

#endif /* PROCESS_H_ */
