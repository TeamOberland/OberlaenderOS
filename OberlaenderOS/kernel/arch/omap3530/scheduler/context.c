/*
 * context.c
 *
 *  Created on: 20.05.2013
 *      Author: Daniel
 */

#include "../../../genarch/scheduler/context.h"
#include "../../../generic/mmu/mmu.h"
#include "../../../../lib/types.h"
#include <stdlib.h>
#include <string.h>

void __context_init(process_t* process)
{
    process->context[0] = (void*)PROCESS_CODE_START;
    process->context[14] = (void*)(PROCESS_STACK_START + PROCESS_STACK_SIZE);
    process->context[16] = (void*) _get_CPSR();
}
