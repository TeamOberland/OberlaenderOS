;****************************************************************************
; Setup interrupt vectors (ARM Optimizing C/C++ Compiler User's Guide p.136)
;****************************************************************************
	.if __TI_EABI_ASSEMBLER
	.asg swi_handle, C_INTSWI
	.asg irq_handle, C_INTIRQ
	.else
	.asg _swi_handle, C_INTSWI
	.asg _irq_handle, C_INTIRQ
	.endif

	.global _c_int00
	.global C_INTIRQ
	.global C_INTSWI

	.sect ".intvecs"
		B _c_int00    ;  Reset 			: 0x4020FFC4
		.word 0       ;  Undefined 		: 0x4020FFC8
		B C_INTSWI	  ;  SWI       		: 0x4020FFCC
		.word 0 	  ;  Prefetch Abort	: 0x4020FFD0
		.word 0		  ;  Data Abort		: 0x4020FFD4
		.word 0       ;  Unused			: 0x4020FFD8
		B C_INTIRQ    ;  IRQ			: 0x4020FFDC
		.word 0       ;  FIQ			: 0x4020FFE0
