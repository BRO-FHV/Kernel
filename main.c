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

extern irq_handler(void);

void IRQHandle68() {
	//scheduler_runNextProcess(context);
	printf("asdf");
}

void switchLED2ON() {
	while (1) {
		int i = GPIOPinRead(SOC_GPIO_1_REGS, LED2_PIN);
		if (i==0) {
			LedOn2();
		}
	}
}
void switchLED2OFF() {
	while (1) {
		int i = GPIOPinRead(SOC_GPIO_1_REGS, LED2_PIN);
		if (i==1) {
			LedOff2();
		}
	}
}

void switchLED3ON() {
	while (1) {
		int i = GPIOPinRead(SOC_GPIO_1_REGS, LED3_PIN);
		if (i==0) {
			LedOn3();
		}
	}
}
void switchLED3OFF() {
	while (1) {
		int i = GPIOPinRead(SOC_GPIO_1_REGS, LED3_PIN);
		if (i==1) {
			LedOff3();
		}
	}
}

int main(void) {

	CPUirqd();

	printf("config timer\n");

	IntControllerInit();

	LedInitRegister();
	LedInit2();
	LedInit3();

	TimerConfiguration(Timer_TIMER2, 2000, scheduler_runNextProcess);
	TimerEnable(Timer_TIMER2);

	scheduler_startProcess(&switchLED2ON);
	scheduler_startProcess(&switchLED2OFF);
	scheduler_startProcess(&switchLED3ON);
	scheduler_startProcess(&switchLED3OFF);

	CPUirqe();

	printf("started - now wait!\n");
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
