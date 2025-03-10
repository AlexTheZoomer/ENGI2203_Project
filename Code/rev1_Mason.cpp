#include <stdio.h>

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

