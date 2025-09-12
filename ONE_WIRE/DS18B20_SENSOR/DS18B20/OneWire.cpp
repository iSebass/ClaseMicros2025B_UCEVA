#include "OneWire.h"

OneWire::OneWire(volatile uint8_t* port, volatile uint8_t* pinRegister, uint8_t pin)
: port(port), pinRegister(pinRegister), pin(pin) {}
	


	
void OneWire::busModeOUT() {
	//CONFIGURAMOS EL BUS DE SALIDA
	*(port-1) |= (1<< pin);
}

void OneWire::busModeIN() {
	//CONFIGURAMOS EL BUS DE ENTRADA
	*(port-1) &= ~(1<< pin);
}

void OneWire::setLow() {
	busModeOUT();
	
	//GENERAMOS EL ESTADO LOGICO DESEADO
	*(port) &= ~(1<<pin);
}

void OneWire::setHigh() {
	busModeIN();
}

bool OneWire::readPin() {
	//REGRESAMOS EL VALOR ACTUAL DEL BUS
	return ( *(pinRegister) & (1 << pin) ) != 0; 
}

bool OneWire::presenceDetect() {
	//REGRESAMOS EL VALOR ACTUAL DEL BUS
	uint16_t timeOut=200;
	while(  readPin()   ){
		if( timeOut == 0){
			return false;
		}
		timeOut--;
		_delay_us(1);
	}
	//DAMOS TIEMPO DE RECUPERACION EN EL BUS
	_delay_us(480);
	return true;
}

bool OneWire::reset() {
	/*
		GENERAMOS EL PULSO DE RESET.
		
		SE GENERA UN PULSO BAJO EN EL BUS POR 480us Y SE LIBERA EL BUS
		______               ________
  		      |_____________|
				  480us
		
		POSTERIORMENTE SE LEE UN PULSO DE PRESENCIA DE PARTE DE LOS SENSORES:
			
		BUS LIBRE ______    PULSO PRESENCIA   _______
					    |____________________|
					         60us a 240uS
		
	*/
	
	//GENERAMOS PULSO DE RESET
	setLow();                  
	_delay_us(480);
	
	//LIBERAMOS EL BUS Y ESPERAMOS 70uS
	setHigh();                 
	_delay_us(60);

	//ESPERMAOS EL PULSO DE PRESENCIA
	bool presence = presenceDetect(); 
	
	//REGRESAMOS EL RESULTADO DE LA ACCION RESET
	return presence;
}

void OneWire::writeBit(bool bit) {
	/*
		ESCRITURA DE 1 LOGICO
		
			BUS LIBRE ___________            ___________________
					   	    	 |__________|                   |
					   		      1us a 15us                    |
					             | <--------------------------->|
					                             60us   
								
		ESCRITURA DE 0 LOGICO
		
			BUS LIBRE    ___________     
						    		|_____________________________   
									| <-------------------------->|
											 60us  
	*/
	
	
	//CONFIGURAMOS EL BUS COMO SALIDA
	busModeOUT();
	
	//SE LANZA UN CERO ENTRE 1us a 15uS
	setLow();
	_delay_us(10);
	
	//PREGUNTAMOS EL BUS QUE DESEA ENVIAR
	if( bit ){
		setHigh();
	}
	_delay_us(50);
	
	//SE REESTABLECE EL BUS
	busModeIN();
	
}

bool OneWire::readBit() {
	uint8_t bit = 0;
	
	//CONFIGURAMOS EL BIT COMO SALIDA
	busModeOUT();
	setLow();	
	_delay_us(1);
	
	busModeIN();
	_delay_us(14);
	
	
	if( readPin() ){
		bit=1;
	}
	_delay_us(45);
	return bit;
}

void OneWire::writeByte(uint8_t byte) {
	for (uint8_t i = 0; i < 8; i++) {
		writeBit(byte & 0x01);
		byte >>= 1;
	}
}

uint8_t OneWire::readByte() {
	uint8_t byte = 0;
	for (uint8_t i = 0; i < 8; i++) {
		byte>>=1;
		if (readBit()) {
			byte |= 0x80;
		}
	}
	return byte;
}