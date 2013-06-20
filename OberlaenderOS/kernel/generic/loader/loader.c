/*
 * loader.c
 *
 *  Created on: 12.06.2013
 *      Author: Daniel
 */

#include <oos/types.h>
#include "loader.h"
#include "parser.h"
#include "parser_elf.h"
#include "parser_intel.h"
#include "../mmu/mmu.h"
#include "../mmu/mem.h"
#include "../scheduler/process.h"
#include <string.h>

bool_t elf_check(elf_header_t* header)
{
    if (header->ident.magic != ELF_MAGIC)
    {
        return FALSE;
    }
    if (header->type != ELF_ET_EXEC)
    {
        return FALSE;
    }
    // TODO: Check machine type
    if (header->ident.class != ELF_CLASS_32)
    {
        return FALSE;
    }
    if (header->ident.data != ELF_DATA_2LSB)
    {
        return FALSE;
    }
    if (header->ident.version != ELF_EV_CURRENT)
    {
        return FALSE;
    }
    return TRUE;
}

void loader_load_elf_from_data(process_t* process, uint32_t length, uint8_t* data, uint32_t* entryPoint)
{
    void* processMemory;
    uint32_t virtual;
    uint32_t physical;
    uint32_t pageCount;

    elf_header_t* header;
    elf_program_header_entry_t entry;
    uint32_t i,j;

    header = (elf_header_t*) data;

    if (elf_check(header))
    {
        //
        // Copy and Map Pages
        *entryPoint = header->entry;
        for (i = 0; i < header->phnum; i++)
        {
            // copy the header to prevent alignment problems
            memcpy(&entry, (void*)(((uint32_t) header) + header->phoff + (header->phentsize * i)), sizeof(elf_program_header_entry_t));
            if (entry.type == ELF_PT_LOAD)
            {
                // allocate pages needed for this program header
                pageCount = entry.filesz/ MMU_MASTER_TABLE_PAGE_SIZE;
                if ((entry.filesz % MMU_MASTER_TABLE_PAGE_SIZE) > 0)
                    pageCount++;
                processMemory = mem_find_free(pageCount, FALSE, TRUE);

                // copy the plain data of the program header
                memcpy(processMemory, (void*)((uint32_t)header + entry.offset), entry.filesz);

                // map the virtual addressses of the new allocated program header
                for(j = 0; j < pageCount; j++)
                {
                    virtual = (entry.vaddr + (i * MMU_MASTER_TABLE_PAGE_SIZE));
                    physical = (((uint32_t) processMemory) + (i * MMU_MASTER_TABLE_PAGE_SIZE));
                    mmu_create_address_mapping(process->masterTable,virtual, physical, 0);
                }
            }
        }
    }
}

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
