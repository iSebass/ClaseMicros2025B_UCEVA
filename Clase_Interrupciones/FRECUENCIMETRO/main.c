#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "LCD/LCD_LIB.h"


unsigned int freq;


int main(void){
	
	//LCD
	lcd_init();
	lcd_disable_cursor();
	lcd_disable_blink();
	
	//CONFIGRUAR LA SENSIBILIDAD
	EICRA |= ( (1<<ISC00) | (1<<ISC01)  );  //FLANCOS DE SUBIDA
	
	//HABILITAR LAS INTERRUCPIONES INT0 E INT1
	EIMSK |= ( (1<<INT0) );
	
	//HABILITAR LAS INTERRUPCIONES GLOBALES
	sei();
	
	while(1){
		_delay_ms(100);
		lcd_set_cursor(1,1);
		lcd_printf("FREQ: %10d", freq*10);
		freq=0;
	}
}

ISR(INT0_vect){
	freq++;
}


