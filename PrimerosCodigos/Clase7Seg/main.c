#define F_CPU 20000000UL
#include <avr/io.h>
#include <util/delay.h>

char decoCC[10]={191, 134, 219, 207, 230, 237, 253, 135, 255, 231};
char decoAC[10]={64, 121, 36, 48, 25, 18, 2, 120, 0, 24};
	
char contador=0; // 0 - 9

int main(void)
{
	//CONFIGURAMOS TODO EL PUERTO COMO SALIDA
    DDRD = 0xFF;

	//LOOP
    while (1) 
    {
		PORTD = decoCC[contador];
		_delay_ms(500);
		contador++;
	    contador = contador>9 ? 0:contador;
    }
}

