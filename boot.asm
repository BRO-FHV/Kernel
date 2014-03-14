	.armfunc _c_int00
    .global _c_int00

;****************************************************************************
; Entry-Exit Point definition
;****************************************************************************
    .asg	_args_main,   ARGS_MAIN_RTN
    .asg	exit,         EXIT_RTN
    .asg    main_func_sp, MAIN_FUNC_SP

;****************************************************************************
;* DEFINES						                                            *
;****************************************************************************
	.global	__STACK_SIZE
	.global ARGS_MAIN_RTN
	.global MAIN_FUNC_SP
	.global	EXIT_RTN
	.global __TI_auto_init

	.global intvecs_adr
	.global irqStack
	.global abortStack

intvecs_adr:.usect	".intvecs", 0, 4
irqStack:.usect		".irqStack", 512, 4
abortStack:.usect	".abortStack", 512, 4


_intvecs_adr		.long	intvecs_adr
_irqStack			.long	irqStack
_abortStack			.long	abortStack


ABORT_STACK_SIZE 	.long    0x1000
IRQ_STACK_SIZE 		.long    0x1000

;***************************************************************
;* FUNCTION DEF: _c_int00                                      
;***************************************************************
_c_int00: .asmfunc
        ;*------------------------------------------------------
        ;* Switch to IRQ Mode and store stack-pointer
        ;*------------------------------------------------------<
        CPS		#0x12
        LDR     sp, _irqStack
		LDR		r0, IRQ_STACK_SIZE
		ADD		sp, sp, r0
        ;*------------------------------------------------------
        ;* Switch to Abort Mode and store stack-pointer
        ;*------------------------------------------------------
        CPS		#0x17
        LDR     sp, _abortStack
		LDR		r0, ABORT_STACK_SIZE
		ADD		sp, sp, r0

        ;*------------------------------------------------------
        ;* Set interrupt vector base address register out of user space
        ;*------------------------------------------------------
		LDR 	r0, _intvecs_adr
		MCR		p15, #0, r0, c12, c0, #0

        ;*------------------------------------------------------
	    ; Enable Interrupts
	    ;*------------------------------------------------------
	    ; MRS   R12, CPSR
	    ; BIC   R12, R12, #192
	    ; MSR   CPSR_cf, R12

		;*------------------------------------------------------
        ;* Perform all the required initilizations:
        ;*   - Process BINIT Table
        ;*   - Perform C auto initialization
        ;*   - Call global constructors
        ;*------------------------------------------------------
        BL      __TI_auto_init

        ;*------------------------------------------------------
        ;* CALL APPLICATION
        ;*------------------------------------------------------
        BL      ARGS_MAIN_RTN
.end
