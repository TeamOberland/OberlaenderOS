#include "pcb.h"

/*
 * pcb.c
 *
 *  Created on: 07.05.2013
 *      Author: Manuel
 */

void pcb_init(pcb_t* t)
{
//    // init Task Control Block
    t->restartAddress = 0;
    t->functionPointer= 0;
    t->R13 = 0;
    t->CPSR =0;
    t->R0 = 0;
    t->R1 = 0;
    t->R2 = 0;
    t->R3 = 0;
    t->R4 = 0;
    t->R5 = 0;
    t->R6 = 0;
    t->R7 = 0;
    t->R8 = 0;
    t->R9 = 0;
    t->R10 = 0;
    t->R11 = 0;
    t->R12 = 0;
    t->R14 = 0;
}

