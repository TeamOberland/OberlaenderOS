/*
 * asm.h
 *
 *  Created on: 11.04.2013
 *      Author: Matthias Amann
 */

#ifndef ASM_H_
#define ASM_H_

//void activate(unsigned int *stack){
    //asm("    cps #10");

    /*asm("ldmfd r0!, {ip,lr}");
    asm("msr SPSR, ip");
    asm("msr CPSR_c, #0xDF");
    asm("mov sp, r0");
    asm("pop {r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,fp,ip,lr}");
    asm("msr CPSR_c, #0xD3");
    asm("movs pc, lr");
*/
    //asm("    mov ip, sp");        /* Copy sp to ip */
    //asm("    msr CPSR_c, #0xDF"); /* System mode */
    //asm("    mov sp, ip");        /* Set user mode sp to our copy */
    //asm("    msr CPSR_c, #0xD3"); /* Supervisor mode */

    //asm("    mov r0, #0x10");     /* User mode */
    //asm("    msr SPSR, r0");      /* Set User mode to SPSR */
    //asm("    ldr lr, =first");    /* Load location of first */
    //asm("    movs pc, lr");       /* movs to first */
//}


#endif /* ASM_H_ */
