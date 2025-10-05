#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

ISR(INT0_vect)
{
	PORTC = 0x01;
	_delay_ms(1000);
	PORTC = 0x00;
	_delay_ms(1000);
	
	GIFR |= (1<<INTF0); // clearing the INT0 flag by writing one to it
}

ISR(INT2_vect)
{
	PORTC |= (1<<PC1);
	_delay_ms(100);
	PORTC &= ~(1<<PC1);
	_delay_ms(100);
	
	GIFR |= (1<<INTF2); //clearing the flag
}
int main(void)
{
	//I am using INT0 which is multiplexed with PD2
	DDRD |= (1<<PD0); //LED is connected to this pin
	DDRD &= ~(1<<PD2); // INT0 pin
	DDRB &= ~(1<<PB2);
	DDRC |= (1<<PC0) | (1<<PC1);
	
	//configuring the interrupts
	MCUCR &= ~(1<<ISC00) & ~(1<<ISC01); // rising edge will cause the interrupt
	MCUCSR |= (1<<ISC2);
	GICR |= (1<<INT0)| (1<<INT2); //enabling the interrupt INT0
	sei(); // global interrupt enable
	
	while (1)
	{
		//LED will be toggling in this loop
		PORTD |= (1<<PD0);
		_delay_ms(250);
		PORTD &= ~(1<<PD0);
		_delay_ms(250);
	}
}