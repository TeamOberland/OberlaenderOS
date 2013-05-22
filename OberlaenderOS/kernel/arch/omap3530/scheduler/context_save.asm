	.global __context_save

	.global current_context
_current_context: .field current_context, 32

__context_save:
	STMFD R13!, {R12, R14}
	LDR R14, _current_context
	; LDR R14, [R14]

	LDR R12, [R13, #8]
	STMIA R14!, {R12}
	LDR R12, [R13]
	STMIA R14, {R0-R14}^
	MRS R12, SPSR
	STR R12, [R14, #60]

	LDMFD R13!, {R12, R14}
	MOV PC, R14
