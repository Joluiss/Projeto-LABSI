#include "config.h"

//volatile unsigned char flag1ms;
// --- Funcao do LED CTC (Protótipo em config.h) ---
// alterna o estado do LED ligado ao pino PD1 (LED2)
void led_1hz(void){
    PORTD ^= (1<<PD1);
}


int main(void) {

    init(); 

    while (1) {
        
        // 1. Ler ADC (Potenciômetro)
        ADCSRA |= (1 << ADSC);             // Inicia a conversão
        while (ADCSRA & (1 << ADSC));      // Espera fim da conversão
        uint8_t adc8 = ADCH;               // Lê o valor de 8 bits (ajuste à esquerda)
        OCR1A = adc8;                      // Ajusta o Duty Cycle do LED PWM (LED1)

        // 2. Piscar LED 1 Hz (Alterna a cada 500ms)
        
        if ((uint16_t)(ms_count - last_ms) >= 500)
        {
            last_ms = ms_count;
            led_1hz();          // Alterna o estado do LED2
        }
            

/*
        void Pisca(){
            if(flag1ms==1)
            {
                flag1ms=0;
                ms_count++;
                if(ms_count==500)
                {
                    PORTD ^=(1<<PD1);
                }
                if(ms_count==1000)
                {
                    ms_count=0;
                    PORTD ^=(1<<PD1);
                }
            }

        }
            */
        


        _delay_ms(5);   
    }
}