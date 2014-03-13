////////////////////////////////////////////////////////
// Linker command file for BeagleBoard)				  //
////////////////////////////////////////////////////////
// Basic configuration using only external memory	  //
////////////////////////////////////////////////////////

-stack           0x00002000
-heap            0x00002000

MEMORY
{
    int_ram:     ORIGIN = 0x40200000        LENGTH = 0x0000FFFF
	// Map handler (see ; See AM335x Technical Reference Manual.pdf Page 4663 Table 23-10. RAM Exception Vectors)
	// Interrupt Undefined		0x4030CE04
	// Interrupt SWI			0x4030CE08
	// Interrupt Prefetch Abort	0x4030CE0C
	// Interrupt Data Abort		0x4030CE10
	// Unused					0x4030CE14
	// Interrupt IRQ			0x4030CE18
	// Interrupt FIQ			0x4030CE1C
   //int_vecs:  	ORIGIN = 0x4030CE24  	LENGTH = 0x0000003B //0x00000018 normally?
    ext_ddr:     ORIGIN = 0x82000000        LENGTH = 0x00010000
}

SECTIONS
{
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
	
	.irqstack 	> ext_ddr
	.abortstack  > ext_ddr
	// TODO: add here further stack-addresses and initialize them in boot.asm as required
	
	// map interrupt-vectors to 0x40200000 instead of 0x4020FFC8 (OMAP35x.pdf at page 3438) because would not
    // fit to memory (overshoot length). so in boot.asm the c12 register is set to 0x40200000
    .intvecs    > int_ram
}
