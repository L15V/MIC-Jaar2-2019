/*
 * B3.c
 *
 * Created: 6-2-2019 11:18:33
 * Author : larsv
 */ 

#define F_CPU 8000000

#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/sleep.h>
#include <util/delay.h>

int digit = 0;
int int0 , int1;

const unsigned char NUMBERS[10] =
{
	0x3F, //0
	0x06, //1
	0x5B, //2
	0x4F, //3
	0x66, //4
	0x6D, //5
	0x7D, //6
	0x07, //7
	0x7F, //8
	0x6F  //9
};

ISR(INT0_vect)
{
	digit++;
	int0 = 1;
}

ISR(INT1_vect){
	digit--;
	int1 = 1;
}

void wait(int ms) {
	for(int i = 0; i < ms; i++) {
		_delay_ms(1);
	}
}

void display(int digit){
	if(digit < 0 || digit > 10) {
		PORTC = 0b01111001;
	}
	else {
		PORTC = NUMBERS[digit];
	}
}

int main(void)
{
    /* Replace with your application code */
	DDRC = 0xFF;
	PORTC = 0x07;
	
	DDRD = 0x00;
	PORTD = 0x00;
	
	EICRA = 0x0F;
	EIMSK = 0x03;

	sei();

    while (1) 
    {
		if(int0 && int1) {
			digit = 0;
			int0 = 0;
			int1 = 0;
		}
		else {
			int0 = 0;
			int1 = 0;
		}
		
		display(digit);
		sleep_mode();
	}
}