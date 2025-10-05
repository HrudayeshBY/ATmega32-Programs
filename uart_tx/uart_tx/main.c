//Program to transmit the data to the serial monitor on PC
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

void transmit(char* data)
{
	int n = 0;
	while(data[n] != '\0')
	{
		UDR = data[n];
		while((UCSRA & 0x40) == 0)
		{
			//do nothing
		}
		_delay_ms(10);
		n++;
	}
	
}
int main(void)
{
    //USART pins are RXD and TXD on port D
	DDRD = 0x02;PORTD = 0x00;
	UCSRA = 0x00;UCSRB = 0x18;UCSRC = 0x06;
	//setting baud rate as 9600
	UBRRH = 0x00;UBRRL = 0x33;
	
	char messaage[] = "Hi PC, I am ATmega32 ";
	transmit(messaage);
	transmit("h");
    while (1) 
    {
		//transmit(messaage);
		//_delay_ms(1000);
    }
}

