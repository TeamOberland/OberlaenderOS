#include "interrupts.h"
#include "../../../generic/scheduler/scheduler.h"
#include "../../../types.h"
#include "../../../generic/scheduler/process.h"


void __enable_irqid(uint32_t irq)
{
    printf("Enabling irq %i (reg: %i, bit %i)\n", irq, irq/32, irq%32);
    *((memory_mapped_io_t)(MPU_INTC + INTCPS_MIR_CLEAR(irq/32))) |= (1 << (irq % 32));
}
