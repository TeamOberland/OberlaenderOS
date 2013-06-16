/*
 * loader.c
 *
 *  Created on: 12.06.2013
 *      Author: Daniel
 */

#include "../../../lib/types.h"
#include "loader.h"
#include "parser.h"
#include "parser_intel.h"
#include "../mmu/mmu.h"
#include "../mmu/mem.h"
#include "../scheduler/process.h"
#include <string.h>

void loader_load_intel_from_string(process_t* proc, const char* data)
{
    code_instruction_t* allInstructions = parser_intel_parse_string(data);
    uint32_t i;

    code_instruction_t* current = allInstructions;

    //
    // Determine how many pages we need for this process
    uint32_t pageStart = 0x1000;
    uint32_t pageEnd = 0;
    while (current != NULL)
    {
        uint32_t pageNumber = current->virtualAddress / MMU_MASTER_TABLE_PAGE_SIZE;
        if (pageNumber < pageStart)
        {
            pageStart = pageNumber;
        }
        if (pageNumber > pageEnd)
        {
            pageEnd = pageNumber;
        }
        current = current->next;
    }

    //
    // Allocate the neede pages and copy the code to this memory

    uint32_t pageCount = pageEnd - pageStart + 1;
    void* processMemory = mem_find_free(pageCount, FALSE, TRUE);
    proc->pageCount = pageCount;
    proc->code = processMemory;

    current = allInstructions;
    uint32_t codeAddress;
    while (current != NULL)
    {
        // copy the code to memory
        codeAddress = ((uint32_t) processMemory) + current->virtualAddress - PROCESS_CODE_START;
        memcpy((void*) codeAddress, current->bytes, current->byteCount);
        current = current->next;
    }

    //
    // Map the newly allocated pages to the processes virtual memory
    uint32_t virtual;
    uint32_t physical;
    for (i = 0; i < pageCount; i++)
    {
        virtual = (PROCESS_CODE_START + (i * MMU_MASTER_TABLE_PAGE_SIZE));
        physical = (((uint32_t) processMemory) + (i * MMU_MASTER_TABLE_PAGE_SIZE));
        mmu_create_address_mapping(proc->masterTable, virtual, physical, 0);
    }
}
