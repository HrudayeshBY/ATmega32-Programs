#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
    /* Replace with your application code */
	DDRD = 0xff;
    while (1) 
    {
		PORTD = 0xff;
		_delay_ms(1000);
		PORTD = 0x00;
		_delay_ms(1000);
    }
}

