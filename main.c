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
#include <dmtimer.h>
//
//static void DMTimerSetUp(void);
//
//void DMTimer3ModuleClkConfig(void)
//{
//    HWREG(SOC_CM_PER_REGS + CM_PER_L3S_CLKSTCTRL) =
//                             CM_PER_L3S_CLKSTCTRL_CLKTRCTRL_SW_WKUP;
//
////    while((HWREG(SOC_CM_PER_REGS + CM_PER_L3S_CLKSTCTRL) &
////     CM_PER_L3S_CLKSTCTRL_CLKTRCTRL) != CM_PER_L3S_CLKSTCTRL_CLKTRCTRL_SW_WKUP);
////
////    HWREG(SOC_CM_PER_REGS + CM_PER_L3_CLKSTCTRL) =
////                             CM_PER_L3_CLKSTCTRL_CLKTRCTRL_SW_WKUP;
////
////    while((HWREG(SOC_CM_PER_REGS + CM_PER_L3_CLKSTCTRL) &
////     CM_PER_L3_CLKSTCTRL_CLKTRCTRL) != CM_PER_L3_CLKSTCTRL_CLKTRCTRL_SW_WKUP);
////
////    HWREG(SOC_CM_PER_REGS + CM_PER_L3_INSTR_CLKCTRL) =
////                             CM_PER_L3_INSTR_CLKCTRL_MODULEMODE_ENABLE;
////
////    while((HWREG(SOC_CM_PER_REGS + CM_PER_L3_INSTR_CLKCTRL) &
////                               CM_PER_L3_INSTR_CLKCTRL_MODULEMODE) !=
////                                   CM_PER_L3_INSTR_CLKCTRL_MODULEMODE_ENABLE);
////
////    HWREG(SOC_CM_PER_REGS + CM_PER_L3_CLKCTRL) =
////                             CM_PER_L3_CLKCTRL_MODULEMODE_ENABLE;
////
////    while((HWREG(SOC_CM_PER_REGS + CM_PER_L3_CLKCTRL) &
////        CM_PER_L3_CLKCTRL_MODULEMODE) != CM_PER_L3_CLKCTRL_MODULEMODE_ENABLE);
////
////    HWREG(SOC_CM_PER_REGS + CM_PER_OCPWP_L3_CLKSTCTRL) =
////                             CM_PER_OCPWP_L3_CLKSTCTRL_CLKTRCTRL_SW_WKUP;
////
////    while((HWREG(SOC_CM_PER_REGS + CM_PER_OCPWP_L3_CLKSTCTRL) &
////                              CM_PER_OCPWP_L3_CLKSTCTRL_CLKTRCTRL) !=
////                                CM_PER_OCPWP_L3_CLKSTCTRL_CLKTRCTRL_SW_WKUP);
////
////    HWREG(SOC_CM_PER_REGS + CM_PER_L4LS_CLKSTCTRL) =
////                             CM_PER_L4LS_CLKSTCTRL_CLKTRCTRL_SW_WKUP;
////
////    while((HWREG(SOC_CM_PER_REGS + CM_PER_L4LS_CLKSTCTRL) &
////                             CM_PER_L4LS_CLKSTCTRL_CLKTRCTRL) !=
////                               CM_PER_L4LS_CLKSTCTRL_CLKTRCTRL_SW_WKUP);
////
////    HWREG(SOC_CM_PER_REGS + CM_PER_L4LS_CLKCTRL) =
////                             CM_PER_L4LS_CLKCTRL_MODULEMODE_ENABLE;
////
////    while((HWREG(SOC_CM_PER_REGS + CM_PER_L4LS_CLKCTRL) &
////      CM_PER_L4LS_CLKCTRL_MODULEMODE) != CM_PER_L4LS_CLKCTRL_MODULEMODE_ENABLE);
////
////    /* Select the clock source for the Timer2 instance. */
////    HWREG(SOC_CM_DPLL_REGS + CM_DPLL_CLKSEL_TIMER3_CLK) &=
////          ~(CM_DPLL_CLKSEL_TIMER3_CLK_CLKSEL);
////
////    HWREG(SOC_CM_DPLL_REGS + CM_DPLL_CLKSEL_TIMER3_CLK) |=
////          CM_DPLL_CLKSEL_TIMER3_CLK_CLKSEL_CLK_M_OSC;
////
////    while((HWREG(SOC_CM_DPLL_REGS + CM_DPLL_CLKSEL_TIMER3_CLK) &
////           CM_DPLL_CLKSEL_TIMER3_CLK_CLKSEL) !=
////           CM_DPLL_CLKSEL_TIMER3_CLK_CLKSEL_CLK_M_OSC);
////
////    HWREG(SOC_CM_PER_REGS + CM_PER_TIMER3_CLKCTRL) |=
////                             CM_PER_TIMER3_CLKCTRL_MODULEMODE_ENABLE;
////
////    while((HWREG(SOC_CM_PER_REGS + CM_PER_TIMER3_CLKCTRL) &
////    CM_PER_TIMER3_CLKCTRL_MODULEMODE) != CM_PER_TIMER3_CLKCTRL_MODULEMODE_ENABLE);
////
////    while((HWREG(SOC_CM_PER_REGS + CM_PER_TIMER3_CLKCTRL) &
////       CM_PER_TIMER3_CLKCTRL_IDLEST) != CM_PER_TIMER3_CLKCTRL_IDLEST_FUNC);
////
////    while(!(HWREG(SOC_CM_PER_REGS + CM_PER_L3S_CLKSTCTRL) &
////            CM_PER_L3S_CLKSTCTRL_CLKACTIVITY_L3S_GCLK));
////
////    while(!(HWREG(SOC_CM_PER_REGS + CM_PER_L3_CLKSTCTRL) &
////            CM_PER_L3_CLKSTCTRL_CLKACTIVITY_L3_GCLK));
////
////    while(!(HWREG(SOC_CM_PER_REGS + CM_PER_OCPWP_L3_CLKSTCTRL) &
////           (CM_PER_OCPWP_L3_CLKSTCTRL_CLKACTIVITY_OCPWP_L3_GCLK |
////            CM_PER_OCPWP_L3_CLKSTCTRL_CLKACTIVITY_OCPWP_L4_GCLK)));
////
////    while(!(HWREG(SOC_CM_PER_REGS + CM_PER_L4LS_CLKSTCTRL) &
////           (CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_L4LS_GCLK |
////            CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_TIMER3_GCLK)));
//
//}
//
//void DMTimerCounterSet(unsigned int baseAdd, unsigned int counter)
//{
//    /* Wait for previous write to complete */
//    //DMTimerWaitForWrite(DMTIMER_WRITE_POST_TCRR, baseAdd);
//
//    /* Set the counter value */
//    HWREG(baseAdd + TCRR) = counter;
//}
//
//void DMTimerReloadSet(unsigned int baseAdd, unsigned int reload)
//{
//    /* Wait for previous write to complete */
//    //DMTimerWaitForWrite(DMTIMER_WRITE_POST_TLDR, baseAdd);
//
//    /* Load the register with the re-load value */
//    HWREG(baseAdd + TLDR) = reload;
//}
//
//void DMTimerModeConfigure(unsigned int baseAdd, unsigned int timerMode)
//{
//    /* Wait for previous write to complete */
//    //DMTimerWaitForWrite(DMTIMER_WRITE_POST_TCLR, baseAdd);
//
//    /* Clear the AR and CE field of TCLR */
//    HWREG(baseAdd + TCLR) &= ~(DMTIMER_TCLR_AR | DMTIMER_TCLR_CE);
//
//    /* Wait for previous write to complete */
//    //DMTimerWaitForWrite(DMTIMER_WRITE_POST_TCLR, baseAdd);
//
//    /* Set the timer mode in TCLR register */
//    HWREG(baseAdd + TCLR) |= (timerMode & (DMTIMER_TCLR_AR | DMTIMER_TCLR_CE));
//}
//
///*
//** Setup the timer for one-shot and compare mode.
//*/
//static void DMTimerSetUp(void)
//{
//
////		INTC_ILR_GTP2 |= 0x04; //set priority of interrupt
////		INTC_MIRCLEAR_GTP2 |= 0x40; //unmask interrupt
//
//
//	DMTimer3ModuleClkConfig();
//
//    /* Load the counter with the initial count value */
//    DMTimerCounterSet(SOC_DMTIMER_2_REGS, TIMER_INITIAL_COUNT);
//
//    /* Load the load register with the reload count value */
//    DMTimerReloadSet(SOC_DMTIMER_2_REGS, TIMER_RLD_COUNT);
//
//    /* Configure the DMTimer for Auto-reload and compare mode */
//    DMTimerModeConfigure(SOC_DMTIMER_2_REGS, DMTIMER_AUTORLD_NOCMP_ENABLE);
//
//	(*((volatile unsigned long*)DMTIMER2 + TCLR)) &= ~0x01; //stop
//	(*((volatile unsigned long*)DMTIMER2 + TTGR)) = 0x00; //ResetTimer Value
//	(*((volatile unsigned long*)DMTIMER2 + TISR)) |= 0x03; //Clear Interrupt bits
//	(*((volatile unsigned long*)DMTIMER2 + TIER)) |= 0x01; //enable interrupts for gpt2
//	(*((volatile unsigned long*)DMTIMER2 + TMAR))  = 10000; //set compare value
//	(*((volatile unsigned long*)DMTIMER2 + TCLR)) |= 0x40; //Enable Compare mode
//	(*((volatile unsigned long*)DMTIMER2 + TLDR)) = 0x0; //set resetvalue to 0
//	(*((volatile unsigned long*)DMTIMER2 + TCLR)) |= 0x02; //autoreload
//	(*((volatile unsigned long*)DMTIMER2 + TCLR)) |= 0x01; //start
//}
#define SOC_AINTC_REGS (0x48200000)

#define INTC_MIR_CLEAR(n) (0x88 + ((n) * 0x20))

int main(void) {

//	printf("disable interrups\n");
//	_disable_interrupts();
//	_disable_IRQ();
//	_disable_FIQ();
//
//	DMTimerSetUp();
//	printf("enable interrups\n");
//	_enable_interrupts();
//	_enable_IRQ();
//	_enable_FIQ();

/*
 *

	_disable_interrupts();

	printf("config timer\n");

	// Disable the system interrupt in the corresponding MIR_CLEAR register
	HWREG(SOC_AINTC_REGS + INTC_MIR_CLEAR(68 >> 0x05)) =
			(0x01 << (68 & 0x1F));

	//reg32m(INTC_MIR_CLEAR1, 0, (1 << 6));
	reg32w(DMTIMER2, TIER, 1);
	reg32w(DMTIMER2, TMAR, (1 << 18));
	reg32w(DMTIMER2, TLDR, 0x00);
	reg32w(DMTIMER2, TWER, 0x01);
	reg32w(DMTIMER2, TISR, 0x03);
	reg32w(DMTIMER2, TTGR, 0x00);
	reg32w(DMTIMER2, TCLR, (1 << 6) | 0x03);
	reg32w(DMTIMER2, TCRR, 0x00);

	_enable_interrupts();

	printf("started - now wait!\n");

	*/

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
}

/**
 * Is called on any sw interrupt request.
 */
#pragma INTERRUPT(swi_handler, IRQ)
interrupt void swi_handler() {
	printf("irq interrupt\n");
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
