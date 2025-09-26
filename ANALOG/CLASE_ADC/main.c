#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#include "ADC/ADC_LIB.h"
#include "LCD/LCD_LIB.h"

int conver;
float temp, sp;

int main(void)
{
	lcd_init();
	lcd_disable_cursor();
	lcd_disable_blink();
	
    ADC_init();
	
	while (1) 
    {
		conver = ADC_read(A0);
		temp   = ADC_Map( conver, 0.0, 307, 0.0, 150.0  );
		
		conver = ADC_read(A1);
		sp     = ADC_Map( conver, 0.0, 1023.0, 20.0, 80.0 );
		
		lcd_set_cursor(1,1);
		lcd_printf("Temp: %5.1f", temp);
		
		lcd_set_cursor(2,1);
		lcd_printf("set_point: %5.1f", sp);
		_delay_ms(100);
		
    }
}

