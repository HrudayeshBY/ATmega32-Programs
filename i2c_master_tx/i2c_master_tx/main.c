//Trying to communiate between ATmega32 master and Arduino UNO I2C Slave
#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define DEVICE_ADDR 0x17
#define WRITE 0
#define READ 1

void i2c_master_init()
{
	TWSR &= 0xF8; //retaining the status register values and setting prescaler to 1
	TWBR = 0x08;
	TWCR |= (1<<TWEN);
}

void i2c_start()
{
	TWCR |= (1<<TWINT) | (1<<TWSTA) | (1<<TWEN) | (1<<TWIE);
	while ( !(TWCR & (1<<TWINT)));
}

void i2c_stop()
{
	TWCR |= (1<<TWINT) | (1<<TWSTO) | (1<<TWEN);
}

void i2c_write(uint8_t data)
{
	TWDR = data;
	TWCR |= (1<<TWINT) | (1<<TWEN);
	while ( !(TWCR & (1<<TWINT)));
}

uint8_t i2c_read_ack()
{
	TWCR |= (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
	while ( !(TWCR & (1<<TWINT))); // wait for data to be received
	return TWDR;
}

uint8_t i2c_read_nack()
{
	TWCR |= (1<<TWINT) | (1<<TWEN);
	while ( !(TWCR & (1<<TWINT))); // wait for data to be received
	return TWDR;
}

void gpio_init()
{
	DDRD &= ~(1<<PD0); //making PD0 as input
	PORTD = 0xFF; //enabling the pull up resistor
	DDRB |= (1<<PB7);
}
int main(void)
{
	uint8_t status;
	i2c_master_init();
    while (1) 
    {
		i2c_start();
		i2c_write((DEVICE_ADDR <<1) | WRITE);
		status = (TWSR & 0xF8);
		if(status == 0x18)
		{
			PORTD ^= (1<<PD7);
		}
		i2c_write(0xFF);
		i2c_stop();
		_delay_ms(1000);
	
    }
}

