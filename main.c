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


void Timer1()
{
	int i = GPIOPinRead(SOC_GPIO_1_REGS, LED0_PIN);
	if(i==0)
	{
		LedOn0();
	}
	else
	{
		LedOff0();
	}
}

void Timer2()
{
	int i = GPIOPinRead(SOC_GPIO_1_REGS, LED1_PIN);
	if(i==0)
	{
		LedOn1();
	}
	else
	{
		LedOff1();
	}
}

void Timer3()
{
	int i = GPIOPinRead(SOC_GPIO_1_REGS, LED2_PIN);
	if(i==0)
	{
		LedOn2();
	}
	else
	{
		LedOff2();
	}
}

void Timer4()
{
	int i = GPIOPinRead(SOC_GPIO_1_REGS, LED3_PIN);
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

	IntControllerInit();

	LedInitRegister();
	LedInit0();
	LedOn0();

	LedInit1();
	LedInit2();
	LedOn2();

	LedInit3();

	//TimerConfiguration(Timer_TIMER1MS, 0, Timer1); //ms not needed
	TimerConfiguration(Timer_TIMER2, 2000, Timer1);
	TimerConfiguration(Timer_TIMER3, 4000, Timer2);
	TimerConfiguration(Timer_TIMER4, 6000, Timer3);
	TimerConfiguration(Timer_TIMER5, 8000, Timer4);

	//further possible timers - THEY WORK!
	//TimerConfiguration(Timer_TIMER6, 10000, Timer1);
	//TimerConfiguration(Timer_TIMER7, 12000, Timer1);

	//TimerEnable(Timer_TIMER1MS);
	TimerEnable(Timer_TIMER2);
	TimerEnable(Timer_TIMER3);
	TimerEnable(Timer_TIMER4);
	TimerEnable(Timer_TIMER5);

	//further possible timers - THEY WORK!
//	TimerEnable(Timer_TIMER6);
//	TimerEnable(Timer_TIMER7);

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
