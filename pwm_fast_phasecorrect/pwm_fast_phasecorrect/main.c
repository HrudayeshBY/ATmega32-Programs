//Fast and Phase Coreect PWM
//using timer 0
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	DDRB |= (1<<PB3); //OC0 pin
	DDRB &= ~(1<<PB0) & ~(1<<PB1); //input pins for incrementing and decrementing the duty cycle
	PORTB = 0x00;
	TCCR0 = 0x69; //fast pwm an non inverting
	//TCCR0 = 0x61;
	int duty_cycle = 127;
	OCR0 = duty_cycle;
    while (1) 
    {
		if(!(PINB & (1<<PB0)))
		{
			
			if(duty_cycle >= 255)
			{
				duty_cycle = 0;
			}
			duty_cycle += 10;
			OCR0 = duty_cycle;
		}
		
		if(!(PINB & (1<<PB1)))
		{
			if(duty_cycle <= 0)
			{
				duty_cycle = 255;
			}
			duty_cycle -= 10;
			OCR0 = duty_cycle;
		}
		
		//for(short int i = 0; i <= 255;i++)
		//{
			//OCR0 = i;
			//_delay_ms(10);
		//}
		//
		//for(short int i = 255; i >= 0;i--)
		//{
			//OCR0 = i;
			//_delay_ms(10);
		//}
    }
}

