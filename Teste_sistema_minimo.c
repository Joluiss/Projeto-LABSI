/*
    Lê um potenciometro ligado a PC0 com o ADC do ATMega328P(8bits)
    Usa esse valor ADC para controlar o brilho de um LED ligado a PB1(OC1A) atraves de um PWM
    Gera uma onda quadrada de 1Hz(led a piscar a 1Hz) em PD1 (toggle a cada 500ms)
*/

/*
    Clock do CPU a 16MHz
*/

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h> //interrupcoes
#include <util/delay.h> //funcoes de atraso (delay)
#include <stdint.h> //tipos de dados

//Contador de milissegundos atualizado por interrupcao
volatile uint16_t ms_count = 0;

//rotina de interrupcao (para mudar o contador)
ISR(TIMER0_COMPA_vect){
    ms_count++;
}
//vai ser chamada a cada 1ms e incrementa assim temos contadem mais precisa

static void led_1hz(void){
    PORTD ^= (1<<PD1);
}
//alterna o estado do LED ligado ao pino PD1

int main(void){

    //configuração dos pinos
    DDRB |= (1<<PB1); //PB1 como saida (PWM)
    DDRD |= (1 << PD1);   // PD1 como saída (LED 1Hz)
    PORTB &= ~(1 << PB1); // LED PWM começa apagado
    PORTD &= ~(1 << PD1); // LED 1Hz começa apagado

    //configurar ADC
    ADMUX = /*(1 << REFS0) | */ (1 << ADLAR); //ajustar a esquerda para ler 8 bits
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
    //ADEN ativa o ADC, PRESCALER = 128 -> adc a 125kHz

    //configurar TIMER1(PWM)
    TCCR1A = (1 << COM1A1) | (1 << WGM10);
    TCCR1B = (1 << WGM12) | (1 << CS11);
    OCR1A = 0;
    /*
        Ativa Fast PWM em 8 bits.
        COM1A1 = 1 → modo não inversor (quanto maior o valor, mais brilho).
        Prescaler = 8.
        OCR1A guarda o valor de ciclo útil (duty cycle), inicialmente 0 (apagado).
    */

    //Configurar o TIMER0
    TCCR0A = (1 << WGM01);
    OCR0A = 249;
    TCCR0B = (1 << CS01) | (1 << CS00);
    TIMSK0 = (1 << OCIE0A);
    /*
    Timer0 em modo CTC (Clear Timer on Compare)
    Conta até 249
    Com prescaler de 64 → cada interrupção ocorre a cada 1 ms
    Ativa interrupção para executar ISR(TIMER0_COMPA_vect)
    */

    sei();//habilita interrupcoes

    while(1){

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
