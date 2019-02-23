/*
 * B2.c
 *
 * Created: 23-2-2019 18:42:50
 * Author : larsv
 */ 

#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BIT(x)	(1 << (x)) //Shifts the value by x

// wait(): busy waiting for 'ms' millisecond
// Used library: util/delay.h
void wait( int ms )
{
	for (int tms=0; tms<ms; tms++)
	{
		_delay_ms( 1 );			// library function (max 30 ms at 8MHz)
	}
}


// Initialize ADC: 10-bits (left justified), free running
void adcInit( void )
{
	ADMUX = 0x63;			// AREF=VCC, result left adjusted, channel1 at pin PF1
	ADCSRA = 0x86;		// ADC-enable, no interrupt, start, free running, division by 64
}


// Main program: ADC at PF1
int main( void )
{
	DDRF = 0x00;				// set PORTF for input (ADC)
	DDRA = 0xFF;				// set PORTA for output
	DDRC = 0x01;
	adcInit();					// initialize ADC

	while (1)
	{
		ADCSRA |= BIT(6);		//Equals ADCSRA |= (1<<6)
		while (ADCSRA & BIT(6));//Waits to complete the poll
		PORTA = ADCH;
		PORTC ^= 1;				//Status led
		wait(250);				// every 100 ms (busy waiting)
	}
}

