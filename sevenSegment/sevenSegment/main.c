/*
 * sevenSegment.c
 *
 * Created: 12-01-2025 02:10:59 PM
 * Author : hp
 */ 
//Program to interface the 7 segment common cathode display with port pins
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

int main(void)
{
	
    DDRD = 0xFF; //all pins of port D are output
	//this is unsigned array of hexa decimal number we want to display
	uint8_t sevenSegment[16] = {0xFD,0x61,0xDB,0xF3,0x67,0xB7,0xBF,0xE1,0xFF,0xF7,0xEF,0x3F,0x1B,0x7B,0x9F,0x8F};
    while (1) 
    {
		for(int i = 0;i<16;i++)
		{
			PORTD = sevenSegment[i];
			_delay_ms(1000);
			//PORTD = 0xFF;
			//PORTD = ~sevenSegment[i];
			//_delay_ms(1000);
		}
    }
	
	/*decoder ic op not coming
	DDRC = 0x0F;
	PORTC = 0x0F;
	while(1)
	{
		for(int i =0;i<10;i++)
		{
			PORTC = (char)i;
		}
	}
	*/
}

