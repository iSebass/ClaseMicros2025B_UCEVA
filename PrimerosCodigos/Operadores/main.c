#define F_CPU 20000000
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	//CONFIGURANDO EL PUERTO D COMO SALIDA
    DDRD = 0xFF;
	DDRB = 0xF0;
	
		
	
    while(1){
		char status_btn01 = PINB & (1<<0);
		char status_btn02 = PINB & (1<<1);
		char status_btn03 = PINB & (1<<2);
		char status_btn04 = PINB & (1<<3);
		
		if( ( PINB & (1<<0) ) != 0){
			PORTD |=(1<<0);
		}
		else{
			PORTD &= ~(1<<0);
		}
		
		
		
    }
}

