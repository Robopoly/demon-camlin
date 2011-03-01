#include <avr/io.h>

#include "config.h"

#include <util/delay.h>
#include <stdio.h>
#define RAND_MAX 6
#include <stdlib.h>

#include "quadm.h"
#include "uart.h"


#define put(x)	uart_transmit_byte_block(x)

unsigned char bigbuffer[QM_BUFFER_SIZE];

void wait_for_start(void);

int main (void)
{

	_delay_ms(300);
	PORTA = 0x00;
	DDRA = 0b11111111;
	PORTB = 0;
	DDRB = 0xFF;

	//DDRD = 0xFF;
	DDRC |= 0x04;
	
	unsigned char rxbuff[30];
	unsigned char txbuff[30];

	unsigned char lcam_buff[102];

	init_matrix();

	uart_init(0, 0, 0, 0, 0);
	_delay_ms(300);


	while(1)
	{
		put('F');
		uart_receive_byte_block();
		PORTC |= 0x04;

		// listen for input on uart
		unsigned char nops;
		nops = 0;

		// start delimiter is 'START'
		wait_for_start();


		// receive 102 pixels
		int i = 0;
		for(i=0; i<102; i++)
		{
			lcam_buff[i] = uart_receive_byte_block();
		}

		
		// convert 96 of 102 pixels into bargraphs
		for (i = 0; i < 96; i++)
		{
			uint8_t val = 0;
			// conversion from lcam_buff[i+3]
			val = lcam_buff[i+3] >> 4;

			uint16_t bar = 1;
			while(val > 0)
			{
				bar <<= 1;
				bar += 1;
				val--;
			}

			bigbuffer[i*2] = (uint8_t)(bar>>8);
			bigbuffer[i*2+1] = (uint8_t)(bar&0xFF);
		}

		write_array_to_board(bigbuffer,0,QM_BUFFER_SIZE-1);
	}
}


void wait_for_start(void)
{
	unsigned char key[] = "START";
	uint8_t pos = 0;
	unsigned char rxchar = 0;

	put('0');
	while(pos<5)
	{
		// wait for first character
		while(rxchar != key[pos])
		{
			rxchar = uart_receive_byte_block();
			//PORTC |= 0x04;
			//put(rxchar);
		}
		pos++;
		
		// check that all following characters are correct
		while(pos<5)
		{
			rxchar = uart_receive_byte_block();
			if(rxchar == key[pos])
			{
				//put(key[pos]);
				pos++;
			}
			else
			{
				pos=0;
				break;
			}
		}
	}
}

