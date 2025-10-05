#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    DDRD |= (1<<PD1);
	DDRD &= ~(1<<PD0);
	PORTD |= (1<<PD0); //internal pull up resistor enabled
    while (1) 
    {
		if(!(PIND & (1<<PD0)))
		{
			PORTD |= (1<<PD1);
		}
		else
		{
			PORTD &= ~(1<<PD1);
		}
    }
}

