//Prorgam to practice simple ADC on different ADC Channels
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include <avr/interrupt.h>

ISR (ADC_vect)
{
	PORTD |= (1<<PD2);
	_delay_ms(100);
	PORTD &= ~(1<<PD2);
	_delay_ms(100);
	ADCSRA |= (1<<ADIF); // clearing the flag by writing one to it
}
void adc0_init()
{
	DDRA &= ~(1<<PA0); // we will be using the ADC0 for the test
	ADMUX |= (1<<REFS0)|(1<<ADLAR);
	ADCSRA |= (1<<ADEN) | (1<<ADIE) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
	sei();
}

int read_ADC0()
{
	ADCSRA |= (1<<ADSC);
	//ADMUX = (ADMUX & 0xF0) | 0x00;
	while((ADCSRA & (1<<ADSC)))
	{
		//wait
	}
	int value = (ADCL>>6) | (ADCH<<2); //result is 10 bit we are shifting and ORing to obtain the result
	return value;
}

void uart_init()
{
	DDRD |= (1<<PD1) | (1<<PD2); //UART transmit pin
	DDRD &= ~(1<<PD0); //UART receive pin
	//UCSRA |= (1<<TXC); //simply clearing the transmission complete flag
	UCSRB |= (1<<TXEN) | (1<<RXEN);
	UCSRC |= (1<<URSEL) | (1<<UCSZ0) | (1<<UCSZ1);
	UBRRH &= ~(1<<URSEL);
	UBRRL = 0x33;
}

void uart_transmit(unsigned char data)
{
	while (!(UCSRA & (1<<UDRE)));
	UDR = data;
	_delay_ms(10);
}

void uart_transmit_string(char * str)
{
	while(*str != '\0')
	{
		uart_transmit(*str);
		str++;
	}
}

int main(void)
{
	adc0_init();
	uart_init();
	int readings;
	char readStr[6];
	while (1)
	{
		readings = read_ADC0();
		sprintf(readStr,"%d\n\r",readings);
		uart_transmit_string(readStr);
		_delay_ms(1000);
		
	}
}