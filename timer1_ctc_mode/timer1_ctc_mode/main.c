#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    DDRC = 0x00; PORTC = 0x00;
	DDRD = 0x30;  //OC1A and OC1B pins
	uint16_t a = 65535, b = 65535;
    while (1) 
    {
		if((PINC & 0x01) == 0)
		{
			while ((PINC & 0x01) == 0)
			{
				a += 10000;
			}
		}
		
		if((PINC & 0x02) == 0)
		{
			while ((PINC & 0x02) == 0)
			{
				a -= 10000;
			}
		}
		
		if((PINC & 0x04) == 0)
		{
			while ((PINC & 0x04) == 0)
			{
				b += 10000;
			}
		}
		
		if((PINC & 0x08) == 0)
		{
			while ((PINC & 0x08) == 0)
			{
				b -= 10000;
			}
		}
		
		//setting the OC1A and OC1B pins
		TCCR1A = 0xF0; TCCR1B = 0x0B;
		OCR1AL = a; OCR1AH = a;
		
		while((TIFR & 0x18) == 0)
		{
			//wait
		}
		TIFR |= 0x18;
		
		//clearing the OC1A and OC1B pins
		TCCR1A = 0xA0; TCCR1B = 0x0B;
		OCR1BL = b; OCR1BH = b;
		
		while((TIFR & 0x18) == 0)
		{
			//wait
		}
		TIFR |=0x18;
    }
}

