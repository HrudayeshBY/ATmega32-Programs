//Practicing a simple uart transmit function
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

char msg[] = "Hi I am ATmega32\n\r";
ISR(USART_TXC_vect)
{
	PORTD |= (1<<PD2);
	_delay_ms(100);
	PORTD &= ~(1<<PD2);
	_delay_ms(100);
	PORTD |= (1<<PD2);
	_delay_ms(100);
	PORTD &= ~(1<<PD2);
	_delay_ms(100);
	UCSRA |= (1<<TXC);
}
void uart_init()
{
	DDRD |= (1<<PD1) | (1<<PD2); //UART transmit pin
	DDRD &= ~(1<<PD0); //UART receive pin
	UCSRA |= (1<<TXC); //simply clearing the transmission complete flag
	UCSRB |= (1<<TXCIE) | (1<<TXEN) | (1<<RXEN);
	UCSRC |= (1<<URSEL) | (1<<UCSZ0) | (1<<UCSZ1);
	UBRRH &= ~(1<<URSEL);
	UBRRL = 0x33;
	sei();
}

void uart_transmit(unsigned char data)
{
	while (!(UCSRA & (1<<UDRE)));
	UDR = data;
	_delay_ms(10);
}

void transmit_string(char * str)
{
	while(*str != '\0')
	{
		uart_transmit(*str);
		str++;
	}
}

int main(void)
{
	uart_init();
	while (1)
	{
		uart_transmit('H');
		_delay_ms(1000);
		transmit_string(msg);
	}
}