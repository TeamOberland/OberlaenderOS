/*
 * mmu.c
 *
 *  Created on: 13.06.2013
 *      Author: Daniel
 */

#include "../../../genarch/mmu/mmu.h"

uint8_t __mmu_get_domain_access(uint8_t domain)
{
    switch(domain)
    {
        case 0:
            return 0x03;
        default:
            return 0x01;
    }
}

inline void __mmu_init(void)
{
    //
    // Initialize domain access control (we use only domain0 therefore we have 11 there)

    // CP15 is the MMU coprocessor
    asm("  MOVT  R0, #0x5555");
    // 0101 0101 0101 0100
    asm("  MOV   R0, #0x5557");
    // 0101 0101 0101 0111
    // C3 with opcode 0 and C0 configures the domain (ARM A8 TRM 3-81)
    asm("  MCR   P15, #0, R0, C3, C0, #0");
}

inline void __mmu_enable(void)
{
    // TODO: move to arch
    asm("  MRC p15, #0, r0, c1, c0, #0");
    asm("  ORR r0, r0, #0x1");
    asm("  MCR p15, #0, r0, c1, c0, #0");
}

