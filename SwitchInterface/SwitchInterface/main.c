/*
 * SwitchInterface.c
 *
 * Created: 11-01-2025 02:41:35 PM
 * Author : Hrudayesh B Y
 * This project aims to understand interfacing of push button switch in both pull down and pull up configuration
 * Will blink or light up some led to demo the same
 */ 

//Points: main() function arguments is made void because embedded application don't take any arguments unlike desktop c apllication
#define F_CPU 8000000UL// we are using he in built 8 MHz oscillator

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	/* This is push button interface
    //Setting up the PORT B and PORTC
	DDRC = 0xFF;//PC is made output
	DDRD = 0x00;//All are made input
    while (1) 
    {
		if ((PIND & (1<<7)) == 0)
		{
			PORTC = 0xAA;
		}
		else
		{
			PORTC = 0x55;
		}
		
    }*/
	
	//Relay Latching with Push button
	/*DDRD = 0x01;// PD7 is ip PD0 is op
	while(1)
	{
		if ((PIND & (1<<7)) == 0)
		{
			PORTD = 0x00;
		}
		else
		{
			PORTD = 0x01;

		}
	}*/
	// trying to check the input pull up configuration
	DDRD = 0x01; //PD0 is made output rest all are output
	PORTD = 0x80;//writing 7th bit high to enable internal pull up
	while(1)
	{
		if((PIND & (1<<7)) == 0)
		{
			PORTD = 0x81;
			//PD0 = 1;
		}
		else
		{
			PORTD = 0x80;
		}
	}
}

