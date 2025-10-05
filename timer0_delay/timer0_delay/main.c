#define F_CPU 8000000UL
#include <avr/io.h>

void timer0_delay()
{
	TCNT0 = 0x42; // the clock pulses will increment the count in the TCNT0 register
	while((TIFR & 0x01) == 0)
	{
		//keep checking till the interrupt flag is set
	}
	TIFR |= (1<<TOV0); //set the bit to clear it
}
int main(void)
{
    DDRD |= 0x01;
	PORTD |= 0x00;
	TCCR0 = 0x05; //setting the timer in normal mode and prescaler is 1024
	short int i;
    while (1) 
    {
		PORTD ^= 0x01;
		for(i = 0; i < 4; i++)
		{
			timer0_delay();
		}
    }
}

