/*
 * B5.c
 *
 * Created: 30-1-2019 12:46:22
 * Author : larsv
 */
#define F_CPU 80000000

#include <avr/io.h>
#include <util/delay.h>

typedef struct {
	unsigned char data;
	unsigned int delay ;
} PATTERN_STRUCT;

PATTERN_STRUCT pattern[] = {
	{0x00, 100}, {0x01, 100}, {0x02, 100}, {0x04, 100}, {0x10, 100}, {0x20, 100}, {0x40, 100}, {0x80, 100},
	{0x00, 100},
	{0xAA,  50}, {0x55,  50},
	{0xAA,  50}, {0x55,  50},
	{0xAA,  50}, {0x55,  50},
	{0x00, 100},
	{0x81, 100}, {0x42, 100}, {0x24, 100}, {0x18, 100}, {0x0F, 200}, {0xF0, 200}, {0x0F, 200}, {0xF0, 200},
	{0x00, 0x00}
};

void wait( int ms ){
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );
	}
}

int main(void)
{
    DDRD = 0b11111111;					// PORTD all output
    
    while (1)
    {
	    int index = 0; //Zet de index op 0 om aan het begin van de array te beginnen.
	    while( pattern[index].delay != 0 ) {//De laatste waarde van de array heeft een delay van 0. Zo geef je het einde aan.
		    PORTD = pattern[index].data; //schrijf de waarde naar portD
		    wait(pattern[index].delay); //Wacht zolang de waarde van delay
		    index++; //Verhoog de inderg om naar de volgende element te gaan.
	    }
    }
}

