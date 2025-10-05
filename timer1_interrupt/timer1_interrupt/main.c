//To toggle led on timer 1 overflow interrupt
// using 1/64 pre scaler expecting a delay of 4 seconds

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

ISR (TIMER1_OVF_vect)
{
	PORTD ^= 0x01;
	TIFR |= (1<<TOV1);
}
int main(void)
{
	sei();
    DDRD |= (1<<PD0);
	PORTD &= ~(1<<PD0);
	TCNT1 = 0x0000;
	TCCR1A = 0x00;
	TCCR1B = 0x03;
	TIMSK |= (1<<TOIE1);
	
    while (1) 
    {
    }
}

