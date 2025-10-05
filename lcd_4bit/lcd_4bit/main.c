//Program to display string in 4 bit mode
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

void sendCommand(char cmd)
{
	PORTC = (cmd & 0xF0);
	PORTD = 0x20;
	_delay_ms(100);
	PORTD = 0x00;
	PORTC = ((cmd<<4) & 0xF0);
	PORTD = 0x20;
	_delay_ms(100);
	PORTD = 0x00;
}

void sendData(char data)
{
	PORTC = (data & 0xF0);
	PORTD = 0xA0;
	_delay_ms(100);
	PORTD = 0x00;
	PORTC = ((data<<4) & 0xF0);
	PORTD = 0xA0;
	PORTD = 0x00;
}

void lcd_init()
{
	sendCommand(0x02);
	sendCommand(0x28);
	sendCommand(0x0E);
	sendCommand(0x01);
	sendCommand(0x80);
}

void display(char* str)
{
	int i = 0;
	while(str[i] != '\0')
	{
		sendData(str[i]);
		i++;
	}
}
int main(void)
{
	DDRC = 0xF0;
	DDRD = 0xE0;
	PORTC = 0x00;
	PORTD = 0x00;
	
	lcd_init();
	display("Hrudayesh B Y");
	sendCommand(0xC0);
	display("ECE Engineer");
	while (1)
	{
		if((PIND & 0x03) == 0x02)
		{
			sendCommand(0x1C);
			_delay_ms(100);
		}
		
		if((PIND & 0x03) == 0x01)
		{
			sendCommand(0x18);
			_delay_ms(100);

		}
	}
}

