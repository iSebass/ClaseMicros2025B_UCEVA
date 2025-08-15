#define F_CPU 20000000UL
#include <avr/io.h>
#include <util/delay.h>

#include "SEVENSEG/SEVENSEG_LIB.h"

#define DP_DECENAS  (1<<PINB0)
#define DP_UNIDADES (1<<PINB1)

char contador=35; // 00 - 99

#define te 5


int main(void)
{
	diplayInit();
	DDRB |= (1<<PINB0)|(1<<PINB1);
	//LOOP
    while (1) 
    {
		PORTB = ~DP_DECENAS;
		displayDecoCC(3);
		_delay_ms(te);
		
		PORTB = ~DP_UNIDADES;
		displayDecoCC(5);
		_delay_ms(te);
		
    }
}

