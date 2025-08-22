#include "CONFIG/Config.h"
#include "LCD/LCD_LIB.h"


char customChar[] = {
	0b00100,
	0b01110,
	0b10101,
	0b00100,
	0b00100,
	0b00100,
	0b00100,
	0b00000
};

char customChar2[] = {
	0b00100,
	0b01110,
	0b11111,
	0b11111,
	0b01110,
	0b00100,
	0b11111,
	0b00000
};


int main(void)
{
    lcd_init();
	
	lcd_disable_blink();
	lcd_disable_cursor();
	
	lcd_custom_char(1,customChar);
	lcd_custom_char(2,customChar2);
	
	lcd_set_cursor(3,5);
	lcd_write(1);
	lcd_write(2);

    while (1) 
    {
		lcd_set_cursor(1,1);
		lcd_puts("Arlin la saca toda");
		
		_delay_ms(500);
    }
}

