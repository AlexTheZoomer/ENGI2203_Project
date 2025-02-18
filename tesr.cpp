int main(void)

{

              DDRB = (1<<PORTB5); // set the data direction register at D0 so that it is in write mode

              PORTB = 0x00; // write 0 to the port

              DDRC = (1<<PORTC0);

              PORTC = 0b11111111;

    while (1==1) //  loop forever

    {

                             if(PINC & (1<<PC0))  // if we're reading 1 on PORTC.0 (Nano Pin A0)

                             {

                                           PORTB |= 0x20; // first set the output PB5 to 1

                                           Delay(1000);

                                           PORTB &= 0xDF; // then set the output PB5 to 0

                                           Delay(1000);    

                             }

              }

}

void AND(){
	
	if(C0=1 && C1=1 && D7=1){
	B0 = 1;
	
	}
	else{
		B0 = 0;
		
	}

}

void NOT(){
	DDRD &= ~(1<<PORTD2);
	DDRB |= (1<<PORTB1);
	PORTB &= ~(1<<PORTB1);
	
	while(1){
	
		if(!(PIND & (1<<PORTD2)){
			PORTB |= (1<<PORTB1);
		
		}
		else{
			PORTB &= ~(1<<PORTB1);
			
		}
	}
}

void NOR(){
	DDRD &= ~((1<<PORTD3) | (1<<PORTD5));
	DDRB |= (1<<PORTB2);
	PORTB &= ~(1<<PORTB2);
	
	while(1){
		if(!(PIND & (1<<PORTD3)) && !(PIND & (1<<PORTD5))){ //NOR
			PORTB |= (1<<PORTB2);
		
		}
		else{
			PORTB &= ~(1<<PORTB2);
			
		}
	}

}


if(D4==D6){ //XNOR
	B3 = 1;
	
}
else{
	B2 = 0;
	
}
