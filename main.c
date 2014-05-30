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
#include <interrupt/dr_interrupt.h>
#include <eth/dr_eth.h>
#include <soc_AM335x.h>
#include <cpu/hw_cpu.h>
#include <eth/echo/dr_echo.h>
#include <timer/dr_timer.h>
#include <led/dr_led.h>
#include <soc_AM335x.h>
#include <cpu/hw_cpu.h>
#include <mmu/sc_mmu.h>
#include <eth/broadcast/dr_broadcast.h>

void test(){
	uint32_t ipAddr = EthConfigureWithDHCP();

	if(0 != ipAddr) {
		printf("starting echo server...\n");
		EchoStart();

		printf("starting broadcast service... \n");
		BroadcastStart();
	} else {
		printf("Ethernet setup failed... ");
	}
}

int main(void) {
	CPUirqd();
	MmuInit();

	IntControllerInit();

	//ALWAYS CONFIGURE DELAY TIMER FIRST!
	//AND ENABLE INTERRUPTS AFTERWARDS
	TimerDelaySetup();

	TimerConfiguration(Timer_TIMER2, 1000, SchedulerRunNextProcess);
	TimerEnable(Timer_TIMER2);

	SchedulerStartProcess(&test);

	CPUirqe();

//	uint32_t ipAddr = EthConfigureWithIP(0xC0A80007u); //0xC0A80007u => 192.168.0.7


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
