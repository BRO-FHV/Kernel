/*
 * Kernel: kernel.c
 * Part of BRO Project, 2014 <<https://github.com/BRO-FHV>>
 *
 * Created on: 05.03.2014
 * Description:
 * TODO
 */

#define HWREG(x)	(*((volatile unsigned int *)(x)))
#define reg32r(b, r) (*(volatile uint32_t *)((b)+(r)))
#define reg32w(b, r, v) (*((volatile uint32_t *)((b)+(r))) = (v))

#define GPTIMER2_BASE 0x48040000

#define GPTIMER_TMAR 0x038 // compare value

#define GPTIMER_TIER 0x01C // controls interrupt events (match, overflow, capture)
#define GPTIMER_TCLR 0x024 //
#define GPTIMER_TCRR 0x028 // timer counter
#define GPTIMER_TLDR 0x02C // timer load value
#define GPTIMER_TWER 0x020 //
#define GPTIMER_TISR 0x018
#define GPTIMER_TTGR 0x030 // timer reloads if written

#define GPTIMER_MATCH 1
#define GPTIMER_OVF (1<<1)
#define GPTIMER_CAPT (1<<2)



#define INTCPS_MIR_CLEAR1 0x482000A8
#define INTCPS_SIR_IRQ 0x48200040
