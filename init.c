#include "config.h"


volatile uint16_t ms_count = 0;
volatile uint16_t last_ms = 0; 
//volatile unsigned char flag1ms;

// É chamada a cada 1ms e incrementa o ms_count
ISR(TIMER0_COMPA_vect){
    ms_count++;
    //flag1ms = 1;
}
void init(void) {

    // --- Configuracao I/O ---
    DDRB |= (1<<PB1);    // PB1 como saida (PWM) - LED1
    DDRD |= (1 << PD1);  // PD1 como saída (LED 1Hz) - LED2
    // PC0 é uma entrada analógica (Potenciometro)
    
    PORTB &= ~(1 << PB1); // LED PWM começa apagado
    PORTD &= ~(1 << PD1); // LED 1Hz começa apagado

    // --- Configuracao ADC (Potenciometro em PC0) ---
    // AVCC como referencia (REFS0), Resultado ajuste à esquerda (ADLAR)
    ADMUX = (1 << REFS0) | (1 << ADLAR); 
    // Ativar (ADEN), Prescaler 128 (Fadc=125KHz)
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); 

    // --- Configuracao Timer1 (PWM para LED1) ---
    // Phase Correct PWM 8-bit (WGM10), Modo Non-Inverting (COM1A1)
    TCCR1A = (1 << COM1A1) | (1 << WGM10); 
    // Prescaler 8 (CS11). Modo 1 (Phase Correct)
    TCCR1B = (1 << CS11); 
    OCR1A = 0;

    // --- Configuracao Timer0 (CTC para interrupcoes de 1ms) ---
    TCCR0A = (1 << WGM01);                  // CTC mode
    TCCR0B = (1 << CS01)|(1 << CS00);        // Prescaler 64
    OCR0A = 249;                             // 1ms=((OCR0A+1)*64)/16MHz
    TIMSK0 |= (1 << OCIE0A);                 // Habilita interrupção do Timer0

    // Habilita interrupções globais
    sei(); 
}