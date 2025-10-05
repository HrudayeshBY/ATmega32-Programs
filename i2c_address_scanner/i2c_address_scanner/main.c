//trying to write an application code for I2C address scanner
//We will send various address by incrementing , we will constantly monitor for the TWSR
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdio.h>

#define WRITE 0
#define READ 1

char uartStr[40] = {'\0'};

void uart_init()
{
	DDRD |= (1<<PD1); //TX pin
	DDRD &= ~(1<<PD0); //RX pin
	UCSRA |= 0x00;
	UCSRB |= (1<<RXEN) | (1<<TXEN);
	UCSRC |= (1<<URSEL) | (1<<UCSZ1) | (1<<UCSZ0);
	UBRRH &= ~(1<<URSEL);
	UBRRL = 0x33;
}

void uart_transmit(char data)
{
	//check if the UDR is empty
	while(!(UCSRA & (1<<UDRE)))
	{
		//wait
	}
	UDR = data;
}

char uart_receive()
{
	while (!(UCSRA & (1<<RXC)))
	{
		//wait
	}
	return UDR;
}

void uart_transmit_str(char *str)
{
	while (*str != '\0')
	{
		uart_transmit(*str);
		str++; //incrementing the pointer
	}
	uart_transmit('\n');
	uart_transmit('\r');
}

void i2c_master_init()
{
	//Don't set the DDRC registers the TWI hardware block will source and sink the pin as and when needed
	TWBR = 0x08; //for 100KHz SCL Frequency
	TWSR &= 0xF8; //making the pre scaler bits 0
	TWCR |= (1<<TWEN);

}

void i2c_start()
{
	TWCR |= (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
}

void i2c_stop()
{
	TWCR |= (1<<TWINT) | (1<<TWSTO) | (1<<TWEN);
}

void i2c_write(uint8_t data)
{
	TWDR = data;
	TWCR |= (1<<TWINT) | (1<<TWEN);
	while (!(TWCR & (1<<TWINT)));//wait till data transfer is complete and flag is set
}

int main(void)
{
	PORTC |= 0xFF; //internal pull up resistor enabled
	uart_init();
	i2c_master_init();
	int flag = 0;
	uint8_t deviceAddress = 0x08;
	
	for (deviceAddress = 0x08;deviceAddress <= 0x77;deviceAddress++)
	{
		i2c_start();
		i2c_write((deviceAddress<<1) | WRITE); //7 bit device address and write bit
		_delay_ms(10);
		if ((TWSR & 0xF8)== 0x18)
		{
			i2c_stop();
			flag = 1;
			sprintf(uartStr,"Device address found is 0x%02X",deviceAddress);
			uart_transmit_str(uartStr);
		}

	}
		
	if (!flag)
	{
		//i2c_stop();
		uart_transmit_str("No I2C device found\n");
	}
	uart_transmit_str("Scanning Complete");
	while (1)
	{

	}
}

