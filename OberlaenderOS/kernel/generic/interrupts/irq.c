/*
 * irq.c
 *
 *  Created on: 07.04.2013
 *      Author: Daniel
 */

#include "../../types.h"
#include "irq.h"
#include "../../genarch/arch.h"
#include "../../genarch/interrupts/interrupts.h"
#include "../scheduler/scheduler.h"

static irq_listener irq_listeners[IRQ_COUNT];

extern int _pcb_old;
extern int _pcb_new;
extern int _stack_pointer_saved_context;
extern int _stack_pointer_original;

extern scheduler_t* _scheduler;

asm("  .global _pcb_old");
asm("  .global _pcb_new");
asm("  .global _stack_pointer_saved_context");
asm("  .global _stack_pointer_original");

void context_switch()
{
    asm(" LDR     R13, _stack_pointer_saved_context");
    asm(" LDR     R13, [R13], #0");

    process_t* currentProcess = _scheduler->schedulingAlgorithm->currentProcess;
    _pcb_old = -1;
    if (currentProcess != NULL)
    {
        if (currentProcess->state == PROCESS_RUNNING)
        {
            currentProcess->state = PROCESS_SLEEPING;
        }
        // Get the TCB's of the processes to switch the context
        _pcb_old = (int) (&currentProcess->pcb.CPSR);
    }

    process_t* newProcess = _scheduler->schedulingAlgorithm->get_next_process(_scheduler->schedulingAlgorithm);
    newProcess->state = PROCESS_RUNNING;

    _pcb_new = (int) (&newProcess->pcb.CPSR);

    if (_pcb_old != -1)
    {
        asm("  LDR  R0, _pcb_old;");
        asm("  LDR  R0, [R0], #0;");
    }
    asm("  LDR  R1, _pcb_new;");
    asm("  LDR  R1, [R1], #0;");

    if (_pcb_old != -1)
    {
        asm(" MRS     R12, SPSR;");             // CPSR of interrupted process
        asm(" STR     R12, [R0], #8;");         // store CPSR into PCB
        asm(" LDMFD   R13!, {R2, R3};");        // Reload R0/R1 from stack
        asm(" STMIA   R0!, {R2, R3};");         // Store R0/R1 to PCB, Point R0 to R2 offset of PCB
        asm(" LDMFD   R13!, {R2-R12, R14};");   // Reload remaining stack values
        asm(" STR     R14, [R0, #-12];");       // Store R14_irq, the restart adress of the process
        asm(" STMIA   R0, {R2-R14}^ ;");        // Store user R2-R14 to PCB
    }

    // restore stack pointer of interrupt
    asm("  LDR R13, _stack_pointer_original;");
    asm("  LDR R13, [R13], #0;");

    // load new process and return to it
    asm("  LDMIA R1!, {R12,R14};"); // restore CPSR
    asm("  MSR SPSR_fsxc, R12;"); // restore restart adress
    asm("  LDMIA R1, {R0-R14}^"); // Load User registers
    asm("  NOP;"); // After user-mode LDM banked registers canot be accessed immediatly

    asm("  MOVS PC, R14"); // Update return address


// scheduler_next();

// switch to active process memory
// mmu_init_memory_for_process(process_table[process_active]);

// process_table[process_active]->state = RUNNING;

// pcb_new = (int) &process_table[process_active]->pcb.CPSR;

// Load addresses of the TCB's of the Tasks to switch into R0 and R1
// if (pcb_old != PID_INVALID) {
    asm(" LDR     R0, pcb_current ;" );
    asm(" LDR     R0, [R0], #0 ;" );
// }
    asm(" LDR     R1, pcb_new ;" );
    asm(" LDR     R1, [R1], #0 ;" );

// if (pcb_old != PID_INVALID) {
    //    // reload the stack pointer of the interrupt handler to get
    //    // the saved context
    //    asm(" LDR     R13, stack_pointer_saved_context");
    //    asm(" LDR     R13, [R13], #0");

    // First store the old precess's User mode state to the PCB pointed to by R0."
    asm(" MRS     R12, SPSR             ; Get CPSR of interrupted process" );
    asm(" STR     R12, [R0], #8         ; Store CPSR to PCB, point R0 at PCB location for R0 value" );
    asm(" LDMFD   R13!, {R2, R3}        ; Reload R0/R1 of interrupted process from stack" );
    asm(" STMIA   R0!, {R2, R3}         ; Store R0/R1 values to PCB, point R0 at PCB location for R2 value" );
    asm(" LDMFD   R13!, {R2-R12, R14} ; Reload remaining stacked values" );
    asm(" STR     R14, [R0, #-12]       ; Store R14_irq, the interrupted process's restart address" );
    asm(" STMIA   R0, {R2-R14}^         ; Store user R2-R14 ");
// }

    // restore the stack pointer of the interrupt
    asm(" LDR     R13, stack_pointer_original");
    asm(" LDR     R13, [R13], #0");

    // Then load the new process's User mode state and return to it.");
    asm(" LDMIA   R1!, {R12, R14}       ; Put interrupted process's CPSR" );
    asm(" MSR     SPSR_fsxc, R12        ; and restart address in SPSR_irq and R14_irq" );
    asm(" LDMIA   R1, {R0-R14}^         ; Load user R0-R14" );
    asm(" NOP                           ; Note: cannot use banked register immediately after User mode LDM" );

    asm(" MOVS    PC, R14               ; Return to address in R14_irq, with SPSR_irq -> CPSR transfer" );
}

/**
 * Initializes the IRQ environment.
 */
void irq_init()
{
    int i = 0;
    for (i = 0; i < IRQ_COUNT; i++)
    {
        irq_listeners[i] = NULL;
    }
}

/**
 * Enables the IRQ environment
 */
void irq_enable()
{
    __enable_irq();
}

/**
 * Disables the IRQ environment
 */
void irq_disable()
{
    __disable_irq();
}

/**
 * Is called on any fast interrupt request.
 */
#pragma INTERRUPT(fiq_handle, FIQ)
interrupt void fiq_handle()
{
    int fiq = __get_fiqid();
    //printf("[FIQ] %i Invoked\n", fiq);
}

/**
 * Is called on any interrupt request.
 */
void irq_dispatch()
{
    *((memory_mapped_io_t) (MPU_INTC + INTCPS_CONTROL)) |= 0x01;
    int irq = __get_irqid();
    //printf("[IRQ] %i Invoked\n", irq);
    if (irq_listeners[irq] != NULL)
    {
        //printf("[IRQ] %i Handler available, calling it\n", irq);
        irq_listeners[irq]();
    }

    *((memory_mapped_io_t) (MPU_INTC + INTCPS_CONTROL)) |= 0x01;
}

/**
 * Is called on any undefined error which caused an abort
 */
#pragma INTERRUPT(udef_handle, UDEF)
interrupt void udef_handle()
{
    __disable_interrupts();
    printf("Undefined Error occured\n");
}

/**
 * Is called on any prefetch abort.
 */
#pragma INTERRUPT(pabt_handle, PABT)
interrupt void pabt_handle()
{
    /* TODO: Tell MMU about prefetch abort */
    printf("Prefetch abort\n");
}

/**
 * Is called on any data abort.
 */
#pragma INTERRUPT(dabt_handle, DABT)
interrupt void dabt_handle()
{
    /* TODO: Tell MMU about data abort */
    printf("Data abort\n");
}

/**
 * Registers a new listener to an IRQ.
 * @param irq the irq to listen on
 * @param listener the listener function to call upon irq.
 */
void irq_add_listener(uint32_t irq, irq_listener listener)
{
    if (irq >= IRQ_COUNT)
        return;

    irq_listeners[irq] = listener;
    __enable_irqid(irq);
}
