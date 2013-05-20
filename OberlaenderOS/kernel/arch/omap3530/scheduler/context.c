/*
 * context.c
 *
 *  Created on: 20.05.2013
 *      Author: Daniel
 */

#include "../../../genarch/scheduler/context.h"
#include "../../../types.h"
#include <stdlib.h>
#include <string.h>

void __context_init(process_t* process)
{
    int* stack = malloc(PROCESS_STACK_SIZE);
    if(stack != NULL)
    {
        memset(stack, 0, PROCESS_STACK_SIZE); // clear stack
        memset(process->context, 0, sizeof(process->context));

        process->context[0] = process->callback;
        process->context[14] = stack + (PROCESS_STACK_SIZE / sizeof(int*));
        process->context[16] = (void*)_get_CPSR();
    }
}
