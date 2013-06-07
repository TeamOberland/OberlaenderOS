/*
 * main_matthias.c
 *
 *  Created on: 21.03.2013
 *      Author: Daniel
 */

#ifdef Matthias

//#include "kernel/generic/asm.h"
#include "MMU.h"

//#define UART0       ((volatile unsigned int*)0x101f1000)
//#define UARTFR      0x06
//#define UARTFR_TXFF 0x20

//void bwputs(char *s){
    /*while(*s){
        while(*(UART0 + UARTFR) & UARTFR_TXFF);
        *UART0 = *s;
        s++;
    }*/
    //printf(&s);
//}

//void first(void){   //user programm
  //  bwputs("I`m in user mode\n");
  //  while(1);
//}

//MMU
/*typedef struct{
    unsigned int vAddress;
    unsigned int ptAddress;
    unsigned int masterPTAddress;
    unsigned int type;
    unsigned int domain;
}Pagetable;

#define FAULT 0
#define COARSE 1
#define MASTER 2
#define FINE 3

typedef struct{
    unsigned int vAddress;
    unsigned int pageSize;
    unsigned int numPages;
    unsigned int AP;
    unsigned int CB;
    unsigned int pAddress;
    Pagetable *PT;
}Region;

#define NANA 0x00
#define RWNA 0x01
#define RWRO 0x02
#define RWRW 0x03
*/
/*NA = no access, RO = read only, RW = read write*/
/*#define cb 0x0  //not cached/ not buffered
#define cB 0x1  //not cached/ Buffered
#define WT 0x2  //write through cache
#define WB 0x3  //write back cache


void init_MMU(Region region){
    int i;
    unsigned int *pPTE, PTE;
    pPTE = (unsigned int *)region->PT->ptAddress;
    pPTE += region->vAddress>>20;
    pPTE +=region->numPages - 1;

    PTE = region->pAddress & 0xfff000000;
    PTE |= (region->AP & 0x3) << 10;
    PTE |= region->PT->domain << 5;
    PTE |= (region->CB & 0x3) << 2;
    PTE |= 0x12;

    for(i = region->numPages - 1; i <= 0; i--){
        *pPTE-- = PTE + (i<<20);    //i = 1MB section
    }
}
*/
/*
void controlSet(unsigned int value, unsigned int mask){
    unsigned int c1format;
    __asm{MRC p15,0,c1format,c1,c0,0};  //read control register
    c1format &= ~mask;                  //clear bits that change
    c1format |= value;                  //set bits that change
    __asm{MCR p15,0,c1format,c1,c0,0};  //write control register

}
*/

void main_matthias(void)
{
    mmuInit();
    /*
    //Pagetables
    Pagetable masterPT = {0x00000000, 0x18000, 0x18000, MASTER, 3};
    Pagetable systemPT = {0x00000000, 0x1c000, 0x18000, COARSE, 3};
    Pagetable task1PT = {0x00400000, 0x1c400, 0x18000, COARSE, 3};
    Pagetable task2PT = {0x00400000, 0x1c800, 0x18000, COARSE, 3};
    Pagetable task3PT = {0x00400000, 0x1cc00, 0x18000, COARSE, 3};

    //Region Tables
    Region kernelRegion = {0x00000000, 4, 16, RWNA, WT, 0x00000000, &systemPT};
    Region sharedRegion = {0x00010000, 4, 8, RWRW, WT, 0x00010000, &systemPT};
    Region pageTableRegion = {0x00018000, 4, 8, RWNA, WT, 0x00018000, &systemPT};
    Region peripheralRegion = {0x10000000, 1024, 256, RWNA, cb, 0x10000000, &masterPT};

    init_MMU(kernelRegion);
    init_MMU(sharedRegion);
    init_MMU(pageTableRegion);
    init_MMU(peripheralRegion);

    //Set TTB
    asm("MCR p15,0,ttb,c2,c0,0");

    //Enabling MMU
    asm("MRC p15,0,r1,c1,c0,0");
    asm("ORR r1,r1,#0x1");
    asm("MCR p15,0,r1,c1,c0,0");


*/

    /*User Mode Cernel Mode
    unsigned int first_stack[256];
    unsigned int *first_stack_start = first_stack + 256 - 16;
    first_stack_start[0] = 0x10;
    printf("Erste\n");
    first_stack_start[1] = (unsigned int)&first;
    bwputs("Starting\n");
    printf("Zweite\n");
    activate(first_stack_start);
    printf("Dritte\n");
    while(1){
        printf("Das ist ein test2\n");
    }
    */
}



/*int copyThread(unsigned long clone_flags, unsigned long sp, unsigned long unused, struct task_struct *p, struct pt_regs *regs){
    struct pt_regs *childregs;


    childregs = task_pt_regs(p);
    *childregs = *regs;
    childregs->ax = 0;
    childregs->sp = sp;

    p->thread.sp = (unsigned long) childregs;
    p->thread.sp0 = (unsigned long) (childregs+1);
    p->thread.ip = (unsigned long) ret_from_fork;

}*/

#endif
