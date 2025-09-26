#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


char old_value, current_value;


int main(void){
	
	//CARGAMOS EL CALOR DEL PIN
	 old_value = (PINC & (1<<PINC0) ) == 1 ? 1: 0;
    
	//CONFIGURAMOS LAS ENTRADAS Y SALIDAS DIGITALES
	DDRD &= ~( (1<<PIND2)|(1<<PIND3) );
	DDRB |=  (1<<PINB0)|(1<<PINB1)|(1<<PINB2);
	
	//CONFIGRUAR LA INTERRUPCION
	// INT0 e INT1
	
	//CONFIGRUAR LA SENSIBILIDAD
	EICRA |= ( (1<<ISC00) | (1<<ISC01)  );  //FLANCOS DE SUBIDA
	EICRA |= ( (1<<ISC11) | (1<<ISC10)  );
	
	//HABILITAR LAS INTERRUCPIONES INT0 E INT1
	EIMSK |= ( (1<<INT0) | (1<<INT1) );
	
	/*CONFIGURAMOS LAS INTERRUPCIONES POR CAMBIO DE ESTADO*/
	PCICR |= (1<<PCIE1);
	
	//HABILITAMOS LAS MASCARAS DE PCINT1
	PCMSK1 |= (1<<PCINT8)|(1<<PCINT9);
	
	
	//HABILITAR LAS INTERRUPCIONES GLOBALES
	sei();
	
    while(1){
		
		
		
		_delay_ms(2000);
		
		
		
    }
}

ISR(INT0_vect){
	PORTB ^=  (1<<PINB0);
}
ISR(INT1_vect){
	PORTB ^=  (1<<PINB1);
}

ISR(PCINT1_vect){
	current_value = (PINC & (1<<PINC0) ) == 1 ? 1: 0;
	if( current_value != old_value ){
		PORTB ^=  (1<<PINB2);
		old_value = current_value;
	}
	
}


//PCINT
