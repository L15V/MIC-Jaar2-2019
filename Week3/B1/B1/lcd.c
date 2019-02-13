/*
 * lcd.c
 *
 * Created: 13-2-2019 10:54:38
 *  Author: larsv
 */
 
 #define F_CPU 8000000

 #include <avr/io.h>
 #include <util/delay.h> 

 #define LCD_E 	3
 #define LCD_RS	2

  void toggle_e(void)
  {
	  PORTC |= (1<<LCD_E);
	  _delay_ms(1);
	  PORTC &= ~(1<<LCD_E);
	  _delay_ms(1);
  }

   void lcd_write_data(unsigned char byte)
   {
	   // First nibble.
	   PORTC = byte;
	   PORTC |= (1<<LCD_RS);
	   toggle_e();

	   // Second nibble
	   PORTC = (byte<<4);
	   PORTC |= (1<<LCD_RS);
	   toggle_e();
   }

    void lcd_command(unsigned char byte)
    {
	    PORTC = byte;
	    PORTC &= ~(1<<LCD_RS);
	    toggle_e();

	    // Second nibble
	    PORTC = (byte<<4);
	    PORTC &= ~(1<<LCD_RS);
	    toggle_e();
    }

 void init(void)
 {
	DDRC = 0xFF;
	PORTC = 0x00;

	// Step 2 (table 12)
	PORTC = 0x20;	// function set
	toggle_e();

	// Step 3 (table 12)
	PORTC = 0x20;   // function set
	toggle_e();
	PORTC = 0x80;
	toggle_e();

	// Step 4 (table 12)
	PORTC = 0x00;   // Display on/off control
	toggle_e();
	PORTC = 0xF0;
	toggle_e();

	// Step 4 (table 12)
	PORTC = 0x00;   // Entry mode set
	toggle_e();
	PORTC = 0x60;
	toggle_e();

 }

 void display_text(char *str)
 {
	for(;*str; str++){
		lcd_write_data(*str);
	}
 }

 void set_cursor(int position)
 {
	lcd_command(0x02);
	for(int i = 0; i < position; i++) {
		lcd_command(0x14);
	}
	PORTC = 0x00;
 }

 void clear_LCD() {
	 lcd_command(0x01);
	 lcd_command(0x02);

 }

 void shift_text(int position) {
	 for(int i = 0; i < position; i++) {
		 lcd_command(0x18);
	 }
 }