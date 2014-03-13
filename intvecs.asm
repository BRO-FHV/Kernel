;****************************************************************************
; Setup interrupt vectors - Example 6-7 (ARM Optimizing C/C++ Compiler User's Guide p.136)
;****************************************************************************
	.global _c_int00
	.global udef_handler
	.global swi_handler
	.global pabt_handler
	.global dabt_handler
	.global irq_handler
	.global fiq_handler
;****************************************************************************
; See AM335x Technical Reference Manual.pdf Page 4663 Table 23-10. RAM Exception Vectors
;****************************************************************************
	.sect ".intvecs"
		B _c_int00		; Reset
		B udef_handler	; Interrupt Undefined		0x4030CE04
		B swi_handler	; Interrupt SWI				0x4030CE08
		B pabt_handler	; Interrupt Prefetch Abort	0x4030CE0C
		B dabt_handler	; Interrupt Data Abort		0x4030CE10
		.word 0			; Unused					0x4030CE14
		B irq_handler	; Interrupt IRQ				0x4030CE18
		B fiq_handler	; Interrupt FIQ				0x4030CE1C
