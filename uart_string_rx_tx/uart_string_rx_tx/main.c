//Program to receive the data from the PC and transmit itback using UART protocol
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

void transmit(char data)
{
	UDR = data;
	while((UCSRA & 0x40) == 0)
	{
		//wait
	}
	_delay_ms(100);
}

char receive()
{
	while((UCSRA & 0x80) == 0)
	{
		//wait
	}
	char receivedData = UDR;
	return receivedData;
}

void uart_init()
{
	DDRD = 0x20;
	PORTD = 0x00;
	UCSRA = 0x00; UCSRB = 0x18; UCSRC = 0x06;
	UBRRH = 0x00; UBRRL = 0x33; //sets baud rate as 9600
}
int main(void)
{
	char incomingString[100];
	uart_init();
	int i = 0;
	char data;
    
    while (1) 
    {
		do 
		{
			data = receive();
			if(data != '\r')
			{
				incomingString[i] = data;
			}
			else
			{
				incomingString[i] = '\0';
			}
			i++;
			
		} while (data != '\r');
		
		i = 0;
		while(incomingString[i] != '\0')
		{
			transmit(incomingString[i]);
			_delay_ms(100);
			i++;
		}
		
		for(int j =0;j<100;j++)
		{
			incomingString[i] = '\0';
		}
    }
}

