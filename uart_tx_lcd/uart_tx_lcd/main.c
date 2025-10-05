//program to receive serial data from pc and print it on LCD
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

void sendCommand(char cmd)
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
	PORTD = 0x00;
}

void lcd_init()
{
	sendCommand(0x38);
	sendCommand(0x01);
	sendCommand(0x0E);
	sendCommand(0x80);
}

void lcd_clear()
{
	sendCommand(0x01);
	sendCommand(0x80);
}
void uart_init()
{
	//This function enables UART communication protocol
	//DDRD |=(1<<PD1);
	//DDRD |= ~(1<<PD0);
	//UCSRA = UCSRA | ~(1<<MPCM) | ~(1<<U2X) | ~(1<<TXC);
	//UCSRB = UCSRB | (1<<RXEN) | (1<<TXEN);
	//UCSRC = UCSRC | ~(1<<URSEL) | ~(1<<USBS) | (1<<UCSZ2) | (1<<UCSZ0);
	//UBRRH = 0x00; UBRRL = 0x33;
	
	UCSRA = 0x00;UCSRB = 0x18;UCSRC = 0x06;
	UBRRH = 0x00;UBRRL = 0x33;
}

void transmit(char data)
{
	UDR = data;
	while((UCSRA & 0x40) == 0)
	{
		
	}
	_delay_ms(100);
}

char receive()
{
	
	while((UCSRA & 0x80) == 0)
	{
		// receiving data
	}
	char data = UDR;
	_delay_ms(100);
	
	return data;
}
int main(void)
{
  DDRC = 0xFF;DDRD = 0xE2;
  PORTD = 0x00; PORTC = 0x00;
  lcd_init();
  uart_init();
  char incomingData;
  
    while (1) 
    {
		//lcd_clear();
		incomingData = receive();
		sendData(incomingData);
		transmit(incomingData);
		_delay_ms(2000);
		
		//transmit('h');
		//_delay_ms(1000);
    }
}

