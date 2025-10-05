/*
 * L293D_Motor_Driver.c
 *
 * Created: 11-01-2025 11:00:39 PM
 * Author : hp
 */ 

#define F_CPU 800000000UL // used my compiler to calculate cycles for delay 
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRD = 0x03;//setting PD0 and PD1 as output
	PORTD = 0x00;
    while (1) 
    {
		PORTD = 0x01;
		_delay_ms(1000);
		PORTD = 0x00;
		_delay_ms(1000);
		PORTD = 0x02;
		_delay_ms(1000);
		PORTD = 0x00;
		_delay_ms(1000);
    }
}

