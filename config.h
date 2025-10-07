#ifndef CONFIG_H
#define CONFIG_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <util/delay.h>

#define F_CPU 16000000UL

extern volatile uint16_t ms_count;
extern volatile uint16_t last_ms; 

void init(void);
void led_1hz(void);
#endif