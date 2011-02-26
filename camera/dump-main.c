#include "robopoly.h"
#include "lcam.h"

/*
 * 	Demo code to send camera data over UART
 */

#define INTEGRATION 200 // microseconds
#define DELAY 250	// milliseconds

int main (void)
{
	// init
	lcam_initport();
	lcam_reset();
	lcam_setup();

	waitms(20);

	// global vars
	unsigned char buffer[102];
	unsigned char pic_pos = 0;

	unsigned char led_val = 1;

	while(1)
	{
		digitalWrite(C,2,led_val);
		// start acquiring image
		lcam_startintegration();

		waitus(INTEGRATION);
		// end integration
		lcam_stop(buffer);

		// delay between two successive acquisitions
		waitms(DELAY);

		pic_pos = lcam_getpic(buffer);

		// begin frame
		uartSendString("START");
		//uartSendByte(pic_pos);

		
		unsigned char i = 0;
		for(i=0;i<102;i++)
		{
			uartSendByte(buffer[i]);
		}
	

		led_val ^= 1;
	}

	// never reached

}
