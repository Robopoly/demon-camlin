#include "robopoly.h"
#include "lcam.h"
#include <avr/io.h>

/*
 * 	Test program to convert 0-255 to 16bit bargraph
 */

#define INTEGRATION 220 // microseconds
#define DELAY 500	// milliseconds

uint16_t char_to_bargraph(unsigned char c);

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
			uartSendByte((buffer[i]>>3)+'0');
			//waitus(100);
		}

		uartSendByte('\0');
	

		led_val ^= 1;
	}

	// never reached

}

// convert an unsigned char (0-255) to a 16-bit bargraph (0-16 active pixels)
uint16_t char_to_bargraph(unsigned char c)
{
	c >>= 4; // divide by 16
	uint16_t out = 1;

	while(c>0)
	{
		out = out + (out<<1);
	}

	return out;
}
