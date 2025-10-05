//Trying to interface two push button to blink led at a different rate
//Button in active low, pulled HIGH
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRC &= ~(1<<PC0) & ~(1<<PC1); //PC0 and PC1 pin set as input
	DDRD |= (1<<PD0) | (1<<PD1);
	while (1)
	{
		if((PINC & 0x03) == 0x02)
		{
			PORTD |= (1<<PD0);
			PORTD &= ~(1<<PD1);
			_delay_ms(300);
			PORTD |= (1<<PD1);
			PORTD &= ~(1<<PD0);
			_delay_ms(300);
		}

		else if((PINC & 0x03) == 0x01)
		{
			PORTD |= (1<<PD0);
			PORTD &= ~(1<<PD1);
			_delay_ms(200);
			PORTD |= (1<<PD1);
			PORTD &= ~(1<<PD0);
			_delay_ms(200);
		}
		else
		{
			PORTD |= (1<<PD0);
			PORTD &= ~(1<<PD1);
			_delay_ms(100);
			PORTD |= (1<<PD1);
			PORTD &= ~(1<<PD0);
			_delay_ms(100);
		}
	}
}