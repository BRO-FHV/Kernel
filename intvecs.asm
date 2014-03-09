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

.if __TI_EABI_ASSEMBLER
.asg c_intIRQ, C_INTIRQ
.else
.asg _c_intIRQ, C_INTIRQ
.endif

.global _c_int00
.global C_INTIRQ
.global tim1_int

.sect ".intvecs"

B _c_int00 ; reset interrupt
.word 0 ; undefined instruction interrupt
.word 0 ; software interrupt
.word 0 ; abort (prefetch) interrupt
.word 0 ; abort (data) interrupt
.word 0 ; reserved

B C_INTIRQ ; IRQ interrupt
B tim1_int ; FIQ interrupt
