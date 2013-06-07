/*
 * mmu.c
 *
 *  Created on: 31.05.2013
 *      Author: Matthias
 */
#define MMU_ALIGN_ADDRESS 0xFFFFC000
#define MMU_MAX_PROCESS_SPACE 0xFFF00000    //4GB space for each process
#define MMU_SECTION_ENTRY_SIZE 0x00100000 // 1 MB for each section entry
#define MMU_SECTION_ENTRY_INITIAL_VALUE_FOR_KERNEL 0xC12
#define MMU_LAST_SECTION_ENTRY_VALUE_FOR_KERNEL 0xFFF00C12
#define MMU_PAGE_SIZE = 0x1000;  //4k
typedef struct{
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
/*NA = no access, RO = read only, RW = read write*/
#define cb 0x0  //not cached/ not buffered
#define cB 0x1  //not cached/ Buffered
#define WT 0x2  //write through cache
#define WB 0x3  //write back cache

#define MAX_PROCESS_SPACE 0xFFF00000
#define SECTION_ENTRY 0xC12


typedef struct{
    int value;
}MMUAddress;

unsigned int kernelMasterTable;
MMUAddress processTableMasterAddress;

void setMasterTablePointer(MMUAddress *tableAddress);
MMUAddress CreateMasterTable();

Pagetable master;
Pagetable system;
Pagetable task1;
Pagetable task2;
Pagetable task3;



void fillPTwithTranslations(Region region){
    int i;
    unsigned int* pPTE;
    unsigned int PTE;

    pPTE = (unsigned int *)(region.pAddress);
    pPTE += region.vAddress >> 20;
    pPTE += (region.numPages - 1);

    PTE = region.pAddress & MAX_PROCESS_SPACE;
    PTE |= (region.pAddress & 0x3) << 10;
    PTE |= region.PT->domain << 5;
    PTE |= (region.CB & 0x3) << 2;
    PTE |= SECTION_ENTRY;

    for(i = region.numPages -1; i >= 0; i--){
        *pPTE-- = PTE + (i << 20);
    }
}

void controlSet(unsigned int value, unsigned int mask){
    unsigned int c1format;
//    asm("  MRC p15, 0, c1format, c1, c0, 0");
    c1format &= ~mask;
    c1format |= value;
//    asm("  MCR p15, 0, c1format, c1, c0, 0");
}

void mmuInit(){
    Pagetable masterPT = {0x00000000, 0x18000, 0x18000, MASTER, 3};
    Pagetable systemPT = {0x00000000, 0x1c000, 0x18000, COARSE, 3};
    Pagetable task1PT = {0x00400000, 0x1c400, 0x18000, COARSE, 3};
    Pagetable task2PT = {0x00400000, 0x1c800, 0x18000, COARSE, 3};
    Pagetable task3PT = {0x00400000, 0x1cc00, 0x18000, COARSE, 3};
    //Region Tables
    Region kernelRegion = {0x00000000, 4, 16, RWRW, WT, 0x00000000, 0};
    kernelRegion.PT = &systemPT;
    Region sharedRegion = {0x00010000, 4, 8, RWRW, WT, 0x00010000, 0};
    sharedRegion.PT = &systemPT;
    Region pageTableRegion = {0x00018000, 4, 8, RWRW, WT, 0x00018000, 0};
    pageTableRegion.PT = &systemPT;
    Region peripheralRegion = {0x10000000, 1024, 256, RWRW, cb, 0x10000000, 0};
    peripheralRegion.PT = &masterPT;

    fillPTwithTranslations(kernelRegion);
    fillPTwithTranslations(sharedRegion);
    fillPTwithTranslations(pageTableRegion);
    fillPTwithTranslations(peripheralRegion);

//    asm("  MCR p15, 0, ttb, c2, c0, 0");

    //Enabling the MMU
//    asm("  MRC p15, 0, r1, c1, c0, 0");
//    asm("  ORR r1, r1, #0x1");
//    asm("  MCR p15, 0, r1, c1, c0, 0");
}

/*void mmuInitOTTOS(){
    unsigned int i;
    unsigned int kernelPagesNr;

    MMUAddress tableAddress;
    processTableMasterAddress = 0;

    asm(" MOV R0, #0x5557");
    asm(" MOVT R0, #0x5555");
    asm(" MCR P15, #0, R0, C3, C0, #0");

    tableAddress = &kernelMasterTable;

    setMasterTablePointer(tableAddress);
    for(i=0x00000000; i < MMU_MAX_PROCESS_SPACE; i += MMU_SECTION_ENTRY_SIZE){
        *tableAddress = i | MMU_SECTION_ENTRY_INITIAL_VALUE_FOR_KERNEL;
        ++tableAddress;
    }

    *tableAddress = MMU_LAST_SECTION_ENTRY_VALUE_FOR_KERNEL;

    asm(" MRC P15, #0, R0, C1, C0, #0");
    asm(" ORR R0, R0, #0x1");
    asm(" MCR P15, #0, R0, C1, C0, #0");
}

void setMasterTablePointer(MMUAddress *tableAddress){
    processTableMasterAddress = (MMUAddress)((unsigned int)tableAddress & MMU_ALIGN_ADDRESS);
    asm(" LDR R1, processTableMasterAddress");
    asm(" LDR R1, [R1]");
    asm(" MCR P15, #0, R1, C2, C0, #0");
    asm(" MRC P15, #0, R1, C2, C0, #0");

    asm(" MOV R0, #0");
    asm(" MCR P15, #0, R0, C8, C7, #0");
}


MMUAddress CreateMasterTable(){
    MMUAddress masterTableAddress;
    masterTableAddress.value=0x18000;
    return masterTableAddress;
}

void mapOneToOne(Pagetable pt){
    int i;
    for(i=0; i < pt.length; i += MMU_PAGE_SIZE){
        //map next Page
    }
}

void mapDirectly(Pagetable pt){

}
*/
