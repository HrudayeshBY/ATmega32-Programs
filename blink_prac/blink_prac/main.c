//Coming to Atmega32 after a long time brushing upon the core aspects of it
#define F_CPU 8000000UL // it is required as we will be using _delay_ms() function which will rewuire the speed of the CPU to provide exact amount of delay
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRD |= (1<<PD0) | (1<<PD1); //PD0 and PD1 are set HIGH
    while (1) 
    {
		PORTD |= (1<<PD0); // we will be toggling the pin for every 250ms
		PORTD &= ~(1<<PD1);
		_delay_ms(250);
		PORTD &= ~(1<<PD0);
		PORTD |= (1<<PD1);
		_delay_ms(250);
    }
}

