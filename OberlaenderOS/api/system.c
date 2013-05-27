/*
 * system.c
 *
 *  Created on: 07.04.2013
 *      Author: Daniel
 */

#include "system.h"
#include "syscalls.h"
#include "semaphore.h"

#include <stdint.h>

timestamp_t sys_get_time()
{
    timestamp_t time;

    syscall(SYSCALL_GETTIME, (uint32_t) (&time), 0);

    return time;
}

char* sys_format_time(timestamp_t* ts)
{
    static char result[26];

    syscall(SYSCALL_FORMATTIME, (uint32_t) (ts), (uint32_t) (&result));

    return result;
}

void sys_semaphore_wait(semaphore_t* semaphore)
{
    syscall(SYSCALL_SEMAPHORE_WAIT, (uint32_t) semaphore, 0);
}

void sys_semaphore_notify(semaphore_t* semaphore)
{
    syscall(SYSCALL_SEMAPHORE_NOTIFY, (uint32_t) semaphore, 0);
}
