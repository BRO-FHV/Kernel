////////////////////////////////////////////////////////
// Linker command file for BeagleBone)				  //
////////////////////////////////////////////////////////
// Basic configuration using only external memory	  //
////////////////////////////////////////////////////////

-stack           0x00002000
-heap            0x00F00000

MEMORY
{
	SRAM:     o = 0x402F0400  l = 0x0000FC00  /* 64kB internal SRAM */
    L3OCMC0:  o = 0x40300000  l = 0x0000CE00  /* 64kB L3 OCMC SRAM */
    M3SHUMEM: o = 0x44D00000  l = 0x00004000  /* 16kB M3 Shared Unified Code Space */
    M3SHDMEM: o = 0x44D80000  l = 0x00002000  /* 8kB M3 Shared Data Memory */
	// Map handler (See AM335x Technical Reference Manual.pdf Page 4663 Table 23-10. RAM Exception Vectors)
	// Reserved (Reset)			0x4030CE00
	// Interrupt Undefined		0x4030CE04
	// Interrupt SWI			0x4030CE08
	// Interrupt Prefetch Abort	0x4030CE0C
	// Interrupt Data Abort		0x4030CE10
	// Unused					0x4030CE14
	// Interrupt IRQ			0x4030CE18
	// Interrupt FIQ			0x4030CE1C
	//overriding the branch (load into PC) instruction between addresses from 0x4030CE04 to 0x4030CE1C
   	RAMEXC:   o = 0x4030CE04  l = 0x00000100  /* interrups exception mapping */
    DDR0:     o = 0x80000000  l = 0x7FFFFFF  /* external DDR Bank 0 */
}

SECTIONS
{
	// map interrupt-vectors to 0x40200000 instead of 0x4020FFC8 (OMAP35x.pdf at page 3438) because would not
    // fit to memory (overshoot length). so in boot.asm the c12 register is set to 0x40200000
    .intvecs 	> RAMEXC

    .const      > DDR0
    .bss        > DDR0
    .far        > DDR0

    .stack      > DDR0
    .data       > DDR0
    .cinit      > DDR0
    .cio        > DDR0

    .text       > DDR0
    .sysmem     > DDR0
    .switch     > DDR0

	.heap		> DDR0

	.irqStack 	> DDR0
	.abortStack	> DDR0
}
