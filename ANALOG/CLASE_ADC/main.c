#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#include "ADC/ADC_LIB.h"
#include "LCD/LCD_LIB.h"

int conver;
float temp;

int main(void)
{
	lcd_init();
	lcd_disable_cursor();
	lcd_disable_blink();
	
    ADC_init();
	
	while (1) 
    {
		conver = ADC_read(A0);
		temp = 100.0/1023.0*conver;
		
		lcd_set_cursor(1,1);
		lcd_printf("Temp: %5.1f", temp);
		_delay_ms(100);
		
    }
}

