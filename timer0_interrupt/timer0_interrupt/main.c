#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

ISR(TIMER0_OVF_vect)
{
	PORTD ^= (1<<PD0);
	//_delay_ms(1000);
}
int main(void)
{
   DDRD |= 0x01;
   PORTD |= 0x00;
   TCCR0 = 0x05;
   sei();
   TIMSK |= (1<<TOV0);
   TCNT0 = 0x00;
    while (1) 
    {
    }
}

