// Program to implement fast and Phase correct pwm in atmega32
// Timer 1 has 2 Output Compare OC pins OC1A and OC1B
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRD |= (1<<PB5) | (1<<PB4);
	DDRD &= ~(1<<PD0) & ~(1<<PD1);
    TCCR1A = 0xA3;
	//TCCR1B = 0x09;// 10bit fast pwm
	TCCR1B = 0x01; //10bit phase correct PWM
	uint16_t a_duty_cycle = 512, b_duty_cycle = 512;
    while (1) 
    {
		if(!(PIND & (1<<PD0)))
		{
			while(!(PIND & (1<<PD0)));
			a_duty_cycle += 100;
			b_duty_cycle -= 100;
			OCR1A = a_duty_cycle;
			OCR1B = b_duty_cycle;
		}
		
		if(!(PIND & (1<<PD1)))
		{
			while(!(PIND & (1<<PD0)));
			a_duty_cycle -= 100;
			b_duty_cycle += 100;
			OCR1A = a_duty_cycle;
			OCR1B = b_duty_cycle;
		}
    }
}

