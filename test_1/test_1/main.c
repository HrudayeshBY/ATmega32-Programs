/*
 * test_1.c
 *
 * Created: 21-02-2025 12:27:42 AM
 * Author : hp
 */ 
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRA = 0xFF;
	DDRB = 0xFF;
	DDRC = 0xFF;
	DDRD = 0xFF;
	PORTA = 0x00;
	PORTB = 0x00;
	PORTC = 0x00;
	PORTD = 0x00;
    while (1) 
    {
			PORTA ^= 0xFF;
			PORTB ^= 0xFF;
			PORTC ^= 0xFF;
			PORTD ^= 0xFF;
			_delay_ms(100);
    }
}

