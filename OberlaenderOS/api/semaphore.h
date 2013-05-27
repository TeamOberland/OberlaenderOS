/*
 * semaphore.h
 *
 *  Created on: 27.05.2013
 *      Author: Daniel
 */

#ifndef SEMAPHORE_API_H_
#define SEMAPHORE_API_H_

#include "list.h"


typedef struct {
    int8_t counter;
    list_t* waitingTasks;
} semaphore_t;

semaphore_t* semaphore_init(void);
void semaphore_free(semaphore_t* semaphore);


#endif /* SEMAPHORE_H_ */
