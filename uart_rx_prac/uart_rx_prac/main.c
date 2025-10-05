//Practicing a simple uart transmit function
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

void uart_init()
{
	DDRD |= (1<<PD1) | (1<<PD2); //UART transmit pin
	DDRD &= ~(1<<PD0); //UART receive pin
	UCSRA |= (1<<TXC); //simply clearing the transmission complete flag
	UCSRB |= (1<<TXEN) | (1<<RXEN);
	UCSRC |= (1<<URSEL) | (1<<UCSZ0) | (1<<UCSZ1);
	UBRRH &= ~(1<<URSEL);
	UBRRL = 0x33;
}

void uart_transmit(unsigned char data)
{
	while (!(UCSRA & (1<<UDRE)));   // Wait until buffer is empty
	UDR = data;
}

unsigned char uart_receive()
{
	while(!(UCSRA & (1<<RXC)))
	{
		//wait
	}
	return UDR;
}
int main(void)
{
	uart_init();
	unsigned char info;
	while (1)
	{
		info = uart_receive();
		_delay_ms(100);
		uart_transmit(info);
		_delay_ms(1000);
	}
	
	return 0;
}