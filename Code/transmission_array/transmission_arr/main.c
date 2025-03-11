#include <avr/io.h>
#include <avr/interrupt.h>

#define SINE_TABLE_SIZE 64
#define TOP_200 50  // Max 8-bit timer value for smooth PWM
#define TOP_100

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

void setupTimer0() {
	DDRD |= (1 << PORTD5); // PD5 sine output

	TCCR0A = (1 << WGM00) | (1 << WGM01) | (1 << COM0B1); // fast PWM
	TCCR0B = (1 << WGM02) | (1 << CS00) | (1 << CS01);   // prescaler 64
	OCR0A = TOP_200; // setting pwm period
	OCR0B = sine_table[sine_index]; // setting initial duty cycle
	TIMSK0 = (1 << TOIE0); // enabling timer0 interrupt
}


ISR(TIMER0_OVF_vect) {
	sine_index = (sine_index + 1) % SINE_TABLE_SIZE; // Loop sine wave index
	OCR0B = (sine_table[sine_index] * TOP_200) / 100; // Scale duty cycle correctly
}

int main() {
	setupTimer0();
	sei(); // turning on global interupts

	while (1) {
		
	}
}
