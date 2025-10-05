//Program to demonstrate the timer 1 operation in norml mode. Timer 1 is a 16bit timer
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

void timer1_delay()
{
	TCNT1 = 0x00; //setting the timer as zero
	while((TIFR & (1<<TOV1)) == 0)
	{
		//wait for 65536 ticks
	}
	//clearing the bit by setting it high again
	TIFR |= (1<<TOV1);
	
}
int main(void)
{
    DDRD |= 0x01;
	PORTD = 0x00;
	TCCR1A = 0x00; TCCR1B = 0x02;
    while (1) 
    {
		PORTD ^= 0x01;
		timer1_delay();
    }
}

