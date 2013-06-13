
/*
 * Thread.h
 *
 *  Created on: 21.03.2013
 *      Author: Manuel
 */

#ifndef PROCESS_H_
#define PROCESS_H_

#include "../../../lib/types.h"
#include "../../genarch/arch.h"
#include "../mmu/mmu_types.h"

typedef uint8_t process_id_t;

typedef void (*process_callback_t)(void);

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
} process_state_t;


typedef struct _process
{
    process_state_t state;
    process_id_t id;
//	uint32_t priority;

    mmu_table_pointer_t masterTable;
    uint32_t pageCount; /**< how many pages (in code) does the code have */
    memory_mapped_io_t code; /**< memory address of the process code */

	DECLARE_PROCESS_CONTEXT(context)
} process_t;

#endif /* PROCESS_H_ */
