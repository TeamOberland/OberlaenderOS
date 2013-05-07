/*
 * interrupts.h
 *
 *  Created on: 07.04.2013
 *      Author: Daniel
 */

#ifndef INTERRUPTS_OMAP3530_H_
#define INTERRUPTS_OMAP3530_H_

#include <stdio.h>
#include "../../../genarch/interrupts/interrupts.h"

/* Some defines platform specific defines */
#define GPTIMER1_IRQ  37
#define GPTIMER2_IRQ  38
#define GPTIMER3_IRQ  39
#define GPTIMER4_IRQ  40
#define GPTIMER5_IRQ  41
#define GPTIMER6_IRQ  42
#define GPTIMER7_IRQ  43
#define GPTIMER8_IRQ  44
#define GPTIMER9_IRQ  45
#define GPTIMER10_IRQ 46
#define GPTIMER11_IRQ 47

#define UART1_IRQ     72
#define UART2_IRQ     73
#define UART3_IRQ     74

#define MPU_INTC 0x48200000
#define MODEM_INTC 0x480C7000

#define INTCPS_REVISION         0x0000
#define INTCPS_SYSCONFIG        0x0010
#define INTCPS_SYSSTATUS        0x0014
#define INTCPS_SIR_IRQ          0x0040
#define INTCPS_SIR_FIQ          0x0044
#define INTCPS_CONTROL          0x0048
#define INTCPS_PROTECTION       0x004C
#define INTCPS_IDLE             0x0050
#define INTCPS_IRQ_PRIORITY     0x0060
#define INTCPS_FIQ_PRIORITY     0x0064
#define INTCPS_THRESHOLD        0x0068
#define INTCPS_ITR(n)           (0x0080 + (0x20 * (n)))
#define INTCPS_MIR(n)           (0x0084 + (0x20 * (n)))
#define INTCPS_MIR_CLEAR(n)     (0x0088 + (0x20 * (n)))
#define INTCPS_MIR_SET(n)       (0x008C + (0x20 * (n)))
#define INTCPS_ISR_SET(n)       (0x0090 + (0x20 * (n)))
#define INTCPS_ISR_CLEAR(n)     (0x0094 + (0x20 * (n)))
#define INTCPS_PENDING_IRQ(n)   (0x0098 + (0x20 * (n)))
#define INTCPS_PENDING_FIQ(n)   (0x009C + (0x20 * (n)))
#define INTCPS_ILR(m)           (0x0100 + (0x4 * (m)))


/* Platform implementation */
#define IRQ_COUNT     95

void inline __enable_interrupts()
{
    _enable_interrupts();
}

void inline __disable_interrupts()
{
    _disable_interrupts();
}


void inline __enable_irq()
{
    _enable_IRQ();
}

uint32_t inline __get_irqid()
{
    return *((memory_mapped_io_t)(MPU_INTC + INTCPS_SIR_IRQ));
}


uint32_t inline __get_fiqid()
{
    return *((memory_mapped_io_t)(MPU_INTC + INTCPS_SIR_FIQ));
}


void inline __disable_irq()
{
    _disable_IRQ();
}

void __enable_irqid(uint32_t irq);


#endif /* INTERRUPTS_H_ */
