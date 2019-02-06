/*
 * B4.c
 *
 * Created: 6-2-2019 12:33:16
 * Author : larsv
 */ 

#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>

typedef struct {
	int output;
	int delay;
} SEGMENTACTION;

const SEGMENTACTION pattern[] = {
	{0x4F, 1000}, {0x59, 1000}, {0x06, 1000},
	{0x01, 250}, {0x02, 250}, {0x04, 250}, {0x08, 250}, {0x10, 250}, {0x20, 250},
	{0x24, 750}, {0x12, 750}, {0x09, 750},
	{0x00, 0}
};

void wait(int ms) {
	for(int i = 0; i < ms; i++) {
		_delay_ms(1);
	}
}

int main(void)
{
	DDRD = 0xFF;
	PORTD = 0x00;
	
	int i;
	while (1)
	{
		i = 0;
		while(pattern[i].delay != 0) {
			PORTD = pattern[i].output;
			wait(pattern[i].delay);
			i++;
		}
	}
}