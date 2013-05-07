/*
 * pcb.h
 *
 *  Created on: 07.05.2013
 *      Author: Manuel
 */

#ifndef PCB_H_
#define PCB_H_

/*
 * program control block
 */
typedef struct _pcb {

    // all registers
    int CPSR;
    int restartAddress;
    int functionPointer;
    int R0;
    int R1;
    int R2;
    int R3;
    int R4;
    int R5;
    int R6;
    int R7;
    int R8;
    int R9;
    int R10;
    int R11;
    int R12;
    int R13;
    int R14;
    int stack_pointer;
} pcb_t;

void pcb_init(pcb_t* t);

#endif /* PCB_H_ */
