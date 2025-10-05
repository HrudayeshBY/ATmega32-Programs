//practicing fast PWM and phase correct PWM
//fast pwm will up count only
//Phase correct pwm will down count 
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	DDRB |= (1<<PB3); //OC0 pin as output
	TCCR0 |= (1<<WGM00) | (1<<COM01) | (1<<CS02); //Fast PWM mode, inverting , CLK/256 prescaler	
	while (1)
	{
		for(int i = 0; i <= 255;i++)
		{
			OCR0 = i;
			//while (!(TIFR & (1<<OCR0)))
			//{
				////wait
			//}
			//TIFR |= (1<<OCR0);
			_delay_ms(10);
		}
		for(int i = 255; i > 1;i--)
		{
			OCR0 = i;
			//while (!(TIFR & (1<<OCR0)))
			//{
				////wait
			//}
			//TIFR |= (1<<OCR0);
			_delay_ms(10);
		}
	}
}