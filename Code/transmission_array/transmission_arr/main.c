#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL
#include <util/delay.h>

#define SINE_TABLE_SIZE 64

#define TOP_high 200  // Frequency for transmitting '1' @ 57Hz, 5.00V-pp
#define TOP_low 35 // Frequency for transmitting '0' @ 107Hz, 2.04V-pp
#define TOP_default 5 // Default Frequency @ 600Hz, 400mV-pp

// Precomputed sine wave lookup table (scaled to 8-bit, duty percentage)

const uint8_t sine_table[SINE_TABLE_SIZE] = {
	50, 54, 59, 64, 69, 73, 77, 81,
	85, 88, 91, 94, 96, 97, 99, 99,
	100, 99, 99, 97, 96, 94, 91, 88,
	85, 81, 77, 73, 69, 64, 59, 54,
	50, 45, 40, 35, 30, 26, 22, 18,
	14, 11, 8, 5, 3, 2, 0, 0,
	0, 0, 0, 2, 3, 5, 8, 11,
	14, 18, 22, 26, 30, 35, 40, 45
};

volatile uint8_t sine_index = 0;
volatile uint8_t bit_index = 0;
volatile uint8_t current_bit = 0;
volatile uint8_t transmission_active = 0;
volatile uint8_t message[16] = {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0}; // bit sequence

void setupTimer0() {
	DDRD |= (1 << PORTD5); // PD5 sine output

	TCCR0A = (1 << WGM00) | (1 << WGM01) | (1 << COM0B1); // Fast PWM
	TCCR0B = (1 << WGM02) | (1 << CS00) | (1 << CS01);   // Prescaler 64
	OCR0A = TOP_default; // 
	OCR0B = sine_table[sine_index]; 
	TIMSK0 = (1 << TOIE0); 
}

void setupTimer1() {
	// bit transmission timing 
	TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10); 
	OCR1A = 5000; // transmission interval
	TIMSK1 = (1 << OCIE1A); 
}

ISR(TIMER0_OVF_vect) {
	sine_index = (sine_index + 1) % SINE_TABLE_SIZE;
	OCR0B = (sine_table[sine_index] * OCR0A) / 100; 
}

ISR(TIMER1_COMPA_vect) {
	if (transmission_active) {
		if (bit_index < 16) {
			current_bit = message[bit_index];
			OCR0A = current_bit ? TOP_high : TOP_low;
			bit_index++;
			} else {
			transmission_active = 0; // done transmission, reset to default transmission frequency
			OCR0A = TOP_default;
		}
	}
}

void startTransmission() {
	bit_index = 0;
	transmission_active = 1;
}

int main() {
	setupTimer0();
	setupTimer1();
	sei(); 
	
	_delay_ms(500);
	startTransmission();

	while (1) {
		// :( photoresistor code will go here 
	}
}
