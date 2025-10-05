//Program to  demonstarte the UART based interrupts
#define F_CPU 8000000UL //speed of CPU clock
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

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
	_delay_ms(100);
}

void uart_init()
{
	DDRD |= 0x02;
	PORTD = 0x00;
	UCSRA = 0x00; UCSRB = 0xD8;// the TXCIE and RXCIE made is set
	UCSRC = 0x06;
	UBRRH = 0x00; UBRRL = 0x33;
}

void lcd_data(char data)
{
	PORTC = data;
	PORTD = 0x20;
	_delay_ms(100);
	PORTD = 0x00;
}

void lcd_command(char cmd)
{
	PORTC = cmd;
	PORTD = 0xA0;
	_delay_ms(100);
	PORTD = 0x00;
}

void lcd_init()
{
	DDRD |= 0xE0;
	DDRC = 0xFF;
	lcd_command(0x38);
	lcd_command(0x0E);
	lcd_command(0x01);
	lcd_command(0x80);
}

void lcd_clear()
{
	lcd_command(0x01);
	lcd_command(0x80);
}

void lcd_display(char* msg)
{
	int i = 0;
	while(msg[i] != '\0')
	{
		lcd_data(msg[i]);
		i++;
		_delay_ms(100);
	}
	
}

ISR(USART_RXC_vect)
{
	lcd_clear();
	lcd_display("Rx Complete");
	_delay_ms(1000);
}

ISR(USART_TXC_vect)
{
	lcd_clear();
	lcd_display("Tx Complete");
	_delay_ms(1000);

}
int main(void)
{
	char data;
	//PORTD = 0x00; PORTC = 0x00;
	lcd_init();
	uart_init();
	sei(); //global interrupt enable
    while (1) 
    {
		data = receiveData();
		_delay_ms(1000);
		transmitData(data);
		_delay_ms(1000);
    }
}

