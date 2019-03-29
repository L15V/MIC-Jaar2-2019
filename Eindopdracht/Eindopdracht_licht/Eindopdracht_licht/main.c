#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <string.h>

#define BIT(x)	(1 << (x))

#define LCD_E 	3
#define LCD_RS	2

typedef struct {
	int red;
	int blue;
} SEGMENTACTION;

const SEGMENTACTION pattern[] = {
	{155, 0}, {120, 20}, {75, 60},{70, 120}, {20, 120}, {0, 155}
};

char toChar[10];

// wait(): busy waiting for 'ms' millisecond
// Used library: util/delay.h
void wait( int ms )
{
	for (int tms=0; tms<ms; tms++)
	{
		_delay_ms( 1 );			// library function (max 30 ms at 8MHz)
	}
}

void timer1Init(void)
{
	OCR0 = 0;
	OCR1B = 0;
	OCR1C = 0;

	TCCR0 |= 1 << WGM00 | 1<<WGM01 | 1 << CS00 | 1<< COM01; //phasecorrect 10 bits mode
	TCCR1A |= 1 << WGM00 | 1<<WGM01 | 1 << CS00 | 1<< COM01;
	TCCR1B = 0b00001011;
}

void setRed(unsigned char redValue)
{
	OCR0 = redValue;
}

void setGreen(unsigned char greenValue)
{
	OCR1B = greenValue;
}

void setBlue(unsigned char blueValue)
{
	OCR1C = blueValue;
}

void adcInit( void )
{
	ADMUX = 0b11100010;//setting the reference of ADC
	ADCSRA |=(1<<ADEN)|(1<<ADFR)|(1<<ADPS0);
	//display_text("test");
}


int main()
{
	DDRF = 0x00;				// set PORTC for input (ADC)
	DDRD = 0xFF;				// set PORTD for output
	DDRC = 0xFF;
	DDRB = 0xFF;				// set PORTB for output
	
	float LDR = 0;
	char output [7];

	adcInit();					// initialize ADC
	timer1Init();
	
	ADCSRA |=(1<<ADSC);
	while (1)
	{
		//LDR=ADC/204.8;
		LDR = ADC / 255;
		dtostrf(LDR, 4, 1, output);
		//sprintf(output, "%d", ADSC);
		//display_text("test");
		memset(output, 0, 7);
		setRed(30 + LDR);
		wait(500);				// every 500 ms (busy waiting)
	}
}