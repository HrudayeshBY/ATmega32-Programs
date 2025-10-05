//Program to test the analog Comparator

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>


//int main(void)
//{
	//SFIOR |=(1<<ACME); // set the analog comparator multiplexer enable bit
	//ACSR = 0x00;
	//DDRB = DDRB & ~(1<<PB2) & ~(1<<PB3); // input pins
	//DDRD |= (1<<PD0); // setting PD0 pin as output
	//
    //while (1) 
    //{
		//if((ACSR & (1<<ACO)))
		//{
			//PORTD |= (1<<PD0);
		//}
		//else
		//{
			//PORTD &= ~(1<<PD0);	
		//}
	//}
//}

// program to use one of the adc channels as the negative input terminal for the comparator

int main(void)
{
	DDRD |= (1<<PD0);PORTD = 0x00;
	DDRA = 0x00;PORTA = 0x00;
	DDRB &= ~(1<<PB2) & ~(1<<PB3);PORTB = 0x00;
	SFIOR |= (1<<ACME); //we are setting the ACME bit as zero
	ACSR &= 0x00;
	ADMUX = 0x07; //enabling the ADC7 channel
	ADCSRA = 0x00;
	
	while (1)
	{
		if(ACSR & (1<<ACO))
	    {
			PORTD = 0x01;
	    }
	    else
	    {
			PORTD = 0x00;
	    }
	}
}

