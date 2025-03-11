/*
 * GccApplication4.c
 *
 * Created: 2025-03-10 9:45:29 AM
 * Author : Admin
 */ 
/*
#include <avr/io.h>
*/

/*int main(void)
{
    // Replace with your application code
    while (1) 
    {
    }
}*/

/*
//define the sensor pin
#define HALL_SENSOR_PIN A6

//define the reference voltage (5v)
#define VREF 5.0

//define the ADC resolution for a 10-bit ADC (0-1023)
#define ADC_RESOLUTION 1024.0

//Art Piece ID Database
int Ref_APID[10] = {3692, 6349, 5588, 9864, 3351, 3020, 5379, 9941, 1343, 4712};

//global variables
int PedestaID = 1;
int Assigned_APID = 3351;
int state;

void setup(){
	Serial.begin(9600); //start serial communication
	while (!Serial);    //wait for serial connection
}

void loop(){
	
}

void Binary_To_APID(){//16bit binary input to 4 digit APID decimal number
	int Recieved_APID = 0;//initiate / reset art piece id
	int bit[3];//binary input array
	int idNum[3];//single digit converted decimal array

	for(int i=0; i<=3; i++){//loop to convert 4 bit binary to id#
		for(int n = 0 ; n<=3; n++){//loop to read input 4 bits at a time
			int sensorValue = analogRead(HALL_SENSOR_PIN); // Read raw analog value (0-1023)

			if (sensorValue > 0){//active high(0) or low(1)
				bit[n] = 1;//if active bit# = 1
			}
			else {
				bit[n] = 0;//else bit# = 0

				delay(1000)//magnetic feild read/sec
			}

			idNum[i] = (bit[3] * 2^3) + (bit[2] * 2^2) + (bit[1] * 2^1) + (bit[0] * 2^1);//4bit binary converted to single digit decimal 0-9
		}

		Recieved_APID = (idNum[0] * 1000) + (idNum[1] * 100) + (idNum[2] * 10) + idNum[3];//4 single digit decimals to 1 four digit decimal
	}

	void Secuity_Log(){
		Serial.print("Pedestal ID#: ");
		Serial.print(PedestaID);
		Serial.print(" | Assigned Art Piece ID#: ");
		Serial.print(Assigned_APID);
		serial.print(" | Received Art Piece ID#: ");
		Serial.print(Recieved_APID);
		serial.print(" | Security State")
		Serial.println(state);
		
	}

	void Database_Reference(int Recieved_APID, int Ref_APID[10]){
		int case;

		for(int k = 0; k<=9; k++){
			
		}
		

	}
*/

/*
#include <Arduino.h>

// Define the sensor pin
#define HALL_SENSOR_PIN A6

// Define the reference voltage (5V)
#define VREF 5.0

// Define the ADC resolution for a 10-bit ADC (0-1023)
#define ADC_RESOLUTION 1024.0

// Art Piece ID Database
int Ref_APID[10] = {3692, 6349, 5588, 9864, 3351, 3020, 5379, 9941, 1343, 4712};

// Global variables
int PedestalID = 1;
int Assigned_APID = 3351;
int state;

void setup() {
	Serial.begin(9600); // Start serial communication
	while (!Serial);    // Wait for serial connection (useful for debugging)
}

void loop() {
	Binary_To_APID();
}

// Function to convert 16-bit binary input to 4-digit APID decimal number
void Binary_To_APID() {
	int Recieved_APID = 0; // Initialize/reset art piece ID
	int bit[4]; // Binary input array
	int idNum[4]; // Single-digit converted decimal array

	for (int i = 0; i < 4; i++) { // Loop to convert 4-bit binary to ID#
		for (int n = 0; n < 4; n++) { // Read 4 bits one at a time
			int sensorValue = analogRead(HALL_SENSOR_PIN); // Read raw analog value (0-1023)
			
			if (sensorValue > 512) { // Assuming a threshold for detection
				bit[n] = 1;
				} else {
				bit[n] = 0;
			}

			delay(1000); // Magnetic field read per second
		}

		// Convert 4-bit binary to decimal (0-9)
		idNum[i] = (bit[3] * (1 << 3)) + (bit[2] * (1 << 2)) + (bit[1] * (1 << 1)) + (bit[0] * (1 << 0));
	}

	// Combine the four single-digit decimals into a four-digit number
	Recieved_APID = (idNum[0] * 1000) + (idNum[1] * 100) + (idNum[2] * 10) + idNum[3];

	// Call Security Log function
	Security_Log(Recieved_APID);
}

// Function to log security information
void Security_Log(int Recieved_APID) {
	Serial.print("Pedestal ID#: ");
	Serial.print(PedestalID);
	Serial.print(" | Assigned Art Piece ID#: ");
	Serial.print(Assigned_APID);
	Serial.print(" | Received Art Piece ID#: ");
	Serial.print(Recieved_APID);
	Serial.print(" | Security State: ");
	Serial.println(state);
} */
/*
#include <avr/io.h>
#include <util/delay.h>

// Define notes (equivalent to "pitches.h")
#define NOTE_C4  262
#define NOTE_G3  196
#define NOTE_A3  220
#define NOTE_B3  247

// Melody notes
int melody[] = {NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4};

// Note durations (4 = quarter note, 8 = eighth note, etc.)
int noteDurations[] = {4, 8, 8, 4, 4, 4, 4, 4};

// Function prototypes
void setup_timer1(uint16_t frequency);
void stop_timer1();

int main(void) {
	// Set PD3 (Pin 3) as output
	DDRD |= (1 << PD3);

	// Iterate over the notes of the melody
	for (int thisNote = 0; thisNote < 8; thisNote++) {
		int note = melody[thisNote];

		// Calculate note duration
		int noteDuration = 1000 / noteDurations[thisNote];

		// Play the tone (if note is not 0)
		if (note > 0) {
			setup_timer1(note);
		}

		// Pause between notes (note duration + 30% pause)
		_delay_ms(noteDuration * 1.30);

		// Stop playing the note
		stop_timer1();
	}

	while (1);  // Loop forever
}

// Setup Timer 1 for tone generation
void setup_timer1(uint16_t frequency) {
	if (frequency == 0) return;

	uint16_t ocr = (F_CPU / (2 * 8 * frequency)) - 1;  // Calculate OCR1A

	TCCR1A = (1 << COM1A0);   // Toggle OC1A (PD3) on Compare Match
	TCCR1B = (1 << WGM12) | (1 << CS11);  // CTC Mode, Prescaler = 8
	OCR1A = ocr;  // Set output compare register
}

// Stop Timer 1
void stop_timer1() {
	TCCR1A = 0;  // Disable output compare mode
	TCCR1B = 0;  // Stop the timer
}
*/

#include <avr/io.h>
#include <util/delay.h>

// Define the sensor pin (Analog pin A6 -> ADC6)
#define HALL_SENSOR_PIN 6

// Define the reference voltage (5V)
#define VREF 5.0

// Define the ADC resolution for a 10-bit ADC (0-1023)
#define ADC_RESOLUTION 1024.0

// Art Piece ID Database
int Ref_APID[10] = {3692, 6349, 5588, 9864, 3351, 3020, 5379, 9941, 1343, 4712};

// Global variables
int PedestalID = 1;
int Assigned_APID = 3351;
int state;

// Function prototypes
void USART_Init(unsigned int baud);
void USART_Transmit(char data);
void USART_Print(const char *str);
void USART_PrintInt(int num);
uint16_t ADC_Read(uint8_t channel);
void Binary_To_APID();
void Security_Log(int Recieved_APID);

int main(void) {
	USART_Init(9600);  // Initialize serial communication
	_delay_ms(100);    // Small delay to stabilize UART
	
	while (1) {
		Binary_To_APID();
		_delay_ms(1000);  // Read every second
	}
}

// Initialize USART (UART) for serial communicationa
void USART_Init(unsigned int baud) {
	unsigned int ubrr = F_CPU / 16 / baud - 1;
	UBRR0H = (unsigned char)(ubrr >> 8);
	UBRR0L = (unsigned char)ubrr;
	
	UCSR0B = (1 << TXEN0);  // Enable transmitter
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);  // 8-bit data
}

// Transmit a single character via UART
void USART_Transmit(char data) { 
	while (!(UCSR0A & (1 << UDRE0)));  // Wait for empty transmit buffer
	UDR0 = data;
}

// Transmit a string via UART
void USART_Print(const char *str) {
	while (*str) {
		USART_Transmit(*str++);
	}
}

// Transmit an integer via UART
void USART_PrintInt(int num) {
	char buffer[10];
	itoa(num, buffer, 10);  // Convert integer to string
	USART_Print(buffer);
}

// Read an analog value using ADC
uint16_t ADC_Read(uint8_t channel) {
	ADMUX = (1 << REFS0) | (channel & 0x07);  // AVcc reference, select channel
	ADCSRA = (1 << ADEN) | (1 << ADSC) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);  // Start conversion, prescaler 128

	while (ADCSRA & (1 << ADSC));  // Wait for conversion to finish
	return ADC;
}

// Convert binary to APID
void Binary_To_APID() {
	int Recieved_APID = 0;
	int bit[4];
	int idNum[4];

	for (int i = 0; i < 4; i++) {
		for (int n = 0; n < 4; n++) {
			uint16_t sensorValue = ADC_Read(HALL_SENSOR_PIN);

			if (sensorValue > 512) {  // Threshold for detection
				bit[n] = 1;
				} else {
				bit[n] = 0;
			}

			_delay_ms(1000);  // Magnetic field read per second
		}

		idNum[i] = (bit[3] * (1 << 3)) + (bit[2] * (1 << 2)) + (bit[1] * (1 << 1)) + (bit[0] * (1 << 0));
	}

	Recieved_APID = (idNum[0] * 1000) + (idNum[1] * 100) + (idNum[2] * 10) + idNum[3];

	Security_Log(Recieved_APID);
}

// Log security information
void Security_Log(int Recieved_APID) {
	USART_Print("Pedestal ID#: ");
	USART_PrintInt(PedestalID);
	USART_Print(" | Assigned Art Piece ID#: ");
	USART_PrintInt(Assigned_APID);
	USART_Print(" | Received Art Piece ID#: ");
	USART_PrintInt(Recieved_APID);
	USART_Print(" | Security State: ");
	USART_PrintInt(state);
	USART_Print("\r\n");
}