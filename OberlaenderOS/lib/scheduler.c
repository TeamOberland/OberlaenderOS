/*
 * scheduler.c
 *
 *  Created on: 27.05.2013
 *      Author: Daniel
 */

#include "scheduler.h"
#include "syscalls.h"

void api_scheduler_run(void)
{
    syscall(SYSCALL_SCHEDULER_RUN, 0, 0, 0);
}

