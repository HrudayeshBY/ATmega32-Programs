#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

ISR(TIMER0_OVF_vect)
{
	PORTB |= (1<<PB1);
	_delay_ms(2000);
	PORTB &= ~(1<<PB1);
	TIFR |= (1<<TOV0); //clearing the bit in the 
}
int main(void)
{
	sei();
	DDRB &= ~(1<<PB0);
	DDRB |= (1<<PB1);
	PORTB = 0x00;
	TCCR0 = 0x07;
	TIMSK = (1<<TOIE0);
	TCNT0 = 0xF9;

    while (1) 
    {
		while((TIFR & 0x01) == 0)
		{
			//wait
		}
		TCNT0 = 0xF9;
    }
}

