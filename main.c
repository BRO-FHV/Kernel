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
#include <eth/dr_eth_udp.h>

#define PORT 2000

void udp_echo() {
	BroUdpInit(PORT);

	while (1) {
		if (BroUdpHasData(PORT)) {
			printf("echo\n");

			upd_package_t* package = BroUdpGetData(PORT);
			BroUdpSendData(package->sender, PORT, package->data, package->len);

			free(package->data);
			package->data = NULL;
			package->len = 0;
		}
	}
}

int main(void) {
	CPUirqd();
	MmuInit();

	IntControllerInit();

	//ALWAYS CONFIGURE DELAY TIMER FIRST!
	//AND ENABLE INTERRUPTS AFTERWARDS
	TimerDelaySetup();


	CPUirqe();

	uint32_t ipAddr = EthConfigureWithIP(0xC0A80007u); //0xC0A80007u => 192.168.0.7

	if(0 != ipAddr) {
		printf("start listening\n");

		CPUirqd();

		TimerConfiguration(Timer_TIMER2, 2000, SchedulerRunNextProcess);
		TimerEnable(Timer_TIMER2);
		SchedulerStartProcess(&udp_echo);

		CPUirqe();
		TimerEnable(Timer_TIMER2);


		while (1) {
			volatile int i = 0;

			for (i = 0; i < 1000000; i++) {
			}
		}
	} else {
		printf("Ethernet setup failed... \n");
		printf("Shut down... \n");

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
