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
#include <mmu/sc_mmu.h>

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

#pragma DATA_ALIGN(pageTable, 16384);
static volatile unsigned int pageTable[4*1024];

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
		if (i!=0) {
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
		if (i!=0) {
			LedOff3();
		}
	}
}






int main(void) {


	CPUirqd();


	mmu_init();

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

	/*printf("started - now wait!\n");*/
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
	mmu_handle_data_abort();
}
