#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#include "LCD/LCD_LIB.h"
#include "HCSR04_LIB/HCSR04_LIB.h"
#include "SERVO/SERVO_LIB.h"

int distancia=0;

int main(void)
{
	lcd_init();
	lcd_disable_cursor();
	lcd_disable_blink();
	HCSR04_Init();
	
	// Usa OC1A (PB1). Si quieres PB2, usa SERVO_PIN_OC1B.
	ServoInit(SERVO_PIN_OC1A);

    while (1){
		
		distancia = HCSR04_GetDistance();
		lcd_set_cursor(1,1);
		lcd_printf("distancia: %3d", distancia);
		_delay_ms(100);
		
		ServoWrite(0);
		distancia = HCSR04_GetDistance();
		_delay_ms(1000);
		ServoWrite(90);
		distancia = HCSR04_GetDistance();
		_delay_ms(1000);
		ServoWrite(180);
		distancia = HCSR04_GetDistance();
		_delay_ms(1000);
		
    }
}

