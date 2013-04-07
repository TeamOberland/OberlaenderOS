////////////////////////////////////////////////////////
// Linker command file for BeagleBoard
// 
// Basic configuration using only external memory
//

-stack           0x00002000
-heap            0x00002000

MEMORY
{
   int_ram:  ORIGIN = 0x40200000  LENGTH = 0x0000FF4C
   //
   // Interrupt Vector Adresses: (http://e2e.ti.com/support/dsp/omap_applications_processors/f/447/t/29274.aspx)
   //  - Reset 			: 0x4020FFC4
   //  - Undefined 		: 0x4020FFC8
   //  - SWI       		: 0x4020FFCC
   //  - Prefetch Abort	: 0x4020FFD0
   //  - Data Abort		: 0x4020FFD4
   //  - Unused			: 0x4020FFD8
   //  - IRQ			: 0x4020FFDC
   //  - FIQ			: 0x4020FFE0
   int_vecs:  ORIGIN = 0x4020FFC4  LENGTH = 0x0000003B
   ext_ddr:  ORIGIN = 0x82000000  LENGTH = 0x10000000
}

SECTIONS
{
	.intvecs   > int_vecs {
		*(.intvecs)
	}

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
