#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdint.h>

volatile unsigned char;
volatile unsigned int;

typedef struct USARTRX
{
	char receiver_buffer;
	unsigned char status;
	unsigned char receive: 1;
	unsigned char error: 1;
	
}USARTRX_st;

void init(void) {

	DDRB = 0b00000101; // Entrada PB1, PB3, PB4, PB5, PB6, PB7
	PORTB = ; // Inicializa PORTB

	DDRC = ; // Displays conectados a PORTC
	PORTC = ; // Inicializa PORTC

	
	TCCR0A |= (1 << WGM00); // PWM mode, phase correct
	TIMSK |= (1 << OCIE0); // Habilita interrupção do Timer0

	OCR1 = 0;
	TCCR1B |= (1 << WGM12)|(1 << CS12); //CTC mode, prescaler 256

	sei(); // Habilita interrupções globais
}



int main(void) {
	init();

	while (1) {
		
	}
}

