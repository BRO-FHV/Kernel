;
; Kernel: boot.asm
; Part of BRO Project, 2014 <<https://github.com/BRO-FHV>>
;
; Created on: Mar 26, 2014
; Description:
; boot function
;
; entry and exit point definition
;
    .asg	_args_main,   ARGS_MAIN_RTN
    .asg	exit,         EXIT_RTN
    .asg    main_func_sp, MAIN_FUNC_SP


	.armfunc boot
    .global boot

    .ref __stack
    .ref __STACK_END

;
; global definitions
;
	.global ARGS_MAIN_RTN
	.global MAIN_FUNC_SP
	.global	EXIT_RTN
	.global __TI_auto_init

	.global int_vecs
	.global irqStack
	.global kernelStack
	.global abortStack
	.global systemStack

;
; define constants
;
_stackptr			.word	__STACK_END
ABORT_STACK_SIZE 	.set    0x8
IRQ_STACK_SIZE 		.set    0x1000

c_sp_irq		.long	irqStack
c_sp_kernel		.long	kernelStack
c_sp_abort		.long	abortStack
c_sp_system		.long	systemStack

_int_vecs		.long 	int_vecs

;
; define arm mode masks
;
MODE_USR			.set	0x10
MODE_FIQ			.set	0x11
MODE_IRQ 			.set	0x12
MODE_SVC			.set	0x13
MODE_ABT 			.set	0x17
MODE_UND			.set	0x1B
MODE_SYS			.set	0x1F

;
; Entry point function
;
boot: .asmfunc
	;*------------------------------------------------------
	;* Switch to IRQ Mode and store stack-pointer
	;*------------------------------------------------------<
	CPS		0x12
	LDR     sp, c_sp_irq

	;*------------------------------------------------------
	;* Switch to Supervisor Mode and store stack-pointer
	;*------------------------------------------------------
	CPS		0x13
	LDR     sp, c_sp_kernel

	;*------------------------------------------------------
	;* Switch to ABT Mode and store stack-pointer
	;*------------------------------------------------------
	CPS		0x17
	LDR     sp, c_sp_abort

	;*------------------------------------------------------
	;* Switch to System Mode and Store stack-pointer
	;*------------------------------------------------------
	CPS		0x1F
	LDR		sp, c_sp_system

	; Interrupt Vectors base register
	LDR R0, _int_vecs
	MCR p15, #0, R0, c12, c0, #0

	;
	; Perform all the required initilizations:
	;	* Process BINIT Table
	;   * Perform C auto initialization
	;   *	 Call global constructors
	;
	BL		__TI_auto_init

	;
	; call application
	;
	BL      ARGS_MAIN_RTN
.end
