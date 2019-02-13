/*
 * lcd.h
 *
 * Created: 13-2-2019 10:54:54
 *  Author: larsv
 */ 

void init(void);
void display_text(char *str);
void set_cursor(int position);
void clear_LCD(void);
void shift_text(int position);