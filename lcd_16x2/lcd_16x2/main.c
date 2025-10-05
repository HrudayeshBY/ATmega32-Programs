/*
 * lcd_16x2.c
 *
 * Created: 15-01-2025 09:48:46 PM
 * Author : hp
 */ 
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

void sendCmd(char cmd)
{
	PORTC = cmd;
	PORTD = 0x20;
	_delay_ms(100);
	PORTD = 0x00;
}

void sendData(char data)
{
	PORTC = data;
	PORTD = 0xA0;
	_delay_ms(100);
	PORTD = 0x80;
}

int main(void)
{
    DDRC = 0xFF;
	DDRD = 0xFF;
	PORTC = 0x00;
	PORTD = 0x00;
	sendCmd(0x38);
	sendCmd(0x80);
	sendCmd(0x01);
	sendCmd(0x0E);
	sendCmd(0x06);
	sendCmd(0x01);
	int count = 0;
	for(char c = 65;c<120;c++)
	{
		sendData(c);
		count++;
		if(count >16)
		{
			count = 0;
			sendCmd(0x01);
			sendCmd(0x80);
		}
	}
	sendData('A');
	

	
    while (1);
 
}

