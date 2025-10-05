// The PCF857A is a remote GPIO expander,
//we are sending the data/cmd to lcd by using the 4 bit mode
//We must send upper nibble and lower nibble every time we send a data/ cmd

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

#define PCF857A_addr (0x27<<1)

#define BLK 3
#define EN 2
#define RW 1
#define RS 0

void i2c_master_init()
{
	TWSR &= (0xF8); //the value of the TWSR bits is retained and only the TWPS bits are made zero
	TWCR |= (1<<TWEN); //enabling the I2C
	TWBR = 0x08; //calculated for 100Khz
}

void i2c_start()
{
	TWCR |= (1<<TWINT) | (1<<TWEN) | (1<<TWSTA); //TWEN bit should be high every time we make a operation like start, stop etc
	while(!(TWCR & (1<<TWINT)))
	{
		//wait
	}
}

void i2c_stop()
{
	TWCR |= (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
}

void i2c_write(char data)
{
	TWDR = data;
	TWCR |= (1<<TWINT) | (1<<TWEN);
	while(!(TWCR & (1<<TWINT)))
	{
		//wait
	}
}
void i2c_lcd_data(char data)
{
	char temp = (data & 0xF0); //retain the upper 4 bits
	temp |= (1<<BLK) | (1<<EN) | (1<<RS);
	i2c_start();
	
	i2c_write(PCF857A_addr);
	i2c_write(temp);
	_delay_us(100); //min delay for the data to be latched
	temp &= ~(1<<EN);
	i2c_write(temp);
	_delay_us(100); //min delay for the data to be latched
	//i2c_stop();
	
	temp = ((data <<4) & 0xF0); //retain the lower 4 bits
	temp |= (1<<BLK) | (1<<EN) | (1<<RS);
	//i2c_start();
	//i2c_write(PCF857A_addr);
	i2c_write(temp);
	_delay_us(100); //min delay for the data to be latched
	temp &= ~(1<<EN);
	i2c_write(temp);
	_delay_us(100); //min delay for the data to be latched
	
	i2c_stop();
	
}

void i2c_lcd_cmd(char cmd)
{
	char temp = (cmd & 0xF0); //retain the upper 4 bits
	temp |= (1<<BLK) | (1<<EN);
	
	i2c_start();
	
	i2c_write(PCF857A_addr);
	i2c_write(temp);
	_delay_us(100); //min delay for the data to be latched
	temp &= ~(1<<EN);
	i2c_write(temp);
	_delay_us(100); //min delay for the data to be latched

	temp = ((cmd <<4) & 0xF0); //retain the lower 4 bits
	temp |= (1<<BLK) | (1<<EN);
	i2c_write(temp);
	_delay_us(100); //min delay for the data to be latched
	temp &= ~(1<<EN);
	i2c_write(temp);
	_delay_us(100); //min delay for the data to be latched
	i2c_stop();
}

void i2c_lcd_init()
{
	i2c_lcd_cmd(0x02);
	i2c_lcd_cmd(0x28);
	i2c_lcd_cmd(0x0E);
	i2c_lcd_cmd(0x01);
	i2c_lcd_cmd(0x80);
}
int main(void)
{
	i2c_master_init();
	i2c_lcd_init();
	_delay_ms(100);
	i2c_lcd_data('H');
	while (1)
	{
	}
}