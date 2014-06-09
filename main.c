/*
 * Kernel: main.c
 * Part of BRO Project, 2014 <<https://github.com/BRO-FHV>>
 *
 * Created on: 05.03.2014
 * Description:
 * Main entry point of the OS. Important initializing is done.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "kernel.h"
#include <interrupt/dr_interrupt.h>
#include <timer/dr_timer.h>
#include <led/dr_led.h>
#include <soc_AM335x.h>
#include <cpu/hw_cpu.h>
#include <scheduler.h>
#include <mmu/sc_mmu.h>
#include <Syscall/lib_syscall.h>
#include <swi/sc_swi.h>
#include <basic.h>

/****************************************************************************/
/*                      INTERNAL MACRO DEFINITIONS                          */
/****************************************************************************/
#define UART_THR_RHR_REG           (SOC_UART_0_REGS)

#define MAX_ACNT                   (1u)
#define MAX_CCNT                   (1u)

#define TX_BUFFER_SIZE             (26u)

/* EDMA3 Event queue number. */
#define EVT_QUEUE_NUM              (0u)

/* PaRAM Set number for Dummy Transfer. */
#define DUMMY_CH_NUM               (5u)

/* UART Module Input Frequency. */
#define UART_MODULE_INPUT_CLK      (48000000u)

/* Baud Rate of UART for communication. */
#define BAUD_RATE_115200           (115200u)

#define TX_THRESHOLD               (1)
#define RX_THRESHOLD               (1)
#define START_ADDR_DDR             (0x80000000)
#define START_ADDR_DEV             (0x44000000)
#define START_ADDR_OCMC            (0x40300000)
#define NUM_SECTIONS_DDR           (512)
#define NUM_SECTIONS_DEV           (960)
#define NUM_SECTIONS_OCMC          (1)

void Delay(void);

#pragma DATA_ALIGN(pageTable, 16384);
static volatile unsigned int pageTable[4 * 1024];

void switchLED2ON() {
	while (1) {
		int i = GPIOPinRead(SOC_GPIO_1_REGS, LED2_PIN);
		if (i == 0) {
			uint32_t* x = (uint32_t*) 0x81200000;
			*x = 5;
			printf("x: %p, *x: %d, i: %d\n", x, *x, i);
			LedOn2();
		}
	}
}
void switchLED2OFF() {
	while (1) {
		int i = GPIOPinRead(SOC_GPIO_1_REGS, LED2_PIN);
		if (i != 0) {
			uint32_t* x = (uint32_t*) 0x81200000;
			*x = 10;
			printf("x: %p, *x: %d, i: %d\n", x, *x, i);
			LedOff2();
		}
	}
}

void switchLED3ON() {
	while (1) {
		int i = GPIOPinRead(SOC_GPIO_1_REGS, LED3_PIN);
		if (i == 0) {
			LedOn3();
		}
	}
}
void switchLED3OFF() {
	while (1) {
		int i = GPIOPinRead(SOC_GPIO_1_REGS, LED3_PIN);
		if (i != 0) {
			LedOff3();
		}
	}
}

int main(void) {

	CPUirqd();

	MmuInit();

	IntControllerInit();

	/*
	LedInitRegister();
	LedInit0();
	LedInit1();
	LedInit2();
	LedInit3();
	*/

	SyscallArgData data17;
	data17.swiNumber = 17;
	Syscall(&data17);

	/*
	 TimerConfiguration(Timer_TIMER2, 1000, SchedulerRunNextProcess);
	 TimerEnable(Timer_TIMER2);

	 SchedulerStartProcess(&switchLED2ON);
	 SchedulerStartProcess(&switchLED2OFF);
	 SchedulerStartProcess(&switchLED3ON);
	 SchedulerStartProcess(&switchLED3OFF);
	 */

	printf("end config start interrupt\n");
	CPUirqe();


	 SyscallArgData data45;
	 data45.swiNumber = 0;
	 char p[255]="\nHallo Franz\n";

	 data45.arg1 = (uint32_t)  p;

	Syscall(&data45);

/*
	SyscallArgData data;
	data.swiNumber = 1;



	Syscall(&data);

	Delay();

	SyscallArgData data2;
	data2.swiNumber = 2;

	Syscall(&data2);

	Delay();

	SyscallArgData data3;
	data3.swiNumber = 5;

	Syscall(&data3);

	Delay();

	SyscallArgData data4;
	data4.swiNumber = 11;
	data4.arg1 = SOC_GPIO_1_REGS;
	data4.arg2 = LED1_PIN;

	Syscall(&data4);

	if (data4.result != 0) {
		LedOn3();
	}
	*/

	while (1) {
		volatile int i = 0;

		for (i = 0; i < 1000000; i++) {
		}
	}
}

/**
 * Is called on any undefined error which caused an abort
 */
#pragma INTERRUPT(udef_handler, UDEF)
interrupt void udef_handler() {
	printf("udef interrupt\n");
}

#pragma INTERRUPT(fiq_handler, FIQ)
interrupt void fiq_handler() {
	printf("fiq interrupt\n");
}

/**
 * Is called on any prefetch abort.
 */
#pragma INTERRUPT(pabt_handler, PABT)
interrupt void pabt_handler() {
	printf("pabt interrupt\n");
}

void Delay(void) {
	volatile int i = 0;

	for (i = 0; i < 1000000; i++) {
	}
}

