#define F_CPU 20000000
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
    //COFIGURAR LA ENTRADA DIGITAL BTN
	DDRD = 0x00;
	
	//CONFIGURAR LA SALIDA DIGITAL LED
	DDRB = (1<<5);

    while (1) 
    {
		if( PIND == (1<<0)  ){
			PORTB = (1<<5);
		}
		else{
			PORTB = 0;
		}
    }
}

