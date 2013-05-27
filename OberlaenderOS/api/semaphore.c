/*
 * semaphore.c
 *
 *  Created on: 27.05.2013
 *      Author: Daniel
 */

#include "list.h"
#include "semaphore.h"
#include <stdlib.h>

semaphore_t* semaphore_init(void)
{
    semaphore_t* s = malloc(sizeof(semaphore_t*));
    s->counter = 0;
    s->waitingTasks = malloc(sizeof(list_t));
    init_list(s->waitingTasks);
    return s;
}

void semaphore_free(semaphore_t* semaphore)
{
    node_t* n;
    while(!list_empty(semaphore->waitingTasks))
    {
        n = list_first(semaphore->waitingTasks);
        if(n != NULL)
        {
            list_remove(n);
            free(n);
        }
    }
    free(semaphore);
}
