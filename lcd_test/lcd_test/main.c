//LCD Test program

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

void sendCommand(char cmd)
{
	PORTC = cmd;
	PORTD = 0b00100000;
	_delay_ms(100);
	PORTD = 0b00000000;
}

void sendData(char data)
{
	PORTC = data;
	PORTD = 0b10100000;
	_delay_ms(100);
	PORTD = 0b00000000;
}

void lcd_init()
{
	sendCommand(0x38);
	sendCommand(0x0E);
	sendCommand(0x01);
	sendCommand(0x80);
}
int main(void)
{
	int count = 0;
	char c = 0;
	DDRC = 0xFF;
	DDRD = 0xE0;
	PORTC = 0x00;
	PORTD = 0x00;
	lcd_init();
	for(c = 65;c<97;c++)
	{
		count++;
		if(count == 16)
		{
			sendCommand(0xC0);
		}
		sendData(c);
		
	}
	for(int i = 0;i < 40;i++)
	{
		sendCommand(0x18);
		_delay_ms(100);
	}
    
    while (1) 
    {
    }
	
}

