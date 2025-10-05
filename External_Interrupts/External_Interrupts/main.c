// C program to implement external interrupts in ATmega32
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

ISR(INT2_vect)
{
	PORTC = 0x01;
	_delay_ms(100);
	//PORTC = 0x00;
	//_delay_ms(100);
}
int main(void)
{
    //INT 0 is multiplexed with pin PD2
	DDRB = 0x01;
	DDRC = 0x80;
	DDRD = 0x00;// the interrupt pins should be made as input
	
	PORTB = 0x00;
	PORTC = 0x00;
	//PORTD = 0x00;
	
	// we should enable interrupt, global interrupt enable. interrupt mode
	sei();// global interrupt enable
	GICR = 0x20; // enabling INT2
	MCUCSR = 0x40;
	
    while (1) 
    {
		PORTB ^= 0x01;
		_delay_ms(200);
		PORTC = 0x00;
    }
}

