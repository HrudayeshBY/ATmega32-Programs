// I will be connecting the led to visualize the toggling of the led by oc0 pin 
// I am using 1/1024 pre-scaler and feed 250 to the OCR register

#define  F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB |= (1<<PB3); //OC0 pin set as output
	DDRC = 0x00; //all pins are made as input
	OCR0 = 0xFA; // 250 in decimal
	TCCR0 = 0x1D; // prescaler set to 1/1024
	
	while(1)
	{
		if((PINC & 0x01) == 0)
		{
			while ((PINC & 0x01) == 0x00)
			{
				OCR0 += 10;
			}
		}
		if((PINC & 0x02) == 0x01)
		{
			while ((PINC & 0x02) == 0x01)
			{
				OCR0 -= 10;
			}
		}
	}
	
    
}

