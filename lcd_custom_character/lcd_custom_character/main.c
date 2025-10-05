//Program to display custom character
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

void sendCommand(char cmd)
{
	PORTC = cmd;
	PORTD = 0x20;
	_delay_ms(1);
	PORTD = 0x00;
	_delay_ms(50);
}

void sendData(char data)
{
	PORTC = data;
	PORTD = 0xA0;
	_delay_ms(1);
	PORTD = 0x00;
	_delay_ms(50);
}

void lcd_init()
{
	sendCommand(0x38);
	sendCommand(0x01);
	sendCommand(0x0E);
	sendCommand(0x80);
}

void custom_char()
{
	sendCommand(0x48);
	sendData(0x1F);sendData(0x02);sendData(0x1F);sendData(0x02);
	sendData(0x1C);sendData(0x08);sendData(0x04);sendData(0x02);
	sendCommand(0x80);
	sendData(0x01);
	
	_delay_ms(500);
	
	sendCommand(0x50);
	sendData(0x00);sendData(0x00);sendData(0x1B);sendData(0x1F);
	sendData(0x0E);sendData(0x04);sendData(0x00);sendData(0x00);
	sendCommand(0x82);
	sendData(0x02);
	
	_delay_ms(500);
	
	sendCommand(0x58);
	sendData(0x00);sendData(0x1B);sendData(0x1B);sendData(0x00);
	sendData(0x00);sendData(0x11);sendData(0x0E);sendData(0x00);
	sendCommand(0x84);
	sendData(0x03);
	
	_delay_ms(500);
	
	sendCommand(0x60);
	sendData(0x11);sendData(0x0A);sendData(0X04);sendData(0x04);
	sendData(0x04);sendData(0x00);sendData(0x00);sendData(0x00);
	sendCommand(0x86);
	sendData(0x04);
	

}
int main(void)
{
	DDRC = 0xFF;
	DDRD = 0xE0;
	PORTC = 0x00;
	PORTD = 0x00;
	
	lcd_init();
	custom_char();
	while (1)
	{
		//Eat 5 star do nothing
	}
}

