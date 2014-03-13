////////////////////////////////////////////////////////
// Linker command file for BeagleBoard)				  //
////////////////////////////////////////////////////////
// Basic configuration using only external memory	  //
////////////////////////////////////////////////////////

-stack           0x00002000
-heap            0x00F00000

MEMORY
{
    int_ram:	ORIGIN = 0x40200000		LENGTH = 0x0010CE00
	// Map handler (see ; See AM335x Technical Reference Manual.pdf Page 4663 Table 23-10. RAM Exception Vectors)
	// Reserved (Reset)			0x4030CE00
	// Interrupt Undefined		0x4030CE04
	// Interrupt SWI			0x4030CE08
	// Interrupt Prefetch Abort	0x4030CE0C
	// Interrupt Data Abort		0x4030CE10
	// Unused					0x4030CE14
	// Interrupt IRQ			0x4030CE18
	// Interrupt FIQ			0x4030CE1C
	//overriding the branch (load into PC) instruction between addresses from 0x4030CE04 to 0x4030CE1C
   	int_vecs:	ORIGIN = 0x4030CE00		LENGTH = 0x0000003B
    ext_ddr:	ORIGIN = 0x82000000     LENGTH = 0x10000000
}

SECTIONS
{
	// map interrupt-vectors to 0x40200000 instead of 0x4020FFC8 (OMAP35x.pdf at page 3438) because would not
    // fit to memory (overshoot length). so in boot.asm the c12 register is set to 0x40200000
    .intvecs load = int_ram ALIGN = 4 {
		int_vecs = .;
		*(.intvecs)
	}

    .const      > ext_ddr
    .bss        > ext_ddr
    .far        > ext_ddr

    .stack      > ext_ddr
    .data       > ext_ddr
    .cinit      > ext_ddr
    .cio        > ext_ddr

    .text       > ext_ddr
    .sysmem     > ext_ddr
    .switch     > ext_ddr
	
	.irqStack 	> ext_ddr
	.abortStack	> ext_ddr
	.systemStack> ext_ddr

//	.stackArea > ext_ddr {
//		. = align(4);
//		. = . + (4 * 1024);
//		irqStack = .;
//		. = . + (4 * 1024);
//		abortStack = .;
//		. = . + (4 * 1024);
//		systemStack = .;
//		. = . + (4 * 1024);
//	}
}
