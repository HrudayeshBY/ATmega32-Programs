//Testing the ADC on atmega32
//Printing value on the serial monitor

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

void uart_init()
{
	DDRD |= (1<<PD1); //enabling the Tx pin
	DDRD |= ~(1<<PD0);//enabling the Rx pin
	PORTD = 0x00;
	UCSRA = 0x00;UCSRB = 0x18;UCSRC = 0x06;
	UBRRH = 0x00;UBRRL = 0x33;
}
void ADC0_init()
{
	DDRA = 0x00;
	PORTA = 0x00;
	ADMUX = 0x60;
	ADCSRA = 0x87;
}
void transmit(char data)
{
	UDR = data;
	while((UCSRA & 0x40) == 0)
	{
		//wait
	}
	_delay_ms(10);
}

void sendString(char *str)
{
	int i = 0;
	while(str[i] != '\0')
	{
		transmit(str[i]);
		i++;
	}
}
int main(void)
{
   uart_init();// initializing the uart
   ADC0_init(); // ADC 0 initialization
   char text[] = "ADC Value: ";
   char value[5];
   int adc_value = 0;
    while (1) 
    {
		ADCSRA |= (1<<ADSC); //starting conversion, it will be cleared after conversion
		while((ADCSRA & 0x40) != 0)
		{
			adc_value = (ADCL >> 6) | (ADCH << 2);
		}
		sprintf(value,"%d",adc_value);
		sendString(text);
		sendString(value);
		transmit('\n');
		transmit('\r');

		_delay_ms(1000);
    }
}

