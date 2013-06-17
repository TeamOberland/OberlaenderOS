	.global __context_load
	.global __context_log

	.global current_context
_current_context: .field current_context, 32

__context_load:
	LDR R14, _current_context
	LDR R14, [R14]
	ADD R14, R14, #64

	LDR R12, [R14]
	MSR SPSR_cxsf, R12

	LDMDB R14, {R0-R14}^
	LDR R14, [R14,#-64]

	MOVS PC, R14
