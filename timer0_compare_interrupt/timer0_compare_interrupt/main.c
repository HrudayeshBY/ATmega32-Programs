#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>

ISR (TIMER0_COMP_vect)
{
	PORTB ^= 0x04;
	TIFR |= (1<<OCF0);
}
int main(void)
{
	sei(); // global interrupt enable
	DDRB |= 0x0C;
	TCCR0 = 0x1D; // 1/1024 prescaler ,ctc mode, in toggle mode
	TIMSK |= (1<<OCIE0); // enabling interrupt on output compare
	OCR0 = 0xC8; // 200 in decimal
	while(1)
	{
		// no operation just looping
	}
}