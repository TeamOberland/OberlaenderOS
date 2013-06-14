	.armfunc _c_int00
    .global _c_int00

;****************************************************************************
; Entry-Exit Point definition
;****************************************************************************
    .asg	_args_main,   ARGS_MAIN_RTN
    .asg	exit,         EXIT_RTN
    .asg    main_func_sp, MAIN_FUNC_SP

;****************************************************************************
; Stack definition
;****************************************************************************
    .global systemStack
c_r13_system    .long    systemStack

;***************************************************************
;* FUNCTION DEF: _c_int00
;***************************************************************
_c_int00: .asmfunc
    BL    __TI_auto_init
    BL    ARGS_MAIN_RTN
.end


;******************************************************
;* UNDEFINED REFERENCES                               *
;******************************************************

	.global ARGS_MAIN_RTN
	.global	EXIT_RTN
	.global __TI_auto_init

