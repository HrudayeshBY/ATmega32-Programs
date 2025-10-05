//ATmega 32 has 8 ADC Channels, only one channel can be used at a time
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

int readADC0()
{
	int raw = 0;
	DDRA = 0x00; PORTA = 0x00;
	ADMUX = 0x60;ADCSRA = 0x87;
	//start conversion
	ADCSRA |= (1<<ADSC);
	while((ADCSRA & 0x40)!= 0)
	{
		raw = (ADCL>>6) | (ADCH << 2);
	}
	 return raw;
}

int readADC1()
{
	int raw = 0;
	DDRA = 0x00; PORTA = 0x00;
	ADMUX = 0x61;ADCSRA = 0x87;
	//start conversion
	ADCSRA |= (1<<ADSC);
	while((ADCSRA & 0x40)!= 0)
	{
		raw = (ADCL>>6) | (ADCH << 2);
	}
	return raw;
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
	uart_init();// initializing the UART
	char ADC0_Value[30];
	char ADC1_Value[30];
	int adc0_reading = 0;
	int adc1_reading = 0;
	while (1)
	{
		adc0_reading = readADC0();
		sprintf(ADC0_Value,"The Value of ADC 0 is : %f ",(adc0_reading / 1023.0) * 5.0);
		
		adc1_reading = readADC1();
		sprintf(ADC1_Value,"The Value of ADC 1 is : %f ",(adc1_reading / 1023.0) * 5.0);
		
		sendString(ADC0_Value);
		transmit('\n');
		transmit('\r');
		sendString(ADC1_Value);
		transmit('\n');
		transmit('\r');
		
		_delay_ms(1000);
	}
}



