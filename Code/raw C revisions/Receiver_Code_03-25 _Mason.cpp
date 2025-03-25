#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// Global Definitions
#define VRef 12.0 // Voltage Reference for Hall sensor
#define ADC_Resolution 1024.0

// Global Variables
const int ODSensitivity = 250;
int APID_Array[5] = {1238, 8953, 6666, 1794, 2486};
int Assigned_APID = 6666;
int Recieved_APID = 0;
int state[2] = {0, 0};
int bit[4] = {0, 0, 0, 0};
int idNum[4] = {0, 0, 0, 0};

// Function Prototypes
void initADC();
uint16_t readADC(uint8_t channel);
void Recieve();
void GreenState();
void BlueState();
void OrangeState();
void RedState();
void Error();

void initADC() {
	ADMUX = (1 << REFS0); // AVCC with external capacitor
	ADCSRA = (1 << ADEN) | (1 << ADSC) | (1 << ADPS2) | (1 << ADPS1); // Enable ADC, start conversion, prescaler 64
}

uint16_t readADC(uint8_t channel) {
	ADMUX = (ADMUX & 0xF8) | (channel & 0x07); // Select ADC channel
	ADCSRA |= (1 << ADSC); // Start conversion
	while (ADCSRA & (1 << ADSC)); // Wait for conversion to complete
	return ADC;
}

ISR(INT0_vect) {
	Recieve();
	if (Recieved_APID == Assigned_APID) {
		GreenState();
	} else if (Recieved_APID == APID_Array[1] || Recieved_APID == APID_Array[2] ||
	Recieved_APID == APID_Array[3] || Recieved_APID == APID_Array[4]) {
		BlueState();
		RedState();
		} else {
		RedState();
	}
}

void setup() {
	DDRB |= (1 << PB0) | (1 << PB1) | (1 << PB2) | (1 << PB3); // Set LED pins as output
	DDRD |= (1 << PD6); // Speaker pin output
	DDRD &= ~(1 << PD2); // Set INT0 (PD2) as input
	PORTD |= (1 << PD2); // Enable pull-up resistor

	initADC();
	EIMSK |= (1 << INT0); // Enable external interrupt INT0
	EICRA |= (1 << ISC01); // Falling edge trigger
	sei(); // Enable global interrupts
}

void loop() {
	uint16_t ObjectDetection = readADC(7);
	if (ObjectDetection > ODSensitivity) {
		OrangeState();
		RedState();
	}
}

void Recieve() {
	uint16_t HallRead;
	do {
		HallRead = readADC(6);
	} while (HallRead > 0);

	for (int i = 0; i < 4; i++) {
		for (int n = 0; n < 4; n++) {
			HallRead = readADC(6);
			bit[n] = (HallRead > 256) ? 1 : 0;
			_delay_ms(1);
		}
		idNum[i] = (bit[0] << 3) + (bit[1] << 2) + (bit[2] << 1) + bit[3];
	}
	Recieved_APID = (idNum[0] * 1000) + (idNum[1] * 100) + (idNum[2] * 10) + idNum[3];
}

void GreenState() {
	PORTB = (1 << PB0);
	_delay_ms(500);
}

void BlueState() {
	for (int i = 0; i < 4; i++) {
		PORTB |= (1 << PB1);
		_delay_ms(1000);
		PORTB &= ~(1 << PB1);
		_delay_ms(1000);
	}
}

void OrangeState() {
	for (int i = 0; i < 3; i++) {
		PORTB |= (1 << PB2);
		_delay_ms(1000);
		PORTB &= ~(1 << PB2);
		_delay_ms(1000);
	}
}

void RedState() {
	while (1) {
		PORTB |= (1 << PB3);
		_delay_ms(500);
		PORTB &= ~(1 << PB3);
		_delay_ms(500);
	}
}

void Error() {
	while (1) {
		PORTB = 0x0F;
		_delay_ms(1000);
		PORTB = 0x00;
		_delay_ms(1000);
	}
}

/* Arduino IDE code
#include <Arduino.h>

//Global Defined
#define VRef 12.0 //Voltage Reference for Hall sensor
#define ADC_Resolution 1024.0

//Global Variables
//Assign Sensors
const int ODSensor = A7;
const int HallSensor = A6;
const int ODSensitivity = 250;

//Digital Output pins
int Red_Led = 2;
int Orange_Led = 3;
int Blue_Led = 4;
int Green_Led = 5;
const int Speaker = 6;

//Functioning Variables
int ObjectDetection = 0;
int APID_Array[5] = {1238, 8953, 6666, 1794, 2486};
int Assigned_APID = 6666;
int Recieved_APID = 0; // Initialize/reset Art Piece ID
int state[2] = {0, 0};
int bit[4] = {0, 0, 0, 0}; // Binary input array
int idNum[4] = {0, 0, 0, 0}; // Single digit converted decimal array

//Function Prototypes
void Recieve();
void GreenState();
void BlueState();
void OrangeState();
void RedState();
void Error();

void setup() {

    Serial.begin(9600);

    //initialize pins
      pinMode(Green_Led, OUTPUT);
      pinMode(Blue_Led, OUTPUT);
      pinMode(Orange_Led, OUTPUT);
      pinMode(Red_Led, OUTPUT);
      pinMode(Speaker, OUTPUT);
}

void loop() {
    ObjectDetection = analogRead(ODSensor);

    if (ObjectDetection <= ODSensitivity) {
        Recieve();
        if (Recieved_APID == Assigned_APID) {
          GreenState();

        } 
        else if (Recieved_APID == APID_Array[1] || Recieved_APID == APID_Array[2] || Recieved_APID == APID_Array[3] || Recieved_APID == APID_Array[4]) {
          BlueState();
          RedState();

        }
        else {
          RedState();
        }

    } 
    else {
        OrangeState();
        RedState();

    }
}

void Recieve() {
    int HallRead;
    do {
      HallRead = analogRead(HallSensor);
    } while (HallRead > 0); // Wait for the 0V trigger

    for (int i = 0; i < 4; i++) {
      for (int n = 0; n < 4; n++) {
        HallRead = analogRead(HallSensor);

        if (HallRead > 256) {
          bit[n] = 1;
        } 
        else {
          bit[n] = 0;
        }
        delay(1);

      }
      idNum[i] = (bit[0] << 3) + (bit[1] << 2) + (bit[2] << 1) + (bit[3] << 0);

    }

    Recieved_APID = (idNum[0] * 1000) + (idNum[1] * 100) + (idNum[2] * 10) + idNum[3];

}

void GreenState() {
  //Change Leds
    digitalWrite(Green_Led, HIGH);
    digitalWrite(Blue_Led, LOW);
    digitalWrite(Orange_Led, LOW);
    digitalWrite(Red_Led, LOW);

  //Speaker Alert
    if (state[1] != 1) { //if the state was not previoiusly green play sound
      tone(Speaker, 2637);
      delay(500);
      noTone(Speaker);

    }

  //Update Security State
    state[1] = 1;

}

void BlueState() {
    state[1] = 2;

    digitalWrite(Green_Led, LOW);
    digitalWrite(Orange_Led, LOW);
    digitalWrite(Red_Led, LOW);

    for (int i = 0; i < 4; i++) {
      digitalWrite(Blue_Led, HIGH);
      tone(Speaker, 2637);
      delay(1000);
      digitalWrite(Blue_Led, LOW);
      noTone(Speaker);
      delay(1000);
    
    }

}

void OrangeState() {
    state[1] = 3;

    digitalWrite(Green_Led, LOW);
    digitalWrite(Blue_Led, LOW);
    digitalWrite(Red_Led, LOW);

    for (int i = 0; i < 3; i++) {
      digitalWrite(Orange_Led, HIGH);
      tone(Speaker, 2637);
      delay(1000);
      noTone(Speaker);
      digitalWrite(Orange_Led, LOW);
      delay(1000);
    
    }

}

void RedState() {
    state[1] = 4;

    digitalWrite(Green_Led, LOW);
    digitalWrite(Blue_Led, LOW);
    digitalWrite(Orange_Led, LOW);

    while (1) {
      digitalWrite(Red_Led, HIGH);
      tone(Speaker, 2637);
      delay(500);
      noTone(Speaker);
      digitalWrite(Red_Led, LOW);
      delay(500);
      
    }
    
}
*/
