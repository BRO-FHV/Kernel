/*
 * Kernel: main.c
 * Part of BRO Project, 2014 <<https://github.com/BRO-FHV>>
 *
 * Created on: 05.03.2014
 * Description:
 * Main entry point of the OS. Important initializing is done.
 */

<<<<<<< HEAD
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
//#include <mmu/sc_mmu.h>
#include <eth/broadcast/dr_broadcast.h>
#include <mmu/mmu.h>

#define LEN_IP_ADDR                        (4u)
#define ASCII_NUM_IDX                      (48u)

#define START_ADDR_DDR                     (0x80000000)
#define START_ADDR_DEV                     (0x44000000)
#define START_ADDR_OCMC                    (0x40300000)
#define NUM_SECTIONS_DDR                   (512)
#define NUM_SECTIONS_DEV                   (960)
#define NUM_SECTIONS_OCMC                  (1)

/******************************************************************************
**                      INTERNAL VARIABLE DEFINITIONS
*******************************************************************************/
/* Page tables start must be aligned in 16K boundary */
#pragma DATA_ALIGN(pageTable, MMU_PAGETABLE_ALIGN_SIZE);
static volatile unsigned int pageTable[MMU_PAGETABLE_NUM_ENTRY];

static void MMUConfigAndEnable(void);


int main(void) {
	CPUirqd();
//	MmuInit();
    MMUConfigAndEnable();

	IntControllerInit();

	LedInitRegister();
	LedInit2();
	LedInit3();

	TimerConfiguration(Timer_TIMER2, 1000, SchedulerRunNextProcess);
	TimerEnable(Timer_TIMER2);

	SchedulerStartProcess(&switchLED2ON);
	SchedulerStartProcess(&switchLED2OFF);
	SchedulerStartProcess(&switchLED3ON);
	SchedulerStartProcess(&switchLED3OFF);

	CPUirqe();

	//uint32_t ipAddr = EthConfigureWithIP(0xC0A80007u); //0xC0A80007u => 192.168.0.7
	uint32_t ipAddr = EthConfigureWithDHCP();
	if(0 != ipAddr) {
		printf("starting echo server...\n");
		EchoStart();

//		printf("starting broadcast service... \n");
//		BroadcastStart();
	} else {
		printf("Ethernet setup failed... ");
	}

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

void MMUConfigAndEnable(void)
{
    /*
    ** Define DDR memory region of AM335x. DDR can be configured as Normal
    ** memory with R/W access in user/privileged modes. The cache attributes
    ** specified here are,
    ** Inner - Write through, No Write Allocate
    ** Outer - Write Back, Write Allocate
    */
    REGION regionDdr = {
                        MMU_PGTYPE_SECTION, START_ADDR_DDR, NUM_SECTIONS_DDR,
                        MMU_MEMTYPE_NORMAL_NON_SHAREABLE(MMU_CACHE_WT_NOWA,
                                                         MMU_CACHE_WB_WA),
                        MMU_REGION_NON_SECURE, MMU_AP_PRV_RW_USR_RW,
                        (unsigned int*)pageTable
                       };
    /*
    ** Define OCMC RAM region of AM335x. Same Attributes of DDR region given.
    */
    REGION regionOcmc = {
                         MMU_PGTYPE_SECTION, START_ADDR_OCMC, NUM_SECTIONS_OCMC,
                         MMU_MEMTYPE_NORMAL_NON_SHAREABLE(MMU_CACHE_WT_NOWA,
                                                          MMU_CACHE_WB_WA),
                         MMU_REGION_NON_SECURE, MMU_AP_PRV_RW_USR_RW,
                         (unsigned int*)pageTable
                        };

    /*
    ** Define Device Memory Region. The region between OCMC and DDR is
    ** configured as device memory, with R/W access in user/privileged modes.
    ** Also, the region is marked 'Execute Never'.
    */
    REGION regionDev = {
                        MMU_PGTYPE_SECTION, START_ADDR_DEV, NUM_SECTIONS_DEV,
                        MMU_MEMTYPE_STRONG_ORD_SHAREABLE,
                        MMU_REGION_NON_SECURE,
                        MMU_AP_PRV_RW_USR_RW  | MMU_SECTION_EXEC_NEVER,
                        (unsigned int*)pageTable
                       };

    /* Initialize the page table and MMU */
    MMUInit((unsigned int*)pageTable);

    /* Map the defined regions */
    MMUMemRegionMap(&regionDdr);
    MMUMemRegionMap(&regionOcmc);
    MMUMemRegionMap(&regionDev);

    /* Now Safe to enable MMU */
    MMUEnable((unsigned int*)pageTable);
=======
#include<scheduler.h>
#include<hal.h>

void BlinkLed0() {
	GPIO5_OUT ^= LED0;
}
void BlinkLed1() {
	GPIO5_OUT ^= LED1;
}

int main(void) {
	long int i;
	// Set the pinmux to select the GPIO signal
	CONTROL_PADCONF_UART1_TX &= 0x0000FFFF; //  [31:16]=GPIO_149  - Clear register bits [31:16]
	CONTROL_PADCONF_UART1_TX |= 0x00040000; //  [31:16]=GPIO_149  - select mux mode 4 for gpio
	CONTROL_PADCONF_UART1_CTS &= 0xFFFF0000; //  [15:0] =GPIO_150  - Clear register [15:0]
	CONTROL_PADCONF_UART1_CTS |= 0x00000004; //  [15:0] =GPIO_150  - select mux mode 4 for gpio

	// Switch on the Interface and functional clocks to the GPIO5 module
	CM_FCLKEN_PER |= 0xFFFFFFF; // Enable GPIO5 F clock
	CM_ICLKEN_PER |= 0xFFFFFFF; // Enable GPIO5 I clock

	// Configure the GPIO signals
	GPIO5_OE &= ~(LED1+LED0); // Set GPIO_149 & GPIO_150 (GPIO 4 bit 2) to output
	GPIO5_OUT |= LED0; // Set GPIO_150 high
	GPIO5_OUT &= ~LED1; // Set GPIO_149 low

	scheduler_startProcess(BlinkLed0);
	scheduler_startProcess(BlinkLed1);
	
	while(1) {
		scheduler_runNextProcess();
	}
>>>>>>> 3e37609f19c2026ea1641580c0c4d5905cc3eb77
}
