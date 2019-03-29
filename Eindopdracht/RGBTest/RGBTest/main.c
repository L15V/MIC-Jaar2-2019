/*
 * RGBTest.c
 *
 * Created: 27-3-2019 09:11:31
 * Author : larsv
 */ 

#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>

typedef struct {
	int red;
	int blue;
} SEGMENTACTION;

const SEGMENTACTION pattern[] = {
	{255, 0}, {200, 50}, {150, 100},{100, 150}, {50, 200}, {0, 255}
};

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

int main(void)
{
	DDRB = 0xFF;
	timer1Init();
	wait(100);
    /*Replace with your application code */
	while (1) 
    {
		for(int i = 0; i < 6 ; i++){
		setRed(pattern[i].red);
		setBlue(pattern[i].blue);

			if(i == 5){
				i = 0;
			}
			wait(1000);
		}
    }
	return 0;
}