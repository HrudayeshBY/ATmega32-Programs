/*
 * 8x8DotMatrixDisplay.c
 *
 * Created: 14-01-2025 08:27:46 PM
 * Author : hp
 */ 
// Trying to interface 8x8 dmd with atmega32 connected the dmd across 2 breadboards and used jumper wires to connect 16 pins to port d and c
//tried few patterns and understood the concept of persistence of vision
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
    DDRD = 0xFF;
	DDRC = 0xFF; //setting port d and c as output. port c will sink the current
	PORTD = 0x00;
	PORTC = 0x00;
	//Program to display the character H and small and big heart emoji on DMD
	unsigned int row[8] = {0xFE,0xFD,0xFB,0xF7,0xEF,0xDF,0xBF,0x7F};
	unsigned int col[8] = {
							//0xC3,0xC3,0xC3,0XFF,0XFF,0xC3,0xC3,0xC3
							//0x00,0x00,0X6C,0X7C,0X38,0X10,0X00,0X00
							0x00,0x66,0XFF,0XFF,0X7E,0X3C,0X18,0X00
							};
	unsigned int col1[8] = {0x00,0x00,0X6C,0X7C,0X38,0X10,0X00,0X00};
	int i = 0, j = 0;
	
    while (1) 
    {
		for(i = 0; i < 10; i++)
		{
			for(j = 0; j < 8; j++)
			{
				PORTC = row[j];
				PORTD = col[j];
				_delay_ms(1);
			}
		}
		_delay_ms(10);
		for(i = 0; i < 10; i++)
		{
			for(j = 0; j < 8; j++)
			{
				PORTC = row[j];
				PORTD = col1[j];
				_delay_ms(1);
			}
		}
			
			
    }
}

