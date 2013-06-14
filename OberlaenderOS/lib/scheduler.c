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
    syscall_data_t data;
    data.swiNumber=SYSCALL_SCHEDULER_RUN;
    data.arg1 = 0;
    data.arg2 =0;
    data.arg3= 0;
    data.arg4 = 0;
    data.arg5 = 0;
    syscall(&data);
}

