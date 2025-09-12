#ifndef DS18B20_H
#define DS18B20_H


// COMANDOS FUNCTION
#define CONVER_T             0x44
#define WRITE_SCRATCHPAD     0x4E
#define READ_SCRATCHPAD      0xBE
#define COPY_SCRATCHPAD      0x48
#define RECALL_EEPROM        0xB8
#define READ_PWR_SUPPLY      0xB4


//DEFINIR EL PUERTO Y EL PIN DEL SENSOR
#define DS18B20_PORT  PORTB
#define DS18B20_DDR   DDRB
#define DS18B20_PIN   PINB
#define DS18B20_DQ    PINB0

#include "OneWire.h"

class DS18B20 : public OneWire {
	
	private:
		//METODO GENERALES
		bool isSensorPresent();       // VERIFICA SI HAY SENSOR
	
	public:
		// CONSTRUCTOR QUE HERA DE ONE WIRE
		DS18B20(volatile uint8_t* port, volatile uint8_t* pinRegister, uint8_t pin);
		
		//METODOS DE ADQUISICION UNIPUNTO
		float get_temp();
		
		//METODOS MULTIPUNTO
		void  read_rom(char *mem);
		float get_temp_idx(char *mem);
	
};

#endif