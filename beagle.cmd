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
-heap            0x00080000

/* supress warning _c_int00 entry point */
--diag_suppress=10063

/* set entry point to boot asm (boot.asm) func */
-e boot

MEMORY
{
	RAMEXC:   o = 0x4030CE04  l = 0x00000100  	/* interrups exception mapping */
    DDR0:     o = 0x80000000  l = 0x7FFFFFF		/* internal ram 128MB */
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
