#include <servo.h>

#define PHOTORESISTOR PB0

#define ID_SENSOR PC4
#define GREENLED PA4
#define ORANGELED 
#define BLUELED
#define REDLED
#define SPEAKER
#define SERVO

#define LIGHT_THRESHOLD 500
#define ALARM TIMEOUT 1000
#define SLOW_BEEP_INTERVAL 1000
#define FAST_BEEP_INTERVAL 2000

enum systemstate{
	NORMAL = 1;
	OBJECT_REMOVED = 2;
	WRONG_OBJECT = 3;
	HIGH_ALERT = 4;
};

servo securityservo;

systemstate currentstate = NORMAL;
unsigned long statestarttime = 0;
unsigned long lastbeeptime = 0;
bool alertactive = false;

void setup(){
	
	serial.begin(9600); // debugging have to have don't know why
	
	pinMode(PHOTORESISTOR, INPUT);
	pinMode(ID_SENSOR, INPUT);
	pinMode(GREENLED, OUTPUT);
	pinMode(BLUELED, OUTPUT);
	pinMode(ORANGELED, OUTPUT);
	pinMode(REDLED, OUTPUT);
	
	securityservo.attach(SERVO);
	securityservo.write(90); // default position
	
	setsystemstate(NORMAL);
}

void loop(){
	
	int lightlevel = analogRead(PHOTORESISTOR);
	int iddetected = analogRead(ID_DETECTION);
	
	systemstate newstate;
	
	if(lightlevel > LIGHT_THRESHOLD{
		if(id_detected){
			newstate = NORMAL;
		}
		else{
			newstate = WRONG_OBJECT;
		}
	} else {
		newstate = OBJECT_REMOVED;
	}
	
	if(newstate != currentstate){
		setsystemstate(newstate);
	}
	
	if((currentstate == OBJECT_REMOVED || currentstate = WRONG_OBJECT) && millis() - statestarttime > ALARM_TIMEOUT){
		setsystemstate(HIGH_ALERT);
	}
	
	
	switch(currentstate){
		
		case NORMAL: 
			digitalWrite(GREENLED, HIGH);
			digitalWrite(ORANGELED, LOW);
			digitalWrite(BLUELED, LOW);
			digitalWrite(REDLED, LOW);
			digitalWrite(SPEAKER, LOW);
			break;
		
		
		case OBJECT_REMOVED:	
			digitalWrite(GREENLED, LOW);
			digitalWrite(ORANGLED, HIGH);
			digitalWrite(BLUELED, LOW);
			digitalWrite(REDLED, LOW);
		
			if(millis() - lastbeeptime > SLOW_BEEP_INTERVAL){
				beepstate = !beepstate;
				digitalWrite(SPEAKER, beepstate);
			}
			break;
		
		case WRONG_OBJECT:
			digitalWrite(GREENLED, LOW);
			digitalWrite(ORANGELED, LOW);
			digitalWrite(BLUELED, HIGH);
			digitalWrite(REDLED, LOW);
			
			if(millis() - lastbeeptime > SLOW_BEEP_INTERVAL){
				beepstate = !beepstate;
				digitalWrite(SPEAKER, beepstate);
				lastbeeptime = millis()
			}
	
	
	
	
	
	
	
	


}
