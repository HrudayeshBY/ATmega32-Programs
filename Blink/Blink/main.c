#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

int main()
{
	DDRC = 0xFF; // setting all pins of port C as output pins
	//directly manipulating the data register is not good, we need to use bit manipulation
	while (1)
	{
		PORTC = 0xFF;
		_delay_ms(1000);
		PORTC = 0x00;
		_delay_ms(1000);
		PORTC = 0xAA;
		_delay_ms(1000);
		PORTC = 0x55;
		_delay_ms(1000);
		
		PORTC = 0x00;
		_delay_ms(1000);
		
		for(int i = 0;i < 8;i++)
		{
			PORTC = PORTC | (1<<i);
		    _delay_ms(100);

		}
		
		for(int i = 0;i < 8;i++)
		{
			PORTC = PORTC & (255>>i);
			_delay_ms(10);

		}
		for(int i = 0;i < 256;i++)
		{
			PORTC = i;
			_delay_ms(10);

		}
		for(int i = 255;i >= 0;i--)
		{
			PORTC = i;
			_delay_ms(10);

		}
		
		for(int i = 0;i < 8;i++)
		{
			PORTC = (1<<i);
			_delay_ms(100);

		}
		for(int i = 0;i < 8;i++)
		{
			PORTC = (255>>i);
			_delay_ms(100);

		}
	}
}

