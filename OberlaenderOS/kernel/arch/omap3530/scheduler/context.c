/*
 * context.c
 *
 *  Created on: 20.05.2013
 *      Author: Daniel
 */

#include "../../../genarch/scheduler/context.h"
#include "../../../generic/mmu/mmu.h"
#include <oos/types.h>
#include <stdlib.h>
#include <string.h>

void __context_init(process_t* process)
{
    __context_init_with_entrypoint(process, PROCESS_CODE_START + 0x04);
}


void __context_init_with_entrypoint(process_t* process, uint32_t address)
{
    memset(process->context, 0, (PROCESS_CONTEXT_SIZE * sizeof(void*)));
    process->context[0] = (void*)address;
    process->context[14] = (void*)(PROCESS_STACK_START + PROCESS_STACK_SIZE);
    process->context[16] = (void*) _get_CPSR();
}


void __context_log(process_t* process)
{
    uint32_t address = (uint32_t)process->context[0];
    printf("Context will jump to (v: 0x%x / p: 0x%x)\n",
            address,
            mmu_virtual_to_physical(process->masterTable, address)
    );
    printf("(v: 0x%x / p: 0x%x)\n",
            0x48000000,
            mmu_virtual_to_physical(process->masterTable, 0x48000000)
    );
    printf("(v: 0x%x / p: 0x%x)\n",
            0x48200040,
            mmu_virtual_to_physical(process->masterTable, 0x48200040)
    );
    printf("(v: 0x%x / p: 0x%x)\n",
            0x49000000,
            mmu_virtual_to_physical(process->masterTable, 0x49000000)
    );
}
