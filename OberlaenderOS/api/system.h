/*
 * system.h
 *
 *  Created on: 07.04.2013
 *      Author: Daniel
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_

#include "semaphore.h"

typedef struct
{
    int sec;
    int min;
    int hour;
    int mday;
    int mon;
    int year;
    int wday;
    int yday;
} timestamp_t;

timestamp_t sys_get_time();
char* sys_format_time(timestamp_t* ts);

void sys_semaphore_wait(semaphore_t* semaphore);
void sys_semaphore_notify(semaphore_t* semaphore);

#endif /* SYSTEM_H_ */
