//Will be practicing the timer as counter
//TRYING TO PUT 75% DUTY CYCLE BY TOGGLING BETWEEN TWO MODES
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

//ISR (TIMER0_OVF_vect)
//{
	//PORTB ^= (1<<PB1);
	//_delay_ms(100);
	//PORTB ^= (1<<PB1);
	//_delay_ms(100);
	//TIFR |= (1<<TOV0);
	//TCNT0 = 0xFA;
//}
//int main(void)
//{
	////initializing the timer
	//TCCR0 |= (1<<CS02) | (1<<CS01) | (1<<CS00); //rising edge on T0 pin will act as clock source
	//TIMSK |= (1<<TOIE0);
	//DDRB &= ~(1<<PB0);//T0 pin
	//DDRB |= (1<<PB1);
	//TCNT0 = 250;
	//sei();
	//while (1)
	//{
//
	//}
//}

int main(void)
{
	DDRB |= (1<<PB3);
	while (1)
	{
		
		TCCR0 |= (1<<WGM01) | (1<<COM00) | (1<<COM01) | (1<<CS02) | (1<<CS00); //IN CTC mode and set OC0 pin on compare match
		OCR0 = 127;
		while (!(TIFR & (1<<OCF0)))
		{
			//wait
		}
		TIFR |= (1<<OCF0); // clearing the output compare flag
		TCCR0 = 0x00;
		TCCR0 |= (1<<WGM01) | (1<<COM01) | (1<<CS02) | (1<<CS00); //IN CTC mode and clear OC0 pin on compare match
		OCR0 = 127;
		while (!(TIFR & (1<<OCF0)))
		{
			//wait
		}
		TIFR |= (1<<OCF0); // clearing the output compare flag
		
	}

}