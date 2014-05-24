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
-stack           0x00002000
-heap            0x00F00000

/* supress warning _c_int00 entry point */
--diag_suppress=10063

/* set entry point to boot asm (boot.asm) func */
-e boot

MEMORY
{
	RAMEXC:  o = 0x4030CE04  l = 0x00000100  	/* interrups exception mapping */
    DDR0:    o = 0x80000000  l = 0x7FFFFFF		/* internal ram 128MB */
}

SECTIONS
{
	.interrupts   > RAMEXC

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

	.stackarea  > DDR0 {
		. = align(4);
		. = . + (4 * 1024);
		kernelStack = .;
		. = . + (4 * 1024);
		irqStack = .;
		. = . + (4 * 1024);
		systemStack = .;
		. = . + (4 * 1024);
		abortStack = .;
	}
}
