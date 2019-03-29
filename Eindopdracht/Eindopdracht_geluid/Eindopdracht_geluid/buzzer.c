/*
 * buzzer.c
 *
 * Created: 27-3-2019 11:29:30
 *  Author: larsv
 */ 

 /*
 * buzzerTest.c
 *
 * Created: 13-3-2019 11:32:21
 * Author : larsv
 */ 

#define BUZZER_PORT PB5
#define BUZZER_DELAY 700

#include <avr/io.h>
#include <util/delay.h>

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

	TCCR0 |= 1 << WGM00 | 1<<WGM01 | 1 << CS00 | 1<< COM01; //phasecorrect 10 bits mode
	TCCR1B = 0b00001011;
}

void BuzzerPlay()
{	
	DDRB = 0xFF;
	timer1Init();

	OCR0 = 255;
	wait(100);
	OCR0 = 0;
	wait(100);
}
