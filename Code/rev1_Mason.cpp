#include <stdio.h>

//define the sensor pin
  #define HALL_SENSOR_PIN A6

//define the reference voltage (5v)
  #define VREF 5.0

//define the ADC resolution for a 10-bit ADC (0-1023)
  #define ADC_RESOLUTION 1024.0

//Art Peice ID Database
  int Ref_APID;
  int Ref_APID[0] = 3692;
  int Ref_APID[1] = 6349;
  int Ref_APID[2] = 5588;
  int Ref_APID[3] = 9864;
  int Ref_APID[4] = 3351;
  int Ref_APID[5] = 3020;
  int Ref_APID[6] = 5379;
  int Ref_APID[7] = 9941;
  int Ref_APID[8] = 1343;
  int Ref_APID[9] = 4712;

//global variables
  int PedistaID = 1;
  int Assigned_APID = 3351;
  int state;

void setup(){
  Serial.begin(9600); //start serial communication
  while (!Serial);    //wait for serial connection
}

void loop(){
 
}

void Binary_To_APID(){//16bit binary input to 4 digit APID decimal number
  int Recieved_APID = 0;//initate / reset art peice id
  int bit[];//binary input array
  int idNum[];//single digit converted decimal array

  for(int i=0; i<=4; i++){//loop to convert 4 bit binary to id#
      for(int n = 1 ; n<=4; n++){//loop to read iput 4 bits at a time
        int sensorValue = analogRead(HALL_SENSOR_PIN); // Read raw analog value (0-1023)

        if (sensorValue > 0){//active high(0) or low(1)
        bit[n] = 1;//if active bit# = 1
        }
        else {
        bit[n] = 0;//else bit# = 0

        delay(1000)//magnetic feild read/sec
      }

      idNum[i] = (bit[1] * 2^3) + (bit[2] * 2^2) + (bit[3] * 2^1) + (bit[1] * 2^1);//4bit binary converted to single digit decimal 0-9
    }

    Recieved_APID = (idNum[1] * 1000) + (idNum[2] * 100) + (idNum[3] * 10) + idNum[4];//4 single digit decimals to 1 four digit decimal
}

void Secuity_Log(){
  Serial.print("Pedistal ID#: ");
  Serial.print(PedistaID);
  Serial.print(" | Assigned Art Piece ID#: ");
  Serial.print(Assigned_APID);
  serial.print(" | Received Art Piece ID#: ");
  Serial.print(Recieved_APID);
  serial.print(" | Security State")
  Serial.println(state);
  
}

void Database_Reference(int Recieved_APID, int Ref_APID[]){
  int case;

  for(int k = 0; k<=9; k++){
    
  }
  

}

