/*
 * B1.c
 *
 * Created: 13-2-2019 10:53:54
 * Author : larsv
 */ 
 #define F_CPU 8000000

 #include <avr/io.h>
 #include <util/delay.h>
 #include "lcd.h"

 void wait(int ms) {
	 for(int i = 0; i < ms; i++) {
		 _delay_ms(1);
	 }
 }

int main(void)
{
    DDRC = 0xFF;
    PORTC = 0x00;
    
    DDRD = 0xFF;
    PORTD = 0x01;
    
    init();
	clear_LCD();
	wait(100);
    set_cursor(2);
    display_text("hallo Hallo");
    wait(2000);
    clear_LCD();
	wait(100);
    display_text("We meet again");
    
    while (1)
    {
	   
    }
}

