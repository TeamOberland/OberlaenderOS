/*
 * mem.c
 *
 *  Created on: 13.06.2013
 *      Author: Daniel
 */

#include "../../../genarch/mmu/mem.h"
#include <stdlib.h>

extern volatile uint32_t int_ram_user_start;
extern volatile uint32_t ext_ddr_user_start;

void __mem_init(void)
{
    memory_count = 2;
    memories = malloc(memory_count * sizeof(mem_memory_t));

    // int_ram
    memories[0].globalStartAddress = 0x40200000;
    memories[0].globalSize = 0x00010000;
    memories[0].userStartAddress = (uint32_t)&int_ram_user_start;
    memories[0].userSize = 0x00010000;

    // ext_ram
    memories[1].globalStartAddress = 0x82000000;
    memories[1].globalSize = 0x10000000;
    memories[1].userStartAddress = (uint32_t)&ext_ddr_user_start;
    memories[1].userSize = 0x10000000;

    // interrupt vectors
    intvecs_start = 0x4020FFC0;
    intvecs_size = 0x0000003B;
}
