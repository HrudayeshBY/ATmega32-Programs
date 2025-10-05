// Interfacing 4x4 hex keypad using adc on atmega32
// Concept of voltage divider is used to get various voltage levels on each key press
// we will interface resistor network and read adc value for every key press an later hard code the range
#define F_CPU 8000000UL
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

#define s1 (value >= 60) && (value <=62)
#define s2 (value >= 87) && (value <=88)
#define s3 (value >= 147) && (value <=149)
#define s4 (value >= 489) && (value <=495)
#define s5 (value >= 65) && (value <=67)
#define s6 (value >= 95) && (value <=97)
#define s7 (value >= 178) && (value <=180)
#define s8 (value >= 1015) && (value <=1017)
#define s9 (value >= 56) && (value <=59)
#define s10 (value >= 79) && (value <=83)
#define s11 (value >= 129) && (value <=132)
#define s12 (value >= 336) && (value <=340)
#define s13 (value >= 56) && (value <=59)
#define s14 (value >= 78) && (value <=80)
#define s15 (value >= 119) && (value <=123)
#define s16 (value >= 313) && (value <=316)

int value = 0;
void uart_init()
{
	DDRD |= (1<<PD1); //set Tx pin
	DDRD &= ~(1<<PD0); //set Rx pin
	PORTD &= ~(1<<PD0) & ~(1<<PD1);
	UCSRA = 0x00;UCSRB = 0x18;UCSRC = 0x06;
	UBRRH = 0x00;UBRRL = 0x33;
}

void transmit(char data)
{
	UDR = data;
	while((UCSRA & (1<<TXC)) == 0)
	{
		//wait
	}
	_delay_ms(50);
}
void adc0_init()
{
	DDRA = 0x00;
	PORTA = 0x00;
	ADMUX = 0x60;
	ADCSRA = 0x87;
}

int read_adc0()
{
	ADCSRA |= (1<<ADSC); //starting the conversion
	int data = (ADCL >> 6) | (ADCH << 2);
	return data;
}
void serial_println(char* str)
{
	short int n = 0;
	while(str[n] != '\0')
	{
		transmit(str[n]);
		n++;
	}
	transmit('\n');
	transmit('\r');
	
}

void keyPad()
{
	value = read_adc0();
	if(s1)
		serial_println("0\r\n");
	else if(s2)
		serial_println("1\r\n");
	else if(s3)
		serial_println("2\r\n");
	else if(s4)
		serial_println("3\r\n");
	else if(s5)
		serial_println("4\r\n");
	else if(s6)
		serial_println("5\r\n");
	else if(s7)
		serial_println("6\r\n");
	else if(s8)
		serial_println("7\r\n");
	else if(s9)
		serial_println("8\r\n");
	else if(s10)
		serial_println("9\r\n");
	else if(s11)
		serial_println("A\r\n");
	else if(s12)
		serial_println("B\r\n");
	else if(s13)
		serial_println("C\r\n");
	else if(s14)
		serial_println("D\r\n");
	else if(s15)
		serial_println("E\r\n");
	else if(s16)
		serial_println("F\r\n");
	else
		serial_println("None\r\n");
}
int main(void)
{
	uart_init();
	adc0_init();
	
	while (1)
	{
		keyPad();
		_delay_ms(1000);
	}
}

