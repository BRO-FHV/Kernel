/*
 * Kernel: main.c
 * Part of BRO Project, 2014 <<https://github.com/BRO-FHV>>
 *
 * Created on: 05.03.2014
 * Description:
 * TODO
 */
int main(void) {
	
	_enable_interrupts();

	while(1) {

	}
	return 0;
}


/**
 * Is called on any interrupt request.
 */
#pragma INTERRUPT(irq_handle, IRQ)
interrupt void irq_handle()
{


}

void xdc_runtime_Startup_reset__I() {

}
