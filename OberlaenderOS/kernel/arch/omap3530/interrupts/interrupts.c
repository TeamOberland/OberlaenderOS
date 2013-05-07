#include "interrupts.h"
#include "../../../types.h"
#include "../../../generic/scheduler/process.h"


/************** GLOBALS START **************/

asm(    "\t .bss _stack_pointer_interrupted, 4 \n" \
        "\t .bss _stack_pointer_restored, 4 \n" \
        "\t .bss _stack_pointer_kernel, 4 \n" \
        "\t .bss _return_address, 4 \n" \
        "\t .bss _function_pointer, 4 \n" \

        "\t .global _stack_pointer_interrupted \n" \
        "\t .global _stack_pointer_restored \n" \
        "\t .global _stack_pointer_kernel\n" \
        "\t .global _return_address \n" \
        "\t .global _function_pointer \n" \

        "function_pointer .field _function_pointer, 32 \n" \
        "stack_pointer_interrupted .field _stack_pointer_interrupted, 32 \n" \
        "stack_pointer_restored .field _stack_pointer_restored, 32 \n" \
        "stack_pointer_kernel .field _stack_pointer_kernel, 32 \n" \
        "return_address .field _return_address, 32");

extern int stack_pointer_kernel;
extern int stack_pointer_interrupted;
extern int stack_pointer_restored;
extern int return_address;
extern int function_pointer;



#define LIST_INITIALIZE(name) \
         list_t name = { \
                 .head = { \
                         .prev = &(name).head, \
                         .next = &(name).head \
                 } \
         }

/************** GLOBALS END **************/

/*
 *  Context Switch Routine
 *  - MUST: save stackpointer and return address before you execute this routine
 */
void contextSwitch(pcb_t* from, pcb_t* to) {




    /***************** schedule *****************/

// TODO HANDLE INTERRUPT
// TODO when starting a new process, what's the return register?

// we are now in the supervisor mode 0x13
// we must save the return address of the supervisor mode
// (lr) to return to the user process

// then we save all registers on the process stack
// then we schedule the next process

// if the scheduled process hasn't been started yet
//      start the process
// otherwise
//      restore the context of the process (registers)

// the stack frame looks like this:
// TOP OF STACK         return address
// TOP OF STACK -1      cpsr
// IN BETWEEN           r0 - r11
// BOTTOM OF STACK      r12


// store the return address
//asm("\t PUSH {r0} \n" \
//    "\t LDR r0, return_address \n" \
//    "\t STR lr, [r0] \n" \
//    "\t POP {r0}");

// to save the process context we can switch in the system
// mode, because system mode has the same stack
asm("\t CPS 0x1F");

if(from ==NULL) {

    // now save all registers inclusive CPSR
    asm("\t STMFD sp!, {r0-r12, lr} \n" \
        "\t MRS r0, cpsr \n" \
        "\t STMFD sp!, {r0}");

    // save the new return address
    asm("\t LDR r0, return_address \n" \
        "\t LDR r0, [r0] \n" \
        "\t STMFD sp!, {r0}");

    // the new stack pointer of the process has to be saved
    // to restore the process
    asm("\t LDR r0, stack_pointer_interrupted \n" \
        "\t STR sp, [r0]");

    // the register r0 to r12 and the cpsr, plus the new return address
    // are now on the process stack

    // to switch to the next process we have to switch
    // to the kernel stack and the restore the context
    asm("\t LDR sp, stack_pointer_kernel \n" \
        "\t LDR sp, [sp] \n" \
        "\t LDMFD sp!, {r0-r12}");

    // save the new stack pointer of the interrupted task
    from->stack_pointer = stack_pointer_interrupted;
}


// goto IRQ mode
asm("\t CPS 0x12");

// Determine Nr. of IRQ (e.g. GPTIMER2 is IRQ_38 --> irqNr = 38)
//int irqNr = *(INTCPS_SIR_IRQ);


// Call Global IRQ-Handler
//globalIRQHandler->callHandlerFor(irqNr);
// reset interrupt

//timer.clearPendingInterrupts(GPTIMER2);
//timer.resetInternalCounter(GPTIMER2);

// Reset IRQ output and enable new IRQ generation.
//*(INTCPS_CONTROL) |= 0x1;


// back to system mode
asm("\t CPS 0x1F");

// schedule next task

// check if the task has been started
if(to->stack_pointer == 0) {
    // the process hasn't been started yet
    // we have to start the process in the user mode
    // therefore we can't just call the function pointer
    // and we have to leave the interrupt handler correctly
    // (either with return or with the LDMFD assembler instruction

    // to start the process we simply set the return address
    // of the handler to the process start (function pointer address)

    function_pointer = to->functionPointer;

    // the new process has its own stack and we have to set
    // the stack pointer of it
    stack_pointer_interrupted = to->stack_pointer;

    // set return address to EXIT
    //return_address = (int)exitTask;

    // save the kernel context
    // TODO restore r0
    asm("\t STMFD sp!, {r0-r12} \n" \
        "\t LDR r0, stack_pointer_kernel \n" \
        "\t STR sp, [r0]");

    // load the stack pointer of the process
    asm("\t LDR sp, stack_pointer_interrupted \n" \
        "\t LDR sp, [sp]");


    asm("\t LDR r0, return_address \n " \
        "\t LDR lr, [r0]");

    // switch back to the interrupt handler
    asm("\t CPS 0x12");

    // ******************************
    // ****** INTERRUPPT STACK ******
    // ******************************

    // set the return address of the interrupt handler to the entry
    // point of the process
    asm("\t LDR lr, function_pointer \n" \
        "\t LDR lr, [lr]");

    // jump to process and leave the interrupt
    asm("\t STMFD sp!, {lr} \n" \
        "\t LDMFD sp!, {pc}^");


} else {

    // restore the context of the next process
    // to restore the context we have to switch to the
    // process stack
    // therefore we set the stack pointer of the process
    stack_pointer_restored = to->stack_pointer;

    // save the kernel context
    asm("\t STMFD sp!, {r0-r12} \n" \
        "\t LDR r0, stack_pointer_kernel \n" \
        "\t STR sp, [r0]");

    // load the stack pointer of the process
    asm("\t LDR sp, stack_pointer_restored \n" \
        "\t LDR sp, [sp]");

    // the return address is at the top of the stack so we need
    // to read it first
    asm("\t LDR r0, function_pointer \n" \
        "\t LDR r1, [sp, #0] \n" \
        "\t STR r1, [r0, #0] \n" \
        // move stack pointer to the register r0-r12
        "\t ADD sp, sp, #4");

    // now read the cpsr register
    asm("\t LDMFD sp!, {r0} \n" \
        "\t MSR SPSR_cxsf, r0");

    // now read the registers r0-r12
    asm("\t LDMFD sp!, {r0-r12, lr}");

    // switch back to the interrupt handler
    asm("\t CPS 0x12");



    // ******************************
    // ****** INTERRUPPT STACK ******
    // ******************************

    // set the return address of the interrupt handler to the entry
    // point of the process
    asm("\t LDR lr, function_pointer \n" \
        "\t LDR lr, [lr]");

    // jump to process and leave the interrupt
    asm("\t STMFD sp!, {lr} \n" \
        "\t LDMFD sp!, {pc}^");

}
}
