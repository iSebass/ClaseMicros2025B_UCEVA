#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#include "LCD/LCD_LIB.h"
#include "HCSR04_LIB/HCSR04_LIB.h"




int distancia=0;

int main(void)
{
	lcd_init();
	lcd_disable_cursor();
	lcd_disable_blink();
	
	HCSR04_Init();
	
	
    while (1){
		
		distancia = HCSR04_GetDistance();
		lcd_set_cursor(1,1);
		lcd_printf("distancia: %d", distancia);
		_delay_ms(100);
		
    }
}

