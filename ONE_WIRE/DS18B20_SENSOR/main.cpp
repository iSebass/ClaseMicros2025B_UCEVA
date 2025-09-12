#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#include "DS18B20/DS18B20.h"


// ---------- UART: 9600 bps ----------
static void uart_init(uint32_t baud = 9600) {
	uint16_t ubrr = (F_CPU / (16UL * baud)) - 1;
	UBRR0H = (uint8_t)(ubrr >> 8);
	//UBRR0F; // to avoid compiler warning if not used
	UBRR0L = (uint8_t)ubrr;
	UCSR0B = (1 << TXEN0);                 // TX enable
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);// 8N1
}



static void uart_putc(char c) {
	while (!(UCSR0A & (1 << UDRE0)));
	UDR0 = c;
}

static void uart_puts(const char* s) {
	while (*s) uart_putc(*s++);
}

static void uart_print_temp(float t) {
	int16_t ent = (int16_t)t;
	uint16_t dec = (uint16_t)((t - ent) * 100.0f);
	if (t < 0 && ent == 0) uart_putc('-'); // signo si -0.x
	char buf[16];
	snprintf(buf, sizeof(buf), "%d.%02u", ent, dec);
	uart_puts(buf);
}


int main(void)
{
	uart_init(9600);
	
    DS18B20 sensor_temp(&PORTB, &PINB, PB0);
	
    while(1){
		float t = sensor_temp.get_temp();   // 0xFFFF si falla
		if (t != 0xFFFF) {
			uart_puts("T = ");
			uart_print_temp(t);
			uart_puts(" C\r\n");
			} else {
			uart_puts("Sensor no presente o error.\r\n");
		}
		_delay_ms(1000);	
    }
}

