/*
 * Kernel: main.c
 * Part of BRO Project, 2014 <<https://github.com/BRO-FHV>>
 *
 * Created on: 05.03.2014
 * Description:
 * TODO
 */

#include<scheduler.h>
#include<hal.h>

void BlinkLed0() {
	while(1) {
		GPIO5_OUT ^= LED0;
	}
}
void BlinkLed1() {
	while(1) {
		GPIO5_OUT ^= LED1;
	}
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
		for(i=0; i<0x100000; i++) { }

		scheduler_runNextProcess();
	}
}
