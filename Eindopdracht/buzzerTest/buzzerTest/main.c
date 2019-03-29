/*
 * buzzerTest.c
 *
 * Created: 13-3-2019 11:32:21
 * Author : larsv
 */ 
#define F_CPU 800000

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

/*
void pwm_init()
{
	DDRB = 0xFF;
	TCCR1A=	0b01000010;
	TCCR1B=	0b00011000;
}

void easybuzz_set_frequentie(int frequentie){
	int ms = (int)(1.0/frequentie *1000000.0);

	TCCR1B |= (1<<CS11);
	ICR1 = ms;
	OCR1A = ms/2;
}

void easybuzz_stop(){
	TCCR1B &=~(1 << CS11); 
};*/

int main()
{	
/*
	pwm_init();
	

	while(1)
	{
		easybuzz_set_frequentie(511);
	}
	*/
	DDRB |= (1 << BUZZER_PORT); // Set port as output
	int delay = 0;
	while (1) {
		if (delay < 1) delay = BUZZER_DELAY;
		PORTB |= (1 << BUZZER_PORT);
		_delay_loop_2(delay);
		PORTB &= ~(1 << BUZZER_PORT);
		_delay_loop_2(delay);
		delay--;
	}
	return (0);
}
