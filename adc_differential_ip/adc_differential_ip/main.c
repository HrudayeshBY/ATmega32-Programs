//ATmega 32 has 8 ADC Channels, only one channel can be used at a time
// For differential input, one channel is positive the other is negative
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

int adc_differential_mode()
{
	int raw_value = 0;
	DDRA = 0x00;PORTA = 0x00;
	ADMUX = 0x68;ADCSRA = 0x87;
	ADCSRA |= (1<<ADSC);
	while((ADCSRA & (1<<ADSC)) != 0)
	{
		raw_value = (ADCL >> 6) | (ADCH << 2);
	}
	return raw_value;
}
int main(void)
{
	uart_init();// initializing the UART
	int value = 0;
	char differentialValue[30];
	
	while(1)
	{
		value = adc_differential_mode();
		sprintf(differentialValue,"The Differential Value is %d ",value);
		sendString(differentialValue);
		transmit('\n');
		transmit('\r');
		
		_delay_ms(1000);
	}

}




