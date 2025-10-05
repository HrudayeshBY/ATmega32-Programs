//Here i will be defining the function
#include "UART.h"
void UART_init()
{
	DDRD |= (1<<PD1);
	DDRD &= ~(1<<PD0);
	UCSRA = 0x00;
	UCSRB = (1<<RXEN) | (1<<TXEN);
	UCSRC = (1<<URSEL) | (1<<UCSZ0) | (1<<UCSZ1);
	UBRRH = 0x00;
	UBRRL = 0x33;
}
void UART_transmit_character(char data)
{
	
	while(!(UCSRA & (1<<UDRE)))
	{
		
	}
	UDR = data;// Placing the data on the Uart data register
}
char UART_receive_character()
{
	char data;
	while(!(UCSRA & (1<<RXC)))
	{
		
	}
	data = UDR;
	return data;
}
void UART_print(char* str)
{
	int n = 0;
	while(str[n] != '\0')
	{
		UART_transmit_character(str[n]);
		n++;
	}
	UART_transmit_character('\r');
}
void UART_println(char* str)
{
	int n = 0;
	while(str[n] != '\0')
	{
		UART_transmit_character(str[n]);
		n++;
	}
	UART_transmit_character('\n');
	UART_transmit_character('\r');
}