/*
 * B4.c
 *
 * Created: 30-1-2019 12:30:34
 * Author : larsv
 */ 
#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>

void wait( int ms ){
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );
	}
}

int main(void)
{
	DDRD = 0xFF; //Zet alle pins op portD op output
    
    while (1) 
    {
		PORTD = 0x01; //Zet het eerste ledje aan
		while(PORTD != 0){
			wait(50);
			PORTD <<= 1; //Als je niet het eerste ledje hebt bitshift dan 1 plaats zodat je steeds het volgende ledje hebt.
		}
    }
}

