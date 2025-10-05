//Stepper Motor Interfacing
// All modes of stepping wave, full, half , micro
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	int time = 3,i = 0,steps = 128;
	//The ULN driver is connected to PORT D first 4 pins
	DDRD = 0x0F;//o,1,2,3 pins are output
	PORTD = 0x00;
    while (1) 
    {
		/*
		Wave Step
		for(i = 0; i < steps;i++)
		{
			PORTD = 0x01;
			_delay_ms(time);
			PORTD = 0x02;
			_delay_ms(time);
			PORTD = 0x04;
			_delay_ms(time);
			PORTD = 0x08;
			_delay_ms(time);
			
		}
		_delay_ms(1000);
		*/
		
		/*
		Full Step
		for(i = 0; i < steps;i++)
		{
			PORTD = 0x03;
			_delay_ms(time);
			PORTD = 0x06;
			_delay_ms(time);
			PORTD = 0x0C;
			_delay_ms(time);
			PORTD = 0x09;
			_delay_ms(time);
			
		}
		_delay_ms(1000);
		*/
		
		/* Half Step
		for(i = 0; i < steps/2;i++)
		{
			PORTD = 0x01;
			_delay_ms(time);
			PORTD = 0x03;
			_delay_ms(time);
			PORTD = 0x02;
			_delay_ms(time);
			PORTD = 0x06;
			_delay_ms(time);
			PORTD = 0x04;
			_delay_ms(time);
			PORTD = 0x0C;
			_delay_ms(time);
			PORTD = 0x08;
			_delay_ms(time);
			PORTD = 0x09;
			_delay_ms(time);
			
		}
		_delay_ms(1000);
		*/
		
		//Micro Step
		for(i = 0; i < 3;i++)
		{
			PORTD = 0x01;
			_delay_ms(time);
			PORTD = 0x03;
			_delay_ms(time);
			PORTD = 0x02;
			_delay_ms(time);
			PORTD = 0x06;
			_delay_ms(time);
			PORTD = 0x04;
			_delay_ms(time);
			PORTD = 0x0C;
			_delay_ms(time);
			PORTD = 0x08;
			_delay_ms(time);
			PORTD = 0x09;
			_delay_ms(time);
			
		}
		_delay_ms(1000);
		
		
		
    }
}

