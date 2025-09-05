#include "HCSR04_LIB.h"

void HCSR04_Init(){
	//CONFIGURAMOS EL TRI COMO PIN DE SALIDA
	HCSR04DDR |= (1<<HCSR04_TRI);
	
	//CONFIGURAMOS EL ECHO COMO ENTRADA
	HCSR04DDR &= ~(1<<HCSR04_ECHO);
	
	HCSR04PORT &= ~(1<<HCSR04_TRI);
}

unsigned int HCSR04_GetDistance(){
	unsigned int contador=0;
	HCSR04PORT |= (1<<HCSR04_TRI);
	_delay_us(10);
	HCSR04PORT &= ~(1<<HCSR04_TRI);
	
	//ESPERANDO A QUE SE GENERE EL SONIDO
	while( ( HCSR04PIN & (1<<HCSR04_ECHO) ) == 0 );
	
	//COMENZAMOS A MEDIR TIEMPO
	while( ( HCSR04PIN & (1<<HCSR04_ECHO) ) != 0 ){
		contador++;
		_delay_us(58);
	}
	return (contador);
	
}