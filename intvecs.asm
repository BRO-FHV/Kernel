;
; Kernel: intvecs.asm
; Part of BRO Project, 2014 <<https://github.com/BRO-FHV>>
;
; Created on: Mar 26, 2014
; Description:
; link int vectors
;
;
; definition for interrupt handlers
;
	.global boot
	.global udef_handler
	.global swi_handler		; implemented in assembler file Driver/interrupt.asm
	.global pabt_handler
	.global dabt_handler
	.global irq_handler		; implemented in assembler file Driver/interrupt.asm
	.global fiq_handler

;
; define .intvecs memory section
;	* see AM335x Technical Reference Manual.pdf Page 4663 Table 23-10 RAM Exception Vectors
;
	.sect ".interrupts"
		;B boot			; Reset
		B udef_handler	; Interrupt Undefined		0x4030CE04
		B swi_handler	; Interrupt SWI				0x4030CE08
		B pabt_handler	; Interrupt Prefetch Abort	0x4030CE0C
		B dabt_handler	; Interrupt Data Abort		0x4030CE10
		.word 0			; Unused					0x4030CE14
		B irq_handler	; Interrupt IRQ				0x4030CE18
		B fiq_handler	; Interrupt FIQ				0x4030CE1C
