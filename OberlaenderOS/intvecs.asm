;****************************************************************************
; Setup interrupt vectors
;****************************************************************************
	.asg _irq_handle, C_INTIRQ
	.global C_INTIRQ
	.global _c_int00

	.sect ".intvecs"
		B _c_int00    ;  Reset 			: 0x4020FFC4
	    .word 0       ;  Undefined 		: 0x4020FFC8
	    .word 0		  ;  SWI       		: 0x4020FFCC
	    .word 0 	  ;  Prefetch Abort	: 0x4020FFD0
	    .word 0		  ;  Data Abort		: 0x4020FFD4
	    .word 0       ;  Unused			: 0x4020FFD8
	    B C_INTIRQ    ;  IRQ			: 0x4020FFDC
	    .word 0       ;  FIQ			: 0x4020FFE0
