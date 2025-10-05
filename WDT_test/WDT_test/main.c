//Program to test the Watch Dog Timer
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRD |= 0x01; PORTD = 0x00;
	//enabling WDT for 2.1 sec timeout
	WDTCR = 0x0F;
	PORTD = 0x01;
	_delay_ms(100);
	PORTD = 0x00;
	_delay_ms(100);
    while (1) 
    {
		//infinite loop WDT will reset
    }
}

