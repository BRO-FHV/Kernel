/*
 * Kernel: main.c
 * Part of BRO Project, 2014 <<https://github.com/BRO-FHV>>
 *
 * Created on: 05.03.2014
 * Description:
 * TODO
 */

#include <stdio.h>
#include <stdint.h>
//#include <hw_cm_per.h>
//#include <soc_AM335x.h>
#include "kernel.h"
#include <timer/dr_timer.c>
//#include <dr_interrupt.c>

#define REG_IDX_SHIFT (0x05)
#define REG_BIT_MASK (0x1F)
#define SOC_AINTC_REGS (0x48200000)

#define INTC_MIR_CLEAR(n) (0x88 + ((n) * 0x20))

#define INTC_SIR_IRQ (0x48200040)

void IRQHandle68()
{
	printf("IRQ 86\n");
}

int main(void) {
	_disable_interrupts();

	printf("config timer\n");

	reg32w(SOC_AINTC_REGS, INTC_MIR_CLEAR(68u >> REG_IDX_SHIFT), (0x01 << (68u & REG_BIT_MASK)));

	TimerBasicConfiguration(Timer_TIMER2, 1, 1, (1 << 18), 0x00, 0, 0,0);
	TimerEnable(Timer_TIMER2);

	_enable_interrupts();

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
	//unsigned int irq = reg32r(INTC_SIR_IRQ,0);
	printf("irq interrupt\n");
	//HandleInterrupt(irq);
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
