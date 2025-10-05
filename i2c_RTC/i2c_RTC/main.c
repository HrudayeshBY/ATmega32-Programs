#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

#define DS1307_ADDR 0x68
#define DS1307_CLC_REG 0x00

char tx_buff[7] = '\0';
char str[60];
int write = 0;
int read = 1;

void uart_init()
{
	DDRD |= (1<<PD1);
	DDRD &= ~(1<<PD0);
	UCSRA |= 0x00;
	UCSRB |= (1<<RXEN) | (1<<TXEN);
	UCSRC |= (1<<URSEL) | (1<<UCSZ1) | (1<<UCSZ0);
	UBRRH = 0x00;
	UBRRL = 0x33;
}

void uart_transmit(char data)
{
	UDR = data;
	while(!(UCSRA & (1<<UDRE)));
}

char uart_receive()
{
	while(!(UCSRA & (1<<RXC)));
	return UDR;
}
void uart_println(char * str)
{
	while(*str != '\0')
	{
		uart_transmit(*str);
		str++;
	}
	uart_transmit('\n');
	uart_transmit('\r');
}

void i2c_master_init()
{
	TWSR = 0x00;
	TWCR |= (1<<TWEN) | (1<<TWEA) | (1<<TWINT);
	TWBR = 0x08;
}

void i2c_start()
{
	TWCR |= (1<<TWINT) | (1<<TWSTA);
	while(!(TWCR & (1<<TWINT)));
}

void i2c_stop()
{
	TWCR |= (1<<TWINT) | (1<<TWSTO);
	while(!(TWCR & (1<<TWINT)));
}

uint8_t i2c_read()
{
	while(!(TWCR & (1<<TWINT)));
	return TWDR;
}

void i2c_write(char data)
{
	TWDR = data;
	TWCR |= (1<<TWEN) | (1<<TWINT);
	while(!(TWCR & (1<<TWINT)));
}

void i2c_readMultiple(int n)
{
	int i = 0;
	uint8_t data;
	while(i < n)
	{
		if(i < (n-1))
		{
			TWCR | = (1<<TWINT) | (1<<TWEN) | (1<<TWEA); 
			while(!(TWCR & (1<<TWINT)));
			data = TWDR;
			tx_buff[i] = data;
		}
		
		else
		{
			TWCR | = (1<<TWINT) | (1<<TWEN);
			while(!(TWCR & (1<<TWINT)));
			data = TWDR;
			tx_buff[i] = data;	
		}
		i++;
		
	}
}


void rtc_setup(char sec, char min, char hrs, char day, char week, char month, char year)
{
	i2c_start();
	i2c_write((DS1307_ADDR << 1) + 0);
	i2c_write(DS1307_CLC_REG);
	i2c_write(sec);
	i2c_write(min);
	i2c_write(hrs);
	i2c_write(day);
	i2c_write(week);
	i2c_write(month);
	i2c_write(year);
	i2c_stop();
}

void rtcGetData()
{
	
}

int main(void)
{
	uart_init();
	i2c_master_init();
	
    while (1) 
    {

    }
}

