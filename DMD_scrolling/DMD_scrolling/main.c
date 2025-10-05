/*
 * DMD_scrolling.c
 *
 * Created: 15-01-2025 02:01:49 AM
 * Author : hp
 */ 
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    DDRD = 0xFF;//port pins connected to column
	DDRC = 0xFF;//port pins connected to rows
	PORTD = 0x00;
	PORTC = 0x00;
	
	unsigned int row[8] = {0xFE,0xFD,0xFB,0xF7,0xEF,0xDF,0xBF,0x7F};
	unsigned int col[8] = {0x00,0x00,0X08,0X04,0X3E,0X04,0X08,0x00};
	int i,j;

    while (1) 
    {
		for(i=0;i<8;i++)
		{
			for(j=0;j<8;j++)
			{
				PORTC = row[j];
				PORTD = col[j] >> i;
				_delay_ms(4);
			}
			//_delay_ms(10);
		}
		
		for(i=0;i<8;i++)
		{
			for(j=0;j<8;j++)
			{
				PORTC = row[j];
				PORTD = col[j] << (7-i);
				//_delay_ms(4);
				_delay_us(1200);
			}
			//_delay_ms(10);
		}
		

    }
}

