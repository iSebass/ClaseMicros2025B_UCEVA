#define F_CPU 20000000
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	//CONFIGURAR
	DDRB  = 0b00000001; //BIT B0 COMO SALIDA
	
    
	
    while(1){
		PORTB = 0b00000001;
		_delay_ms(500);
		
		PORTB = 0b00000000;
		_delay_ms(500);
		
    }
}

