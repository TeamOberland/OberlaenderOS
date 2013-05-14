/*
 * arch.c
 *
 *  Created on: 27.03.2013
 *      Author: Daniel
 */

#include "../../types.h"
#include "../../genarch/arch.h"

#include "interrupts/timer.h"

extern void* __stack;

void setup_arch()
{
    memory_mapped_io_t reg;
    /* Enable Functional Clock of GPIO1 */
    reg = (memory_mapped_io_t)(WKUP_CM + CM_FCLKEN);
    *(reg) = (*(reg)) | (0x01 << 3);

    /* Enable Interface Clock */
    reg = (memory_mapped_io_t)(WKUP_CM + CM_ICLKEN);
    *(reg) = (*(reg)) | (0x01 << 3);
}
