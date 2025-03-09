// transmission_arr.c
// Created 2025-02-14
// Authors: AD
// Final Design Project
// Timer Code

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL
#include <util/delay.h>

#define SINE_TABLE_SIZE 64
#define TOP 250

// Precomputed sine wave lookup table (scaled to 8-bit range 0-255)
const uint8_t sine_table[SINE_TABLE_SIZE] = {
	128, 140, 153, 165, 177, 189, 200, 211,
	221, 230, 239, 246, 252, 255, 258, 259,
	258, 255, 252, 246, 239, 230, 221, 211,
	200, 189, 177, 165, 153, 140, 128, 115,
	102,  90,  78,  66,  55,  44,  34,  25,
	16,   9,   3,   0,   0,   0,   3,   9,
	16,  25,  34,  44,  55,  66,  78,  90,
	102, 115
};

double duty_cycle = 50;

void setupTimer0() {
	DDRD |= 1 << PORTD5;
	TCCR0A = (1 << WGM00) | (1 << WGM01) | (1 << COM0B1);
	OCR0A = TOP;
	OCR0B = (duty_cycle/100)*TOP;
	TCCR0B = (1 << WGM02) | (1 << CS00) | (1 << CS01);
	TIMSK0 = (1 << TOIE0);
}

ISR(TIMER0_OVF_vect){
	OCR0B = (duty_cycle/100)*TOP;
}

int main() {
	setupTimer0();
	sei(); // Enable global interrupts

	while (1) {
		duty_cycle++;
		_delay_ms(10);
		if(duty_cycle > 100){
			duty_cycle = 0;
		}
	}
}
