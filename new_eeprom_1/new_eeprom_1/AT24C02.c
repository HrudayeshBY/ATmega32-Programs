/*
 * AT24C02.c
 *
 * Created: 18-03-2025 02:03:00 AM
 *  Author: hp
 */ 
#include "AT24C02.h"

unsigned char eeprom_buf[60] = {'\0'};
char w = 0x00, r = 0x01;
char str1[60] = {'\0'};

//UART functions
void uart_init()
{
	UCSRA = 0x00;
	UCSRB = 0x18;
	UCSRC = 0x06;
	UBRRH = 0x00; UBRRL = 0x33;

}

void transmit(char a)
{
	UDR = a;
	while((UCSRA & 0x40) == 0);
	_delay_ms(60);
}

void uart_send_str(char *str)
{
	while((*str) != '\0')
	{
		transmit(*str);
		str++;
	}
}


//I2C functions
void i2c_init_master()
{
	TWSR &= 0xF8;
	TWBR = 0x07;
	TWCR |= (1<<2);
}

void i2c_start()
{
	TWCR = (1<<7) | (1<<5) | (1<<2);
	while((TWCR & (1<<7)) == 0);
}

void i2c_stop()
{
	TWCR = (1<<4) | (1<<2) | (1<<7);
}

void i2c_write(unsigned char data)
{
	TWDR = data;
	TWCR = (1<<7) | (1<<2);
	while((TWCR & (1<<7)) == 0);
}

unsigned char i2c_read()
{
	unsigned char z = '\0';
	TWCR = (1<<7) | (1<<2);
	while((TWCR & (1<<7)) == 0);
	z = TWDR;
	return z;
}

void i2c_read_multiple(int n)
{
	int x;
	for(x = 0; x < n;x++)
	{
		if(x < (n-1))
		{
			TWCR = (1 << 7) | (1<<6) | (1<<2);
			while((TWCR & (1<<7)) == 0);
			eeprom_buf[x] = TWDR;
		}

		else
		{
			TWCR = (1<<7) | (1<<2);
			while((TWCR & (1<<7)) == 0);
			eeprom_buf[x] = TWDR;
		}
	}
}

//At24C02 functions
void at24c02_write_byte(unsigned char mem_addr, unsigned char data)
{
	i2c_start();
	i2c_write((EEPROM_ADDR << 1) + w);
	i2c_write(mem_addr);
	i2c_write(data);
	i2c_stop();
}

unsigned char at24c02_read_byte(unsigned char meme_addr)
{
	unsigned char k = '\0';
	i2c_start();
	i2c_write((EEPROM_ADDR << 1) + w);
	i2c_write(meme_addr);
	i2c_stop();
	i2c_start();
	i2c_write((EEPROM_ADDR << 1) + r);
	k = i2c_read();
	return k;
}

void at24c02_write_sequential(unsigned char mem_addr, unsigned char str[])
{
	int i = 0;
	while(str[i] != '\0')
	{
		i2c_start();
		i2c_write((EEPROM_ADDR << 1) + w);
		i2c_write(mem_addr);
		i2c_write(str[i]);
		i2c_stop();
		i++;
		mem_addr += 0x01;
		_delay_ms(100);
	}
}

void at24c02_read_sequential(unsigned char mem_addr, int n)
{
	int i;
	i2c_start();
	i2c_write((EEPROM_ADDR << 1) + w);
	i2c_write(mem_addr);
	i2c_stop();
	i2c_start();
	i2c_write((EEPROM_ADDR << 1) + r);
	i2c_read_multiple(n);
	i2c_stop();
	uart_send_str("Sequential Data Read: ");
	sprintf(str1, "%s", eeprom_buf);
	uart_send_str(str1);
	for(i = 0; i < 60; i++)
	{
		str1[i] = '\0';
		eeprom_buf[i] = '\0';
	}
}

void at24c02_erase()
{
	int u = 0;
	unsigned char mem_addr = 0x00;
	do
	{
		u++;
		at24c02_write_byte(mem_addr, 0xFF);
		mem_addr += 0x01;
		transmit('.');
		if(!(u % 32))
		{
			uart_send_str("\n\r");
		}
		_delay_ms(100);
	}
	while(mem_addr != 0xFF);
}

void at24c02_read()
{
	int u = 0;
	unsigned char mem_addr = 0x00, p = '\0';
	do
	{
		u++;
		p = at24c02_read_byte(mem_addr);
		sprintf(str1, "%02X", p);
		uart_send_str(str1);
		if((u%32) == 0)
		{
			uart_send_str("\n\r");
		}

		for(int i = 0; i < 60; i++)
		{
			str1[i] = '\0';
		}
		mem_addr += 0x01;
		_delay_ms(100);
	}
	while (mem_addr != 0xFF);
	
}