/*
 * B3.c
 *
 * Created: 30-1-2019 11:24:53
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
   DDRC = 0x00; //Alle pins van PORTC op input zetten.
   DDRD = 0xFF;	//Alle pins van PORTD op output zetten.
    while (1) 
    {
		if((PINC & 0b00000001) == 1){ //Kijken of PINC is ingedrukt, want de stroom loopt van de voeding naar de controller dus vandaar dat je kijkt of het signaal 1 is.
			PORTD = 0b10000000;	//Zet pin 7 van port D op hoog
			wait(500);
			PORTD = 0b00000000; // Zet alle pins van port D op laag.
			wait(500);
		}
		else { // Als knop niet is ingedrukt
			PORTD = 0b00000000; //Zet alle pins port D laag
			wait(500);
		}
		
    }
	return 1;
}

