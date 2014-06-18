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
    int_ram:    o = 0x402F0400  l = 0x0000FF4C
	int_vecs:   o = 0x4030CE04  l = 0x00000100  	/* interrups exception mapping */
    ext_ddr:    o = 0x80000000  l = 0x7FFFFFF		/* internal ram 128MB */
}

SECTIONS
{
	.intvecs   > int_vecs {
		int_vecs = .;
		*(.intvecs)
	}

	.interrupts	> int_ram

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

	.stackarea  > ext_ddr {
		. = align(4);
		. = . + (4 * 1024);
		kernelStack = .;
		. = . + (4 * 1024);
		irqStack = .;
		. = . + (4 * 1024);
		systemStack = .;
		. = . + (4 * 1024);
		abortStack = .;
		ext_ddr_user_start = .;
	}
}
