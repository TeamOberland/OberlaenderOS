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
                mmu_create_address_mapping_range(process->masterTable,
                        (uint32_t)entry.vaddr,
                        (uint32_t)processMemory, (uint32_t)processMemory + entry.filesz,
                        0
                );
            }
        }
    }
}

