//External_Interrupt_yt
//Will be interfacing Switch to INT0, IR Sensor to INT1 and PIR sensor to INT2

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

ISR(INT0_vect)
{
	PORTD |= (1<<PD5);
	_delay_ms(250);
	PORTD &= ~(1<<PD5);
	_delay_ms(250);
}

ISR(INT1_vect)
{
	PORTD ^= (1<<PD6);
}

ISR(INT2_vect)
{
	PORTD |= (1<<PD7);
	_delay_ms(500);
	PORTD &= ~(1<<PD7);
	_delay_ms(500);
}

int main(void)
{
	DDRD &= ~(1<<PD2);
	DDRD &= ~(1<<PD3);
	DDRB &= ~(1<<PB2);
	DDRD |= (1<<PD4)|(1<<PD5)|(1<<PD6)|(1<<PD7);
	
	
	//Enabling the interrupts and setting the mode
	sei();
	GICR |= (1<<INT0)|(1<<INT1)|(1<<INT2);
	MCUCR |= (1<<ISC00); //INT1 will have low level trigger and INT0 will have both edge triggering
	MCUCSR |= (1<<ISC2); //INT2 will have positive edge triggering
	
	
    while (1) 
    {
		PORTD &= ~(1<<PD6);
		PORTD |=(1<<PD4);
		_delay_ms(100);
		PORTD &= ~(1<<PD4);
		_delay_ms(100);
    }
}

