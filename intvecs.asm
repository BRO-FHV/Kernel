.global _c_int00
.global C_INTIRQ
.global tim1_int
.sect ".intvecs"
B _c_int00 ; reset interrupt
.word 0 ; undefined instruction interrupt
.word 0 ; software interrupt
.word 0 ; abort (prefetch) interrupt
.word 0 ; abort (data) interrupt
.word 0 ; reserved
B C_INTIRQ ; IRQ interrupt
B tim1_int ; FIQ interrupt
