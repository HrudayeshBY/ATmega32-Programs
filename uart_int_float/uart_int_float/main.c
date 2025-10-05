//Program to print integer and floating point numbers
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h> //we are using printf function

void transmitData(char data)
{
	UDR = data;
	while((UCSRA & 0x40) == 0)
	{
		//wait
	}
	_delay_ms(100);
}

char receiveData()
{
	while((UCSRA & 0x80) == 0)
	{
		//wait
	}
	char incomingData = UDR;
	return incomingData;
}

void uart_init()
{
	DDRD = 0x02;
	PORTD = 0x00;
	UCSRA = 0x00; UCSRB = 0x18; UCSRC = 0x06;
	UBRRH = 0x00; UBRRL = 0x33;
}
int main(void)
{
	uart_init();
	int counter = 0;
	int integer = 17;
	float floatNumber = 3.14;
	char intString[25];
	char floatString[25];
	sprintf(intString,"The integer is %d\n\r", integer);
	sprintf(floatString,"The float number is %f\n\r", floatNumber);
	
    while (1) 
    {
		while((intString[counter] != '\0'))
		{
			transmitData(intString[counter]);
			counter++;
			
		}
		_delay_ms(2500);
		counter = 0;
		while((floatString[counter] != '\0'))
		{
			transmitData(floatString[counter]);
			counter++;
			
		}
		_delay_ms(2500);
		
		counter = 0;
    }
}

