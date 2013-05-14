#include "interrupts.h"
#include "../../../generic/scheduler/scheduler.h"
#include "../../../types.h"
#include "../../../generic/scheduler/process.h"


asm(" .bss _pcb_current, 4 ");
asm(" .bss _pcb_new, 4 ");
asm(" .bss _stack_pointer_saved_context, 4 ");
asm(" .bss _stack_pointer_original, 4 ");

asm(" .global _pcb_current ");
asm(" .global _pcb_new ");
asm(" .global _stack_pointer_saved_context ");
asm(" .global _stack_pointer_original ");

asm("pcb_current .field _pcb_current, 32 ");
asm("pcb_new .field _pcb_new, 32 ");
asm("stack_pointer_saved_context .field _stack_pointer_saved_context, 32 ");
asm("stack_pointer_original .field _stack_pointer_original, 32 ");

extern int pcb_current;
extern int pcb_new;
extern int stack_pointer_saved_context;
extern int stack_pointer_original;
extern scheduler_t* _scheduler;

#define SAVE_CONTEXT_IRQ \
        asm(" SUB     R14, R14, #4            ; Put return address of the interrupted task into R14 "); \
        asm(" STMFD   R13!, {R0-R12, R14}     ; Save Process-Registers "); \
        asm(" LDR     R0, stack_pointer_saved_context");    \
        asm(" STR     R13, [R0], #0");
        //stack_pointer_original = stack_pointer_saved_context + SAVED_REGISTERS_SPACE;

#define SAVE_CONTEXT_DABT \
        asm(" SUB     R14, R14, #8"); \
        asm(" STMFD   R13!, {R0-R12, R14}     ; Save Process-Registers "); \
        asm(" LDR     R0, stack_pointer_saved_context");    \
        asm(" STR     R13, [R0], #0");
        //stack_pointer_original = stack_pointer_saved_context + SAVED_REGISTERS_SPACE;

#define SAVE_CONTEXT_PABT \
    asm(" SUB     R14, R14, #4"); \
    asm(" STMFD   R13!, {R0-R12, R14}     ; Save Process-Registers "); \
    asm(" LDR     R0, stack_pointer_saved_context");  \
    asm(" STR     R13, [R0], #0");
    //stack_pointer_original = stack_pointer_saved_context + SAVED_REGISTERS_SPACE;

#define SAVE_CONTEXT_SWI \
        asm(" STMFD   R13!, {R0-R12, R14} ; Save Process-Registers ");  \
        asm(" LDR     R0, stack_pointer_saved_context");    \
        asm(" STR     R13, [R0], #0");
        //stack_pointer_original = stack_pointer_saved_context + SAVED_REGISTERS_SPACE + SWI_PARAMETERS_SPACE;

#define RESTORE_AND_SWITCH_CONTEXT \
        asm(" LDMFD   R13!, {R0-R12, PC}^");

void context_switch() {
// reload the stack pointer of the interrupt handler to get
 // the saved context
 asm(" LDR     R13, stack_pointer_saved_context");
 asm(" LDR     R13, [R13], #0");

 int pcb_current= (int)&_scheduler->schedulingAlgorithm->currentProcess->pcb;
 int pcb_new=(int)&_scheduler->schedulingAlgorithm->get_next_process(_scheduler->schedulingAlgorithm)->pcb;

// if (process_active != PID_INVALID) {
//   if (process_table[process_active]->state == RUNNING) {
//     process_table[process_active]->state = READY;
//   }
//   // Get the TCB's of the processes to switch the context
//   pcb_old = (int) &process_table[process_active]->pcb.CPSR;
// }
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

void __enable_irqid(uint32_t irq)
{
    printf("Enabling irq %i (reg: %i, bit %i)\n", irq, irq/32, irq%32);
    *((memory_mapped_io_t)(MPU_INTC + INTCPS_MIR_CLEAR(irq/32))) |= (1 << (irq % 32));
}
