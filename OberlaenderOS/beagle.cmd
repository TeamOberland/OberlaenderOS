////////////////////////////////////////////////////////
// Linker command file for BeagleBoard)
// 
// Basic configuration using only external memory
//

-stack           0x00002000
-heap            0x00002000

MEMORY
{
   int_ram:  ORIGIN = 0x40200000  LENGTH = 0x0000FFFF
   ext_ddr:  ORIGIN = 0x82000000  LENGTH = 0x10000000
}

SECTIONS
{
   .const      > ext_ddr
   .bss        > ext_ddr
   .far        > ext_ddr
   
   .stack      > ext_ddr
   .data       > ext_ddr
   .cinit      > ext_ddr
   .cio        > ext_ddr
   
   .text       > ext_ddr
   .sysmem     > ext_ddr
   .switch     > ext_ddr

   .stackarea  > ext_ddr {
		/* 4k stacks */
		. = . + (4 * 1024);
		kernelStack = .;
		. = . + (4 * 1024);
		irqStack = .;
		. = . + (4 * 1024);
		systemStack = .;
   }
}
