
#include "SERVO_LIB.h"

// Cálculos de temporización
// Cuentas por microsegundo = F_CPU / (prescaler * 1e6)
// Ej: 16MHz y /8 -> 2 cuentas/us
#define COUNTS_PER_US ( (uint32_t)(F_CPU) / ( (uint32_t)SERVO_PRESCALER * 1000000UL ) )

// Periodo 20 ms (50 Hz)
#define SERVO_PERIOD_US 20000UL
#define SERVO_TOP       ( (uint16_t)(SERVO_PERIOD_US * COUNTS_PER_US) )

static servo_pin_t g_servo_pin = SERVO_PIN_OC1A;

// Convierte microsegundos a cuentas de Timer1
static inline uint16_t us_to_counts(uint16_t us) {
	uint32_t c = (uint32_t)us * COUNTS_PER_US;
	if (c > 0xFFFF) c = 0xFFFF;
	return (uint16_t)c;
}

// Constrain helper
static inline uint16_t clamp_u16(uint16_t v, uint16_t lo, uint16_t hi) {
	return (v < lo) ? lo : (v > hi) ? hi : v;
}

void ServoInit(servo_pin_t pin)
{
	g_servo_pin = pin;

	// Configura PB1 (OC1A) y/o PB2 (OC1B) como salida según el pin elegido
	if (g_servo_pin == SERVO_PIN_OC1A) {
		DDRB |= _BV(DDB1); // PB1 salida
		// Clear/Set en OC1A (no inversor)
		TCCR1A = (TCCR1A & ~(_BV(COM1A1) | _BV(COM1A0))) | _BV(COM1A1);
		// Deshabilita OC1B por si venía prendido
		TCCR1A &= ~(_BV(COM1B1) | _BV(COM1B0));
		} else {
		DDRB |= _BV(DDB2); // PB2 salida
		// Clear/Set en OC1B (no inversor)
		TCCR1A = (TCCR1A & ~(_BV(COM1B1) | _BV(COM1B0))) | _BV(COM1B1);
		// Deshabilita OC1A por si venía prendido
		TCCR1A &= ~(_BV(COM1A1) | _BV(COM1A0));
	}

	// Modo Fast PWM, TOP = ICR1 -> WGM13:0 = 14 (1110b)
	// TCCR1A: WGM11=1, WGM10=0
	TCCR1A = (TCCR1A & ~(_BV(WGM10))) | _BV(WGM11);
	// TCCR1B: WGM13=1, WGM12=1
	TCCR1B = (TCCR1B & ~0) | _BV(WGM13) | _BV(WGM12);

	// TOP para 20 ms
	ICR1 = SERVO_TOP;

	// Prescaler
	// CS12 CS11 CS10: selecciona según SERVO_PRESCALER
	// 1 -> /1, 8 -> /8, 64 -> /64, 256 -> /256, 1024 -> /1024
	#if   (SERVO_PRESCALER == 1)
	TCCR1B = (TCCR1B & ~(_BV(CS12)|_BV(CS11)|_BV(CS10))) | _BV(CS10);
	#elif (SERVO_PRESCALER == 8)
	TCCR1B = (TCCR1B & ~(_BV(CS12)|_BV(CS11)|_BV(CS10))) | _BV(CS11);
	#elif (SERVO_PRESCALER == 64)
	TCCR1B = (TCCR1B & ~(_BV(CS12)|_BV(CS11)|_BV(CS10))) | _BV(CS11) | _BV(CS10);
	#elif (SERVO_PRESCALER == 256)
	TCCR1B = (TCCR1B & ~(_BV(CS12)|_BV(CS11)|_BV(CS10))) | _BV(CS12);
	#elif (SERVO_PRESCALER == 1024)
	TCCR1B = (TCCR1B & ~(_BV(CS12)|_BV(CS11)|_BV(CS10))) | _BV(CS12) | _BV(CS10);
	#else
	# error "SERVO_PRESCALER inválido. Usa 1, 8, 64, 256 o 1024."
	#endif

	// Pulso neutro al iniciar (~90°)
	ServoWriteMicroseconds(SERVO_NEUTRAL_US);
}

void ServoWrite(uint8_t angle_deg)
{
	if (angle_deg > 180) angle_deg = 180;

	// Map 0..180 -> SERVO_MIN_US..SERVO_MAX_US
	// pulse = min + (angle * (max-min))/180
	uint32_t span = (uint32_t)SERVO_MAX_US - (uint32_t)SERVO_MIN_US;
	uint16_t pulse_us = (uint16_t)( (uint32_t)SERVO_MIN_US + ((uint32_t)angle_deg * span) / 180UL );
	ServoWriteMicroseconds(pulse_us);
}

void ServoWriteMicroseconds(uint16_t pulse_us)
{
	// Garantiza que el pulso caiga dentro del periodo y el rango
	pulse_us = clamp_u16(pulse_us, 500, (uint16_t)(SERVO_PERIOD_US - 500)); // márgenes de seguridad
	uint16_t counts = us_to_counts(pulse_us);

	if (g_servo_pin == SERVO_PIN_OC1A) {
		OCR1A = counts;
		} else {
		OCR1B = counts;
	}
}

void ServoDisable(void)
{
	// Apaga comparadores para soltar el pin
	if (g_servo_pin == SERVO_PIN_OC1A) {
		TCCR1A &= ~(_BV(COM1A1) | _BV(COM1A0));
		DDRB &= ~_BV(DDB1); // pin como entrada
		} else {
		TCCR1A &= ~(_BV(COM1B1) | _BV(COM1B0));
		DDRB &= ~_BV(DDB2); // pin como entrada
	}
}
