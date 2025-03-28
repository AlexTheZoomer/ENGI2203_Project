#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

// Pin Definitions
#define PhotoResistor 7  // Photoresistor connected to ADC7
#define Green_Led PD2     // Green LED (Correct APID)
#define Blue_Led PD3      // Blue LED (Valid but Not Assigned APID)
#define Red_Led PD5       // Red LED (Invalid APID)
#define Orange_Led PD4

// APID System
int APID_Array[5] = {1238, 8953, 6666, 1794, 2486}; // List of valid APIDs
int Assigned_APID = 6666;  // Expected APID
int Recieved_APID = 1238;  // Manually set APID for testing

void GREEN();
void BLUE();
void ORANGE();
void RED();

void setupADC(){
	ADMUX = (1 << REFS0) | (1 << MUX2) | (1 << MUX1) | (1 << MUX0); // Select ADC7 (Photoresistor)
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Enable ADC
}

uint16_t readADC(){
	ADCSRA |= (1 << ADSC);
	while (ADCSRA & (1 << ADSC));
	return ADC;
}

// Function to check if Recieved_APID exists in APID_Array
int isValidAPID(int apid) {
	for (int i = 0; i < 5; i++){
		if (APID_Array[i] == apid) {
			return 1; // Found in array
		}
	}
	return 0; // Not found
}

void loopForever(){
	while (1){  // Infinite loop to continuously check the sensor
		uint16_t lightLevel = readADC(); // Read ADC value once to check light level

		if (lightLevel < 500){  // Only check APID if the sensor is covered
			Covered();
		}
		else{
			int i = 0
			
			if ( i == 1){
				RED();
			}
			Else if (i ==0){
				Exposed();
				i++;
				break;
			}

		}
			_delay_ms(100); // Small delay to prevent overwhelming the CPU
	}
}

int main(){
	DDRD |= (1 << Green_Led) | (1 << Blue_Led) | (1 << Red_Led) | (1 << Orange_Led);  // Set LEDs as OUTPUT
	PORTD &= ~((1 << Green_Led) | (1 << Blue_Led) | (1 << Red_Led) | (1 << Orange_Led)); // Start with LEDs OFF

	setupADC();
	loopForever();

	return 0;
}

void GREEN(){
	PORTD |= (1 << Green_Led);  // ? Correct APID - Turn on Green LED
	PORTD &= ~((1 << Blue_Led) | (1 << Red_Led) | (1 << Orange_Led)); // Turn off others
}

void BLUE(){
	PORTD |= (1 << Blue_Led);   // ?? Valid but not assigned - Turn on Blue LED
	PORTD &= ~((1 << Green_Led) | (1 << Red_Led) | (1 << Orange_Led));
}

void RED(){
	PORTD |= (1 << Red_Led);    // ? Invalid APID - Turn on Red LED
	PORTD &= ~((1 << Green_Led) | (1 << Blue_Led) | (1 << Orange_Led));
}

void ORANGE(){
	PORTD |= (1 << Orange_Led); // Orange LED for when light is not detected
	PORTD &= ~((1 << Green_Led) | (1 << Blue_Led) | (1 << Red_Led));
}

void Covered(){
	if (Recieved_APID == Assigned_APID){
		GREEN();
	}
	
	else if (isValidAPID(Recieved_APID)) {
		BLUE();
		_delay_ms(4000);
		
		read();
		
		if (Recieved_APID == Assigned_APID){
			GREEN();
			
		}
		
		else{
			RED();
		}
	}

	else {
		ORANGE();
		_delay_ms(3000);
		
		read();
		
		if (Recieved_APID == Assigned_APID){
			break;
		}
		
		else if (isValidAPID(Recieved_APID)){
			BLUE();
			_delay_ms(4000);
			
			read();
			
			if (Recieved_APID == Assigned_APID){
				break();
				
			}
			else if{
				RED();
			}
		}
		else {
			RED();
		}
	}
}

	
}

void Exposed(){
	ORANGE();
	_delay_ms(3000);
	return

}

void read(){
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
}


