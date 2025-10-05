// program to demonstarte the analog comparator interrupt
// the interrupt has many mode, we are using the interrupt when toggle happens
#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

ISR(ANA_COMP_vect)
{
	//when interrupt occurs the interrupt flag is set it has to cleared
	PORTC ^= (1<<PD0);
}
int main(void)
{
	DDRB = 0x00; PORTB = 0x00;
	DDRD = 0x01; PORTD = 0x00;
	DDRC = 0x01; PORTC = 0x00; // used to toggle led on interrupt
	sei(); //global interrupt enable
	SFIOR |= (1<<ACME); //enabling the negative input from AIN1
	ACSR = 0x08; //enabling the AC interrupt
	
    
    while (1) 
    {
		//main program toggling led 
		PORTD ^= (1<<PD0);
		_delay_ms(500);
    }
}

