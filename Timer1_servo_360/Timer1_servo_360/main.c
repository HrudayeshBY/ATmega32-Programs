//program to control the speed and direction with button of 260 degree continious rotation Servo motor
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    DDRD |= (1<<PB5); //OC1A pin as output
	DDRD &= ~(1<<PD0) & ~(1<<PB1); // input pins to switch direction
	TCCR1A = 0x82; TCCR1B = 0x1B;
	ICR1 = 2499;
	OCR1A = 186; // no rotation

    while (1) 
    {
		while(!(PIND & (1<<PD0)))
		{
			OCR1A = 65;
		
		}
		while(!(PIND & (1<<PD1)))
		{
			OCR1A = 300;
		}
		OCR1A = 186; // no rotation
		
    }
}

