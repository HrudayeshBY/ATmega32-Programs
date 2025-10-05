//testing four input switches
#define F_CPU 8000000UL
#include <avr/io.h>

int main(void)
{
	DDRC = 0x00; PORTC = 0x00;
	DDRD = 0x03; PORTD = 0x00;
    while (1) 
    {
		if(!(PINC & 0x01))
		{
			PORTD = 0x01;
		}
		
		if(!(PINC & 0x02))
		{
			PORTD = 0x02;
		}
		
		if(!(PINC & 0x04))
		{
			PORTD = 0x03;
		}
		
		//else
		//{
			//PORTD = 0x00;
		//}
    }
}

