;****************************************************************************
; Setup interrupt vectors (ARM Optimizing C/C++ Compiler User's Guide p.136)
;****************************************************************************
	.global _c_int00
	.global fiq_handle
	.global irq_handle
	.global swi_handle
	.global udef_handle
	.global pabt_handle
	.global dabt_handle

	.sect ".intvecs"
		B _c_int00    	;  Reset 			: 0x4020FFC4
		B udef_handle   ;  Undefined 		: 0x4020FFC8
		B swi_handle	;  SWI       		: 0x4020FFCC
		B pabt_handle	;  Prefetch Abort	: 0x4020FFD0
		B dabt_handle	;  Data Abort		: 0x4020FFD4
		.word 0       	;  Unused			: 0x4020FFD8
		B irq_handle    ;  IRQ				: 0x4020FFDC
		B fiq_handle    ;  FIQ				: 0x4020FFE0
