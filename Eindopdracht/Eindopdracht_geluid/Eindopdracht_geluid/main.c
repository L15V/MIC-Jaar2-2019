#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <string.h>

#include "buzzer.h"



#define BIT(x)	(1 << (x))

void adcInit( void )
{
	ADMUX = 0b11100001;			// AREF=VCC, result left adjusted, channel1 at pin PF1
	ADCSRA = 0b11100110;		// ADC-enable, no interrupt, start, free running, division by 64
}

void timer1MInit(void)
{
	OCR1B = 0;

	TCCR1A |= 1 << WGM00 | 1<<WGM01 | 1 << CS00 | 1<< COM01; //phasecorrect 10 bits mode
	TCCR1B = 0b00001011;
}

int main( void )
{
	timer1MInit();
	DDRB = 0xFF;
	DDRD = 0xFF;
	DDRF = 0;	//Taking portF as input.
	adcInit();
	ADCSRA |= (1<<ADSC);  //starting the ADC conversion
	float i = 0;

	while (1)
	{
		i = ADC;

		if(i > /*54400*/ 54100){
			PORTD ^= (1<<7);	// Toggle PORTD.7
			wait(100);

			OCR1B = 255;
			wait(100);

			//Do something when it is too loud
			//TODO make this wotk with the buzzer and figure out what the best value is for the sound recognition
		}
		else{
			OCR1B = 0;
		}
	}
}