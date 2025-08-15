#define F_CPU 20000000UL
#include <avr/io.h>
#include <util/delay.h>

#include "SEVENSEG/SEVENSEG_LIB.h"

char contador=0; // 0 - 9

int main(void)
{
	diplayInit();
	//LOOP
    while (1) 
    {
		displayDecoCC(contador);
		_delay_ms(500);
		contador++;
	    contador = contador>9 ? 0:contador;
		
		
    }
}

