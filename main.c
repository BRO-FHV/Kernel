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

#include <soc_AM335x.h>

#include <eth/dr_eth.h>
#include <eth/dr_eth_udp.h>
#include <interrupt/dr_interrupt.h>
#include <timer/dr_timer.h>
#include <led/dr_led.h>
#include <cpu/hw_cpu.h>
#include <mmu/sc_mmu.h>
#include <sd/dr_sd.h>
#include <sd/thirdParty/fatfs/src/ff.h>

#include <Led/lib_led.h>
#include <stdlib/stdlib.h>
#include <Eth/lib_eth.h>

#include <list/linkedlist.h>

#define PORT					2000
#define LENGTH_USERNAME 		7 //Byte
#define CMD_LED					1

uint8_t BROADCAST_IP[] = { 255, 255, 255, 255 };

typedef struct {
	uint8_t username[LENGTH_USERNAME];
	uint8_t cmd;
} tCmd;

typedef struct {
	tCmd cmd;
	uint8_t led;
	uint8_t state;
} tCmd_Led;


/*
int asdf(void) {
	BroUdpInit(PORT);

	while (1) {
		if (BroUdpHasData(PORT)) {
			udp_package_t* package = BroUdpGetData(PORT);
			tCmd* command = (tCmd*) (package->data);

			if (CMD_LED == command->cmd) {
				tCmd_Led* ledCmd = (tCmd_Led*) (package->data);

				if (ledCmd->led >= 1 && ledCmd->led <= 4) {
					switch (ledCmd->led) {
					case 2:
						if (ledCmd->state) {
							LedOn1();
						} else {
							LedOff1();
						}
						break;
					case 3:
						if (ledCmd->state) {
							LedOn2();
						} else {
							LedOff2();
						}
						break;
					case 4:
						if (ledCmd->state) {
							LedOn3();
						} else {
							LedOff3();
						}
						break;
					}

					//BROADCAST TO ALL LISTENERS
					BroUdpSendData(BROADCAST_IP, PORT, package->data, package->len);
				}
			}

			free(package->data);
			package->data = NULL;
			package->len = 0;
		}
	}
}
*/


int BroUDP(void) {
	lib_udp_init(PORT);

	while (1) {
		if (lib_udp_has_data(PORT)) {
			lib_udp_package_t* package = lib_udp_get_data(PORT);
			tCmd* command = (tCmd*) (package->data);

			if (CMD_LED == command->cmd) {
				tCmd_Led* ledCmd = (tCmd_Led*) (package->data);

				if (ledCmd->led >= 1 && ledCmd->led <= 4) {
					switch (ledCmd->led) {
					case 1:
						if (ledCmd->state) {
							lib_led_on_0();
						} else {
							lib_led_off_0();
						}
						break;
					case 2:
						if (ledCmd->state) {
							lib_led_on_1();
						} else {
							lib_led_off_1();
						}
						break;
					case 3:
						if (ledCmd->state) {
							lib_led_on_2();
						} else {
							lib_led_off_2();
						}
						break;
					case 4:
						if (ledCmd->state) {
							lib_led_on_3();
						} else {
							lib_led_off_3();
						}
						break;
					}
				}
			}

			//BROADCAST TO ALL LISTENERS
			lib_udp_send_data(BROADCAST_IP, PORT, package->data, package->len);

			lib_free(package->data);
			package->data = NULL;
			package->len = 0;
		}
	}
}

int main(void) {
	CPUirqd();
	MmuInit();

	LedInitRegister();
	LedInit0();
	LedInit1();
	LedInit2();
	LedInit3();

	IntControllerInit();

	//ALWAYS CONFIGURE DELAY TIMER FIRST!
	//AND ENABLE INTERRUPTS AFTERWARDS
	TimerDelaySetup();

	CPUirqe();

	// load elf
//	startFileSystem();
//	FILINFO fi;
//
//	if (f_stat("BRO_LED.out", &fi) == FR_OK) {
//		uint8_t* dataBuff = malloc(fi.fsize);
//		getElfFile(dataBuff, fi.fsize, "BRO_LED.out");
//
//		// start a process
//		loadProcessFromElf(0, dataBuff);
//		free(dataBuff);
//	}

	uint32_t ipAddr = EthConfigureWithIP(0xC0A80007u); //0xC0A80007u => 192.168.0.7

	if (0 != ipAddr) {
		printf("start listening\n");
		// init timer
		SchedulerStartProcess(BroUDP);

		TimerConfiguration(Timer_TIMER2, 1000, SchedulerRunNextProcess);
		TimerEnable(Timer_TIMER2);

		while (1) {
			volatile int i = 0;

			for (i = 0; i < 1000000; i++) {
			}
		}
	} else {
		printf("Ethernet setup failed... \n");
		printf("Shut down... \n");
		while (1) {

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
