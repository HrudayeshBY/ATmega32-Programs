//Operating timer 1 in INPUT capture mode
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
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

ISR (TIMER1_CAPT_vect)
{
	char buffer[40];
	PORTC ^=0x80;
	sprintf(buffer,"The Captured value is %u\n\r",ICR1);
	uart_println(buffer);
	TIFR|= (1<<ICF1);
}
int main(void)
{
	uart_init();
	sei();
	DDRD &= ~(1<<PD6);
	DDRC = 0x80;
	TCCR1A &= ~(TCCR1A);
	TCCR1B = 0x43;
	TIMSK |= (1<<TICIE1); //enabling timer/counter input capture interrupt
	while (1)
	{
		//do nothing	
	}
}

