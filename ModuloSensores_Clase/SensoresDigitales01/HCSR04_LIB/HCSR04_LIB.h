/*
 * HCSR04_LIB.h
 *
 * Created: 05/09/2025 08:33:23 a. m.
 *  Author: USER
 */ 


#ifndef HCSR04_LIB_H_
#define HCSR04_LIB_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define HCSR04DDR   DDRD
#define HCSR04PIN   PIND
#define HCSR04PORT  PORTD
#define HCSR04_TRI  2
#define HCSR04_ECHO 3

void HCSR04_Init();
unsigned int HCSR04_GetDistance();


#endif /* HCSR04_LIB_H_ */