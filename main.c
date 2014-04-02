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
#include "kernel.h"
#include <led/dr_led.h>


/*****************************************************************************
**                INTERNAL MACRO DEFINITIONS
*****************************************************************************/



/*****************************************************************************
**                INTERNAL FUNCTION PROTOTYPES
*****************************************************************************/
static void Delay(unsigned int count);


int main(void) {

	InitLedRegister();
	InitLed0();
	InitLed1();
	InitLed2();
	InitLed3();

	  while(1)
	    {
	        /* Driving a logic HIGH on the GPIO pin. */

		  	OnLed0();
	        OnLed1();
	        OnLed2();
	        OnLed3();

	        Delay(0x3FFFF);

	        /* Driving a logic LOW on the GPIO pin. */
	        OffLed0();
	        OffLed1();
	        OffLed2();
	        OffLed3();

	        Delay(0x3FFFF);
	    }



}


/*
** A function which is used to generate a delay.
*/
static void Delay(volatile unsigned int count)
{
    while(count--);
}

