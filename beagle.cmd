/*
 * Kernel: beagle.cmd
 * Part of BRO Project, 2014 <<https://github.com/BRO-FHV>>
 *
 * Created on: 05.03.2014
 * Description:
 * Linker command file for BeagleBone
 * Basic linker options
 */

/* heap and stack sizes */
-stack           0x00000008
-heap            0x00002000

/* supress warning _c_int00 entry point */
--diag_suppress=10063

/* set entry point to boot asm (boot.asm) func */
-e boot

MEMORY
{
<<<<<<< HEAD
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
=======
	RAMEXC:   o = 0x4030CE04  l = 0x00000100  	/* interrups exception mapping */
    DDR0:     o = 0x80000000  l = 0x7FFFFFF		/* internal ram 128MB */
>>>>>>> 3cfba02f327a7c05a188d671bb100412c5197385
}

SECTIONS
{
    .intvecs 	> RAMEXC

    .text      	: load > DDR0
    .data   	: load > DDR0
    .bss    	: load > DDR0
    .const 	    : load > DDR0
    .stack  	: load > 0x87FFFFF0

    .cinit	   	: load > DDR0
    .sysmem		: load > DDR0
}
