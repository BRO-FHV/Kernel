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
#include <sd/dr_sd.h>
#include <scheduler.h>
#include "Test.h"
#include <mmu/sc_mmu.h>

extern irq_handler(void);

int main(void) {

	CPUirqd();

	MmuInit();

	IntControllerInit();

	TimerConfiguration(Timer_TIMER2,2000,SchedulerRunNextProcess);
	TimerEnable(Timer_TIMER2);

	printf("started - now wait!\n");
	uint32_t l = sizeof(Test) / sizeof(Test[0]);
	loadProcessFromElf(l, Test);
	CPUirqe();
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
	printf("pabt interrupt\n");
}

/**
 * Is called on any data abort.
 */
#pragma INTERRUPT(dabt_handler, DABT)
interrupt void dabt_handler() {
	printf("dabt interrupt\n");
}
