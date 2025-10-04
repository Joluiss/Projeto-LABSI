#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdint.h>

//Contador de milissegundos atualizado por interrupcao
volatile uint16_t ms_count = 0;
volatile uint16_t last_ms = 0;

//rotina de interrupcao (para mudar o contador)
ISR(TIMER0_COMPA_vect){
    ms_count++;
}
//vai ser chamada a cada 1ms e incrementa assim temos contadem mais precisa

static void led_1hz(void){
    PORTD ^= (1<<PD1);
}
//alterna o estado do LED ligado ao pino PD1


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
	TIMSK0 |= (1 << OCIE0A); // Habilita interrupção do Timer0

	ADCSRA = (1 << ADEN)|(1 << ADPS2)|(1 << ADPS1)|(1 << ADPS0); //Ativar com prescaler de 128 (Fadc=125KHz)
	ADMUX = (1 << REFS1)|(1 << ADLAR); // Resultado ajuste à esquerda

	sei(); // Habilita interrupções globais
}



int main(void) {

	init();

	while (1) {
		// Ler ADC
        ADCSRA |= (1 << ADSC);
        while (ADCSRA & (1 << ADSC));  // espera fim da conversão
        uint8_t adc8 = ADCH;           // valor de 8 bits
        OCR1A = adc8;                  // ajusta brilho do LED PWM

        // Piscar LED 1 Hz
        if ((uint16_t)(ms_count - last_ms) >= 500)
        {
            last_ms = ms_count;
            led_1hz();          // alterna LED
        }

        _delay_ms(5);   
    }
}

