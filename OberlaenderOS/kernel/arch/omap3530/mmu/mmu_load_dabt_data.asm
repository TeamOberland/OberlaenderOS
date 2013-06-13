	.global __mmu_load_dabt_data

	.global mmu_accessed_address
	.global mmu_fault_state

_mmu_accessed_address: .field mmu_accessed_address, 32
_mmu_fault_state: .field mmu_fault_state, 32

__mmu_load_dabt_data:
	MRC   P15, #0, R0, C6, C0, #0
	LDR   R1, _mmu_accessed_address
	STR   R0, [R1]

	MRC p15, #0, r0, c5, c0, #0
	LDR r1, _mmu_fault_state
	STR r0, [r1]
