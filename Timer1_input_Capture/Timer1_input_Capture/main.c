//Operating timer 1 in INPUT capture mode
#define F_CPU 8000000UL
#include <util/delay.h> 
#include <avr/io.h>
#include <stdio.h>

void uart_init()
{
	DDRD |= 0x02; PORTD = 0x00;
	UCSRA &= ~(UCSRA);
	UCSRB = 0x18;
	UCSRC = 0x86;
	UBRRH &= ~(UBRRH);
	UBRRL = 0x33;
}

void uart_transmit(char data)
{
	UDR = data;
	while(!(UCSRA & (1<<TXC)))
	{
		//wait
	}
	_delay_ms(10);
}

char uart_receive()
{
	while(!(UCSRA & (1<<RXC)))
	{
		
	}
	char data = UDR;
	return data;
}

void uart_print(char* str)
{
	int i = 0;
	while(str[i] != '\0')
	{
		uart_transmit(str[i]);
		i++;
	}
}

void uart_println(char* str)
{
	int i = 0;
	while(str[i] != '\0')
	{
		uart_transmit(str[i]);
		i++;
	}
	uart_transmit('\n');
}
int main(void)
{
    uart_init();
    while (1) 
    {
		char buffer[40];
		DDRD &= ~(1<<PD6);
		TCCR1A &= ~(TCCR1A);
		TCCR1B = 0x43;
		
		while(!(TIFR & (1<<ICF1)))
		{
			//wait
		}
		sprintf(buffer,"The Captured value is %u\n\r",ICR1);
		uart_println(buffer);
		TIFR|= (1<<ICF1);
		
    }
}

