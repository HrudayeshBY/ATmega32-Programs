#define F_CPU 8000000UL
#include "BLINK.h"
#include <avr/io.h>
#include <util/delay.h>

void blinky()
{
	DDRD = 0xFF;
	PORTD = 0xFF;
	_delay_ms(100);
	PORTD = 0x00;
	_delay_ms(100);
}