/*
 * B2.c
 *
 * Created: 30-1-2019 11:01:36
 * Author : larsv
 */ 
 #define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>

void wait( int ms )
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}


int main(void)
{
	DDRD = 0xFF; // Zet PortD op output
    while (1) 
    {
		PORTD= 0xAA; //schrijf 10101010b wat om en om een led aan en uit zet
		wait(500);
		PORTD= 0x55; // schrijft binair het omgekeerde van het bovengenoemde statement
		wait(500);
    }

	return 1;
}

