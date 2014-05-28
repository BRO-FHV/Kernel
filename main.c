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

int main(void) {
	CPUirqd();
	MmuInit();

	IntControllerInit();

//	EthConfigureWithIP(0xC0A80007u); //0xC0A80007u => 192.168.0.7
	EthConfigureWithDHCP();

	CPUirqe();

	printf("starting echo server...\n");
	EchoStart();

	printf("starting broadcast service... \n");
	BroadcastStart();

	TimerDelaySetup();
	LedInitRegister();
	LedInit0();

	while (1) {
		TimerDelayDelay(500);

		int ledStatus = GPIOPinRead(SOC_GPIO_1_REGS, LED0_PIN);
		if (ledStatus) {
			LedOff0();
		} else {
			LedOn0();
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
