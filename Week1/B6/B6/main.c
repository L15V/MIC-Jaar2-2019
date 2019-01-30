/*
 * B6.c
 *
 * Created: 30-1-2019 13:04:01
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
    DDRD = 0b11111111;
    int delayInt = 500;
    int pushed = 0;

    while(1)
    {
	    PORTD = 0x10;
	    wait(delayInt);
	    PORTD = 0x00;
	    wait(delayInt);

	    if(PINC & 0x01)
	    {
		    if(delayInt == 500 && pushed == 0)
		    delayInt = 125;
		    else if(delayInt == 125 && pushed == 0)
		    delayInt = 500;
		    
		    pushed = 1;
	    }
	    else{
		    pushed = 0;
	    }
    }
}

