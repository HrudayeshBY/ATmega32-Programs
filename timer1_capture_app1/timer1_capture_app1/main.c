//Determining time between 2 successive button presses
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>

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
	DDRD &= ~(1<<PD6); // Input Capture Pin
	TCCR1A &= ~(TCCR1A);
	TCCR1B = 0x43;
	char buffer[35];
	while (1)
	{
		unsigned int t1 = 0, t2 = 0, Time = 0,overflow_count = 0;
		float actual_time = 0.0;
		
		while(!(TIFR & (1<<ICF1)))
		{
			//wait
		}
		t1 = ICR1;
		TIFR |= (1<<ICF1);
		
		while(!(TIFR & (1<<ICF1)))
		{
			if(TCNT1 >= 65535)
			{
				overflow_count++;
			}
		}
		t2 = ICR1;
		TIFR |= (1<<ICF1);
		
		Time = (65535 - t1) + ((overflow_count - 1) * 65535) + t2;
		actual_time =  0.000008 * (float)Time/5.2;
		sprintf(buffer,"The time recorded is %f\n",actual_time);
		uart_println(buffer);
		overflow_count = 0;
		                                                                                                          
	
	}
}

