;****************************************************************************
; Setup interrupt vectors - Example 6-7 (ARM Optimizing C/C++ Compiler User's Guide p.136)
;****************************************************************************
; To map interrupt routines to interrupt vectors you need to include a intvecs.asm file. This file will contain
; assembly language directives that can be used to set up the ARM's interrupt vectors with branches to your
; interrupt routines. Follow these steps to use this file:
; 	1. Using Example 6-7 as a guide, create intvecs.asm and include your interrupt routines. For each routine:
; 		(a) At the beginning of the file, add a .global directive that names the routine.
; 		(b) Modify the appropriate .word directive to create a branch to the name of your routine.
; 	2. Assemble and link intvecs.asm with your applications code and with the compiler's linker control file
; 	   (lnk16.cmd or lnk32.cmd). The control file contains a SECTIONS directive that maps the .intvecs
; 	   section into the memory locations 0x00-0x1F.
;
; NOTE: Prefixing C/C++ Interrupt Routines
; 	Remember, if you are using C/C++ interrupt routines, you must use the proper linkname. So
; 	for TIABI and TI ARM9 ABI use _c_intIRQ instead of c_intIRQ, for example, for a function defined in C scope.
;
; For example, on an ARM v4 target, if you have written a C interrupt routine for the IRQ interrupt called
; c_intIRQ and an assembly language routine for the FIQ interrupt called tim1_int, you should create
; intvecs.asm as in Example 6-7
;****************************************************************************

	.global _c_int00
	.global udef_handler
	.global swi_handler
	.global pabt_handler
	.global dabt_handler
	.global irq_handler
	.global fiq_handler

	.sect ".intvecs"

; See AM335x Technical Reference Manual.pdf Page 4663 Table 23-10. RAM Exception Vectors
		B _c_int00		; Reset
		B udef_handler	; Interrupt Undefined		0x4030CE04
		B swi_handler	; Interrupt SWI				0x4030CE08
		B pabt_handler	; Interrupt Prefetch Abort	0x4030CE0C
		B dabt_handler	; Interrupt Data Abort		0x4030CE10
		.word 0			; Unused					0x4030CE14
		B irq_handler	; Interrupt IRQ				0x4030CE18
		B fiq_handler	; Interrupt FIQ				0x4030CE1C
