#ifndef SERVO_H
#define SERVO_H

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#include <stdint.h>
#include <avr/io.h>

#ifndef F_CPU
#warning "F_CPU no está definido. Defínelo (p.ej. 16000000UL) en Project -> Toolchain -> Symbols."
#endif

// Selección de pin de salida (los pines de servo disponibles en Timer1)
typedef enum {
	SERVO_PIN_OC1A = 0,   // PB1
	SERVO_PIN_OC1B = 1    // PB2
} servo_pin_t;

// Config por defecto (puedes cambiarlas antes de compilar)
#ifndef SERVO_PRESCALER
#define SERVO_PRESCALER 8u     // /8 da buena resolución: 0.5 us por tick @16MHz
#endif

#ifndef SERVO_MIN_US
#define SERVO_MIN_US     1000u // 1.000 us  -> ~0°
#endif

#ifndef SERVO_MAX_US
#define SERVO_MAX_US     2000u // 2.000 us  -> ~180°
#endif

#ifndef SERVO_NEUTRAL_US
#define SERVO_NEUTRAL_US 1500u // 1.500 us  -> ~90°
#endif

// API
void ServoInit(servo_pin_t pin);
void ServoWrite(uint8_t angle_deg);              // 0..180°
void ServoWriteMicroseconds(uint16_t pulse_us);  // 1000..2000 (o tu rango)
void ServoDisable(void);                         // Opcional: apaga la salida (flota el pin)

#endif /* SERVO_H */
