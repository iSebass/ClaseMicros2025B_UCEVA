#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#include "LCD/LCD_LIB.h"
#include "HCSR04_LIB/HCSR04_LIB.h"
#include "SERVO/SERVO_LIB.h"


int distancia=0;

#define MOTORES_DDR   DDRC
#define MOTORES_PORT  PORTC

#define IN1MA    0
#define IN2MA    1
#define IN1MB    2
#define IN2MB    3


void InitMotores(){
	MOTORES_DDR  |=    (1<<IN1MA) | (1<<IN2MA) | (1<<IN1MB) | (1<<IN2MB);
	MOTORES_PORT &= ~( (1<<IN1MA) | (1<<IN2MA) | (1<<IN1MB) | (1<<IN2MB) );
}

void GirarDerecha(){
	MOTORES_PORT |=  (1<<IN2MA);
	MOTORES_PORT &= ~(  (1<<IN1MA) | (1<<IN1MB) | (1<<IN2MB) );
}
void GirarIzquierda(){
	MOTORES_PORT |= (1<<IN1MB);
	MOTORES_PORT &= ~( (1<<IN1MA) | (1<<IN2MA)  | (1<<IN2MB) );
}
void Retroceder(){
	MOTORES_PORT |= (1<<IN2MB) | (1<<IN1MA);
	MOTORES_PORT &= ~(  (1<<IN2MA)  | (1<<IN1MB) );
}
void Parar(){
	MOTORES_PORT &= ~( (1<<IN1MA) | (1<<IN2MA) | (1<<IN1MB) | (1<<IN2MB) );
}
void Avanzar(){
	MOTORES_PORT |= (1<<IN1MB) | (1<<IN2MA);
	MOTORES_PORT &= ~( (1<<IN1MA)|  (1<<IN2MB) );
}


int main(void)
{
	lcd_init();
	lcd_disable_cursor();
	lcd_disable_blink();
	HCSR04_Init();
	
	// Usa OC1A (PB1). Si quieres PB2, usa SERVO_PIN_OC1B.
	ServoInit(SERVO_PIN_OC1A);
	InitMotores();

    while (1){
		
		distancia = HCSR04_GetDistance();
		lcd_set_cursor(1,1);
		lcd_printf("distancia: %3d ", distancia);
		
		if( distancia <= 10){
			Parar();
			_delay_ms(500);
			GirarDerecha();
			_delay_ms(1000);
			
		}
		else{
			Avanzar();
			
		}
		
		_delay_ms(100);
		
		
    }
}

