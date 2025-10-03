	/*
 * ONE_WIRE.h
 *
 * Created: 03/01/2025 02:18:41 p. m.
 *  Author: USER
 */ 


#ifndef ONE_WIRE_H
#define ONE_WIRE_H

//COMANDOS DE ROM
#define SEARCH_ROM           0xF0
#define READ_ROM             0x33
#define MATCH_ROM            0x55
#define SKIP_ROM             0xCC
#define ALARM_SEARCH_ROM     0xEC


#define F_CPU 16000000UL
#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>

class OneWire {
	protected:
		volatile uint8_t* port;			// REGISTRO DEL PUERTO (EJ: &PORTB)
		volatile uint8_t* pinRegister;  // REGISTRO DE CONFIGRUACION (EJ: &DDRB)
		uint8_t pin;					// PIN DONDE VA QUEDAR CONECTADO EL BUS ONE WIRE

		void setLow();					// CONFIGURA EL PIN COMO SALIDA Y LO PONE EN BAJO
		void setHigh();					// CONFIGURA EL PIN DE ENTRADA Y LO PONE EN ALTO (ESTADO NATURAL DE BUS)
		bool readPin();					// LEE EL ESTADO DEL BUS
		bool presenceDetect();			// DETECTAMOS PULSO DE PRESENCIA 
		void busModeOUT();
		void busModeIN();

	public:
		OneWire(volatile uint8_t* port, volatile uint8_t* pinRegister, uint8_t pin);

		bool reset();					// ENVIA LA SENAL DE RESET DEL BUS
		void writeBit(bool bit);		// ESCRIBE LA LOGICA DE 1 LOGICO EN EL BUS
		bool readBit();					// LECTURA DEL ESTADO LOGICO A GUARDAR
		void writeByte(uint8_t byte);   // ESCRIBE UN BYTE EN EL BUS
		uint8_t readByte();				// LEE UN BYTE EN EL BUS
};


#endif /* ONE_WIRE_H_ */