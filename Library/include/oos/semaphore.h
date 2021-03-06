/*
 * semaphore.h
 *
 *  Created on: 27.05.2013
 *      Author: Daniel
 */

#ifndef SEMAPHORE_API_H_
#define SEMAPHORE_API_H_

#include <oos/types.h>
#include <oos/list.h>

typedef struct
{
    int8_t counter;
    list_t* waitingTasks;
} semaphore_t;

semaphore_t* api_semaphore_init(void);
void api_semaphore_free(semaphore_t* semaphore);

#endif /* SEMAPHORE_H_ */
