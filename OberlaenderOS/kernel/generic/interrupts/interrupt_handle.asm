	.bss pcb_old, 4
	.bss pcb_new, 4
	.bss stack_pointer_saved_context, 4
	.bss stack_pointer_original, 4

	.global irq_dispatch
	.global irq_handle

	.global swi_dispatch
	.global swi_handle

	.global pcb_old
	.global pcb_new
	.global stack_pointer_saved_context
	.global stack_pointer_original

	.global _pcb_old
	.global _pcb_new
	.global _stack_pointer_saved_context
	.global _stack_pointer_original

_pcb_old: .field pcb_current, 32
_pcb_new: .field pcb_new, 32
_stack_pointer_saved_context: .field stack_pointer_saved_context, 32
_stack_pointer_original: .field stack_pointer_original,32

swi_handle:
	STMFD   sp!, {R0-R12, R14}
	PUSH 	{R0}
	LDR     R0, _stack_pointer_saved_context
	STR     R13, [R0], #0

	POP 	{R0}
	B swi_dispatch

    LDMFD   R13!, {R0-R12, PC}^

	.global irq_dispatch
	.global irq_handle
	.global stack_pointer_saved_context

irq_handle:
	SUB     R14, R14, #4
	STMFD   R13!, {R0-R12, R14}
	PUSH 	{R0}
	LDR     R0, _stack_pointer_saved_context
	STR     R13, [R0], #0

	POP		{R0}
	B irq_dispatch

    LDMFD   R13!, {R0-R12, PC}^

