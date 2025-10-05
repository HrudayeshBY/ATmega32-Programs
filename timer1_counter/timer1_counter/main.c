#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

ISR (TIMER1_OVF_vect)
{
	PORTD = 0x01;
	_delay_ms(1000);
	PORTD = 0x00;
	TCNT1 = 0xFFFA;
	TIFR |= (1<<TOV1);
	
}
int main(void)
{
	DDRD |= (1<<PD0);
	PORTD |= 0x00;
	DDRB = 0x00;
	PORTB = 0x00;
    sei(); // enabling the global interrupt
	TCCR1A = 0x00;
	TCCR1B = 0x07;
	TCNT1 = 0xFFFA;
	TIMSK |= (1<<TOIE1);
	
    while (1) 
    {
    }
}

