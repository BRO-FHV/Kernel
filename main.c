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


void IRQHandle68()
{
	int i = GPIOPinRead(SOC_GPIO_1_REGS,23);
	if(i==0)
	{
		LedOn3();
	}
	else
	{
		LedOff3();
	}

}

int main(void) {

	CPUirqd();

	printf("config timer\n");

	IntControllerInit();

	LedInitRegister();
	LedInit2();
	LedInit3();

	LedOn3();

	TimerConfiguration(Timer_TIMER2, 1000, IRQHandle68);
	TimerEnable(Timer_TIMER2);

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
 * Is called on any interrupt request.
 */
#pragma INTERRUPT(irq_handler, IRQ)
interrupt void irq_handler() {
	printf("irq interrupt\n");
	IntIRQHandler();
}


/**
 * Is called on any sw interrupt request.
 */
#pragma INTERRUPT(swi_handler, IRQ)
interrupt void swi_handler() {
	printf("swi interrupt\n");
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
