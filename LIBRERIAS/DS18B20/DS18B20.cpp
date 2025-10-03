#include "DS18B20.h"

// Constructor que llama al constructor base de OneWire;
DS18B20::DS18B20(volatile uint8_t* port, volatile uint8_t* pinRegister, uint8_t pin)
: OneWire(port, pinRegister, pin) {}

// Verifica si el sensor está conectado;
bool DS18B20::isSensorPresent() {
	return reset(); // Si el sensor responde al reset, está presente;
}

float DS18B20::get_temp(){
	uint8_t temp_lsb, temp_msb;
	uint16_t temp;
		
	if( isSensorPresent() ){
		writeByte(0xCC); //SKIP ROOM
		writeByte(0x44); //START CONVER
		_delay_ms(750);
	}
		
	if( isSensorPresent() ){
		writeByte(0xCC);
		writeByte(0xBE);  //LEER LA MEMORIA
		
		temp_lsb = readByte();
		temp_msb = readByte();
		temp = (temp_msb << 8) | temp_lsb;
		return temp*0.0625;
	
	}
	return 0xFFFF;
}

void DS18B20::read_rom(char *mem){
	if( isSensorPresent() ){
		writeByte(READ_ROM);
		for(uint8_t i=0; i<=7; i++){
			mem[i]=readByte();
		}
		isSensorPresent();
		_delay_ms(500);	
	}	
}

float DS18B20::get_temp_idx(char *mem){
	uint8_t temp_lsb, temp_msb;
	uint16_t temp;
	
	if( isSensorPresent() ){
		writeByte(MATCH_ROM);
		
		for(uint8_t i=0; i<=7; i++){
			writeByte(mem[i]);
		}
		
		writeByte(CONVER_T);
		_delay_ms(750);
		
		isSensorPresent();
		writeByte(MATCH_ROM);
		
		for(uint8_t i=0; i<=7; i++){
			writeByte(mem[i]);
		}
		
		writeByte(READ_SCRATCHPAD);
		
		temp_lsb = readByte();
		temp_msb = readByte();
		
		temp = (temp_msb << 8) | temp_lsb;
		
		return temp*0.0625;
	}
	return 0xFFFF;
}