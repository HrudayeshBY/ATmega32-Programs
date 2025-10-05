//Program to demonstrate the working of sw1 and sw2 on development board
// to comment selected lines press ctrl + k and ctrl + c
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB = 0x03;//PB0 and PB1 are op
	DDRD = 0x00;// PD0 is ip and PD1 is op
	PORTB = 0x00; //Initially all values are zero
    while (1) 
    {
		if((PIND & 0x03) == 0x02)
		{
			PORTB |= (1<<0);
		}
		else
		{
			PORTB &= ~(1<<0);
		}
		
		if((PIND & 0x03) == 0x01)
		{
			PORTB |= (1<<1);
		}
		else
		{
			PORTB &= ~(1<<1);
		}
    }
}

