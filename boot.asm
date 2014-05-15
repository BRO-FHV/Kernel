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

;
; define constants
;
_stackptr			.word	__STACK_END
ABORT_STACK_SIZE 	.set    0x8
IRQ_STACK_SIZE 		.set    0x1000

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
	;
	; adjust stack pointer
	;
	LDR		r0, _stackptr	; load address to stack pointer in r0
	SUB		r0, r0, #8		; adjust sp
	BIC		r0, r0, #7

	;
	; switch to irq mode and set sp
	;
	CPS		#MODE_IRQ
	MOV		sp, r0						; set sp
	SUB		r0, r0, #IRQ_STACK_SIZE		; adjust sp

	;
	; switch to abort mode and set sp
	;
	CPS		#MODE_ABT
	MOV     sp, r0						; set sp
	SUB		r0, r0, #ABORT_STACK_SIZE	; adjust sp

	;
	; switch to sys mode
	;
	CPS		#MODE_SYS
	MOV		sp, r0		; set sp

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
