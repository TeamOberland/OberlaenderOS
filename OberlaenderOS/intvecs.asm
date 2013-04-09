;****************************************************************************
; Setup interrupt vectors (ARM Optimizing C/C++ Compiler User's Guide p.136)
;****************************************************************************
	.asg swi_handle, C_INTSWI
	.asg irq_handle, C_INTIRQ
	.asg udef_handle, C_INTUDEF
	.asg pabt_handle, C_INTPABT
	.asg dabt_handle, C_INTDABT

	.global _c_int00
	.global C_INTIRQ
	.global C_INTSWI
	.global C_INTUDEF
	.global C_INTPABT
	.global C_INTDABT

	.sect ".intvecs"
		B _c_int00    ;  Reset 			: 0x4020FFC4
		B C_INTUDEF   ;  Undefined 		: 0x4020FFC8
		B C_INTSWI	  ;  SWI       		: 0x4020FFCC
		B C_INTPABT	  ;  Prefetch Abort	: 0x4020FFD0
		B C_INTDABT	  ;  Data Abort		: 0x4020FFD4
		.word 0       ;  Unused			: 0x4020FFD8
		B C_INTIRQ    ;  IRQ			: 0x4020FFDC
		.word 0       ;  FIQ			: 0x4020FFE0
