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
//#include <mmu/sc_mmu.h>
#include <eth/broadcast/dr_broadcast.h>
#include <mmu/mmu.h>

#define LEN_IP_ADDR                        (4u)
#define ASCII_NUM_IDX                      (48u)

<<<<<<< HEAD
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
=======
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
>>>>>>> ad789c5bef67aa9fa7ed16875b355030178ceb0e

static void MMUConfigAndEnable(void);


<<<<<<< HEAD
int main(void) {
	CPUirqd();
//	MmuInit();
    MMUConfigAndEnable();

=======
>>>>>>> ad789c5bef67aa9fa7ed16875b355030178ceb0e
	IntControllerInit();

	LedInitRegister();
	LedInit0();
	LedOn0();

	LedInit1();
	LedInit2();
	LedOn2();

	LedInit3();

<<<<<<< HEAD
	TimerConfiguration(Timer_TIMER2, 1000, SchedulerRunNextProcess);
=======
	//TimerConfiguration(Timer_TIMER1MS, 0, Timer1); //ms not needed
	TimerConfiguration(Timer_TIMER2, 1000, Timer1);
	TimerConfiguration(Timer_TIMER3, 2000, Timer2);
	TimerConfiguration(Timer_TIMER4, 3000, Timer3);
	TimerConfiguration(Timer_TIMER5, 4000, Timer4);

	//further possible timers - THEY WORK!
	//TimerConfiguration(Timer_TIMER6, 10000, Timer1);
	//TimerConfiguration(Timer_TIMER7, 12000, Timer1);

	//TimerEnable(Timer_TIMER1MS);
>>>>>>> ad789c5bef67aa9fa7ed16875b355030178ceb0e
	TimerEnable(Timer_TIMER2);
	TimerEnable(Timer_TIMER3);
	TimerEnable(Timer_TIMER4);
	TimerEnable(Timer_TIMER5);

	//further possible timers - THEY WORK!
//	TimerEnable(Timer_TIMER6);
//	TimerEnable(Timer_TIMER7);

	SchedulerStartProcess(&switchLED2ON);
	SchedulerStartProcess(&switchLED2OFF);
	SchedulerStartProcess(&switchLED3ON);
	SchedulerStartProcess(&switchLED3OFF);

	CPUirqe();

<<<<<<< HEAD
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

=======
>>>>>>> ad789c5bef67aa9fa7ed16875b355030178ceb0e
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
}
