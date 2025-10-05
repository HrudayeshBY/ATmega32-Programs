// Program to control LED Brightness / motor speed
#define  F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB |= (1<<PB3); // OC0 pin as output
	DDRB &= ~(1<<PB0) & ~(1<<PB1); // input pins
	TCCR0 = 0x69;
	uint8_t dutyCycle = 0;
	OCR0 = dutyCycle;
    while (1) 
    {
		if(!(PINB & (1<<PB0)))
		{
			while(!(PINB & (1<<PB0)));
			dutyCycle += 10;
			OCR0 = dutyCycle;
		}
		
		if(!(PINB & (1<<PB1)))
		{
			while(!(PINB & (1<<PB0)));
			dutyCycle -= 10;
			OCR0 = dutyCycle;
		}
		
		//for(short int i = 0; i < 255; i++)
		//{
			//OCR0 = i;
			//_delay_ms(10);
		//}
		//
		//for(short int i = 255; i > 0; i--)
		//{
			//OCR0 = i;
			//_delay_ms(10);	
		//}
    }
	
	return 0;
}

