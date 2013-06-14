	.global __mmu_update_master_table

	.global current_master_table
_current_master_table: .field current_master_table, 32


__mmu_update_master_table:
	LDR R1, _current_master_table
	LDR R1, [R1]

	MCR   P15, #0, R1, C2, C0, #0 ; sets the master table
	MRC   P15, #0, R1, C2, C0, #0

	MOV   R0, #0	; clears the tlb
	MCR   P15, #0, R0, C8, C7, #0
