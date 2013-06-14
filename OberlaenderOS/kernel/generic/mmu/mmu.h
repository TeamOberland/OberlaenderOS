/*
 * mmu.h
 *
 *  Created on: 12.06.2013
 *      Author: Daniel
 */

#ifndef MMU_H_
#define MMU_H_

#include "../../../lib/types.h"
#include "mmu_types.h"
#include "../scheduler/process.h"

#include "../../genarch/mmu/mmu.h"
#include "../../genarch/mmu/mem.h"

//
// General
//
#define MMU_ALIGN_ADDRESS 0xFFFFC000

//
// Master Table (4 pages)
//
#define MMU_MASTER_TABLE_PAGE_SIZE 0x1000
#define MMU_MASTER_TABLE_PAGE_COUNT 4
#define MMU_MASTER_TABLE_SIZE MMU_MASTER_TABLE_PAGE_SIZE * MMU_MASTER_TABLE_PAGE_COUNT

// the upper 12 bits of a virtual address are the index of the
// L2 Pointer in the master table
#define MMU_VIRTUAL_TO_MASTER_TABLE_ENTRY(v) ((v) >> 20)
#define MMU_MASTER_TABLE_ENTRY_TO_L2_ADDRESS(e) ( (e) & ~0x7FF)

#define MMU_MAX_PROCESS_SPACE   0xFFF00000
#define MMU_SECTION_ENTRY_SIZE  0x00100000
#define MMU_SECTION_ENTRY_KERNEL_INITIAL   0x00000C12
#define MMU_CROSS_PAGE_TABLE_INITIAL_VALUE 0x00000011


//
// L2 Table
//
#define MMU_L2_PAGE_COUNT 256
#define MMU_L2_PAGE_SIZE 4
#define MMU_L2_TABLE_SIZE MMU_L2_PAGE_SIZE * MMU_L2_PAGE_COUNT

// the upper 20 bits of the physical address represent the page address
#define MMU_L2_TABLE_ENTRY_TO_PAGE(p) (((p) >> 12) << 12)
#define MMU_VIRTUAL_TO_L2_TABLE_ENTRY(v) ( (v >> 12) & 0xFF)

//
// Handler
//

#define MMU_DEBUG_EVENT 0x02
#define MMU_TRANSLATION_FAULT_SECTION 0x05
#define MMU_TRANSLATION_FAULT_PAGE 0x07

//
// Functions
//
void mmu_init(void);
void mmu_set_master_table(mmu_table_pointer_t table);
void mmu_switch_to_kernel();
void mmu_switch_to_process(process_t* process);

bool_t mmu_handle_data_abort();
bool_t mmu_handle_prefetch_abort();

mmu_table_pointer_t mmu_create_master_table(void);
void mmu_create_page_mapping(mmu_table_pointer_t masterTable, uint32_t virtualAddress, uint8_t domain);
void mmu_create_address_mapping(mmu_table_pointer_t masterTable, uint32_t virtualAddress, uint32_t physicalAddress, uint8_t domain);
mmu_table_pointer_t mmu_get_or_create_l2_table(mmu_table_pointer_t masterTable, uint32_t masterTableEntry, uint8_t domain);

bool_t mmu_is_legal(uint32_t accessedAddress, uint32_t faultState);
bool_t mmu_is_process_page(uint32_t address);
void mmu_delete_process_memory(process_t* proc);

#endif /* MMU_H_ */
