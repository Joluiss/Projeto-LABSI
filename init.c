#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <util/delay.h>

volatile uint16_t ms_count = 0;
volatile uint16_t last_ms = 0;


ISR(TIMER0_COMPA_vect){
	ms_count++;
}

void init(void) {

	DDRB |= (1<<PB1) ; // Saída LED (PWM)
	PORTB &= ~(1<<PB1) ; // LED PWM desligado

	DDRC |= (1<<PC0) ; // Saída Pontenciómetro
	PORTC &= ~(1<<PC0); //

	DDRD |= (1<<PD1); // Saída LED (CTC)
	PORTD &= ~(1<<PD1); // LED CTC desligado

	TCCR1A = (1 << WGM10)|(1<<COM1A1); //PWM mode, phase correct, prescaler 8-bit, non-iverting mode
	OCR1A = 0;

	
	TCCR0A = (1 << WGM01); // CTC mode
	TCCR0B = (1 << CS01)|(1 << CS00); //Prescaler 64
	OCR0A = 249; // 1ms=((OCR0A+1)*64)/16MHz,
	TIMSK |= (1 << OCIE0A); // Habilita interrupção do Timer0

	ADCSRA = (1 << ADEN)|(1 << ADPS2)|(1 << ADPS1)|(1 << ADPS0); //Ativar com prescaler de 128 (Fadc=125KHz)
	ADMUX = (1 << REFS1)|(1 << ADLAR); // Resultado ajuste à esquerda

	sei(); // Habilita interrupções globais
}



int main(void) {
	init();

	while (1) {
		
	}
}
