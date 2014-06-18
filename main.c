/*
 * Kernel: main.c
 * Part of BRO Project, 2014 <<https://github.com/BRO-FHV>>
 *
 * Created on: 05.03.2014
 * Description:
 * Main entry point of the OS. Important initializing is done.
 */

#include <stdio.h>
#include <stdint.h>
#include "kernel.h"
#include <interrupt/dr_interrupt.h>
#include <timer/dr_timer.h>
#include <led/dr_led.h>
#include <soc_AM335x.h>
#include <cpu/hw_cpu.h>
#include <scheduler.h>
#include "Test.h"
#include "Test2.h"
#include <sd/dr_sd.h>
#include <elf/dr_elfloader.h>
#include <inttypes.h>
#include <sd/thirdParty/fatfs/src/ff.h>

#include <mmu/sc_mmu.h>

extern irq_handler(void);

int main(void) {


	CPUirqd();


	LedInitRegister();
	LedInit1();
	LedInit2();
	MmuInit();

	IntControllerInit();




	printf("started - now wait!\n");
	startFileSystem();
	CPUirqe();
	FILINFO fi;
	if(f_stat("Test.out",&fi) == FR_OK)
	{
		uint8_t *dataBuf = (uint8_t*)malloc(fi.fsize);
		getElfFile(dataBuf, fi.fsize, "Test.out");
		loadProcessFromElf(0, dataBuf);
		free(dataBuf);
		//loadProcessFromElf(0, Test);
	}
	loadProcessFromElf(0, Test2);
	TimerConfiguration(Timer_TIMER2,2000,SchedulerRunNextProcess);
	//CPUirqe();
	TimerEnable(Timer_TIMER2);
	while (1) {
		volatile int i = 0;

		for (i = 0; i < 1000000; i++) {
		}
	}
}

#pragma INTERRUPT(fiq_handler, FIQ)
interrupt void fiq_handler() {
	printf("fiq interrupt\n");
}

/**
 * Is called on any undefined error which caused an abort
 */
#pragma INTERRUPT(udef_handler, UDEF)
interrupt void udef_handler() {
	printf("udef interrupt\n");
}

/**
 * Is called on any prefetch abort.
 */
#pragma INTERRUPT(pabt_handler, PABT)
interrupt void pabt_handler() {
	printf("pabt interrupttfu\n");
}
