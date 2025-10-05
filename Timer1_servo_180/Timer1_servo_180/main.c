#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    DDRD |= (1<<PD5); //OC1A pin as op
	TCCR1A = 0x82; TCCR1B = 0x1B; //Fast PWM , top value is taken from ICR1 register
	TCNT1 = 0x00; ICR1 = 2499;
    while (1) 
    {
		//OCR1A = 65;
		//_delay_ms(2500);
		//OCR1A = 175;
		//_delay_ms(2500);
		//OCR1A = 300;
		//_delay_ms(2500);
		
		// As now i understand the way to produce duty cycle we will iterate the loop for 
		//0 - 180 degree sweep
		float default_value = 2.6;
		float angle = 0; 
		for(int i = 0; i < 180; i++)
		{
			angle = 2499 * ((default_value + (0.052) * i)/100);
			OCR1A = angle;
			_delay_ms(10);
			
		}
		_delay_ms(1000);
		
		for(int i = 180; i > 0; i--)
		{
			angle = 2499 * ((default_value + (0.052) * i)/100);
			OCR1A = angle;
			_delay_ms(10);
			
		}
		_delay_ms(1000);
		
    }
}

