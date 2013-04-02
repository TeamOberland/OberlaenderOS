# CPU Operating Modes 
http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.ddi0210c/Cihhcjia.html
http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.dui0204j/Cihfdbhd.html

## [USR] User

*CPSR Register Value / Flags for CPS Command*: 0x10
*Description*: User mode is the usual ARM program execution state, and is used for executing most application programs.
	
## [FIQ] Fast Interrupt Request

*CPSR Register Value / Flags for CPS Command*: 0x11
*Description*: Fast Interrupt (FIQ) mode supports a data transfer or channel process.

## [IRQ] Interrupt Request
*CPSR Register Value / Flags for CPS Command*: 0x12
*Description*:  Interrupt (IRQ) mode is used for general-purpose interrupt handling.
	
## [SVC] Supervisor
*CPSR Register Value / Flags for CPS Command*: 0x13
*Description*:  Supervisor mode is a protected mode for the operating system.
	
## [ABT] Abort

*CPSR Register Value / Flags for CPS Command*: 0x17
*Description*:  Abort mode is entered after a data or instruction Prefetch Abort.

## [UND] Undefined Instruction
*CPSR Register Value / Flags for CPS Command*: 0x1b
*Description*:  Undefined mode is entered when an undefined instruction is executed.
	
## [SYS] System
*CPSR Register Value / Flags for CPS Command*: 0x1F
*Description*: System mode is a privileged user mode for the operating system.
	