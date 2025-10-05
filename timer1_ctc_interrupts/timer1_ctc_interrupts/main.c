//We will be using the OCIE interrupts to toggle led 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>

ISR (TIMER1_COMPA_vect)
{
	PORTD ^= 0x01;
	TIFR |= (1<<OCIE1A);
}

ISR (TIMER1_COMPB_vect)
{
	PORTD ^= 0x02;
	TIFR |= (1<<OCIE1B);
}
int main(void)
{
	sei();
	DDRD |= 0x02;
    TCCR1A = 0x50; TCCR1B = 0x0A;
	OCR1A = 50000; OCR1B = 30000;
	TIMSK |= (1<<OCIE1A) | (1<<OCIE1B);
    while (1) 
    {
		//eat 5 star do nothing
    }
	
}

