#include <avr/io.h>
#include <avr/interrupt.h>


volatile unsigned char invert_direction = 0;
volatile unsigned int ms_counter_250 = 0;

void init(void) {

	DDRB = 0b11100000; // PB5, PB6 e PB7 para motor
	PORTB = 0b00111110; // Inicializa PORTB

	DDRC = 0xFF; // Displays conectados a PORTC
	PORTC = 0xFF; // Inicializa PORTC

	// Configura Timer0 para 5 ms (CTC mode)
	OCR0 = 77; // Valor calculado para 5 ms (prescaler de 1024)
	TCCR0 = 0b00001111; // CTC mode, prescaler 1024
	TIMSK |= (1 << OCIE0); // Habilita interrup��o do Timer0

	sei(); // Habilita interrup��es globais
}



int main(void) {
	init();

	while (1) {
		
	}
}
