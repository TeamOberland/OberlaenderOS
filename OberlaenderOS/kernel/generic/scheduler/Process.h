#include "stdint.h"
/*
 * Thread.h
 *
 *  Created on: 21.03.2013
 *      Author: Manuel
 */

#ifndef PROCESS_H_
#define PROCESS_H_

enum process_state : uchar_t
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
};

typedef struct _process
{
	process_state state;
	ushort_t id;
	uint32_t* context;
} _process_t;

#endif /* PROCESS_H_ */
