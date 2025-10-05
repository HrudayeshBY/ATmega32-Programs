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
	char buffer[40];
	DDRD &= ~(1<<PD6);
	TCCR1A &= ~(TCCR1A);
	uint16_t a,b,c,period,on_time;
	float frequency = 0.0, duty_cycle = 0.0;
	while (1)
	{
		TCNT1 = 0x00;
		TCCR1B = 0x41;
		TIFR |= (1<<ICF1);
		while(!(TIFR & (1<<ICF1)))
		{
			//wait
		}
		a = ICR1;
		TIFR |= (1<<ICF1); // clear the flag
		
		
		TCCR1B = 0x01;
		while(!(TIFR & (1<<ICF1)))
		{
			//wait
		}
		b = ICR1;
		TIFR |= (1<<ICF1); // clear the flag
		
		TCCR1B = 0x41;
		while(!(TIFR & (1<<ICF1)))
		{
			//wait
		}
		c = ICR1;
		TIFR |= (1<<ICF1); // clear the flag
		
		if((a<b) && (b<c))
		{
			on_time = b - a;
			period = c - a;
			frequency = (float)(F_CPU/period) / 0.972;
			duty_cycle = on_time/period * 100;
			sprintf(buffer,"Frequency = %f and Duty Cycle = %f",frequency,duty_cycle);
			uart_println(buffer);
			//memset(buffer,'0', 40* sizeof(char));
			_delay_ms(2000);
		}
	}
}

