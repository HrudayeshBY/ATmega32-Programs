// Interfacing DS1307 RTC Module with AVR
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

// ------------------------ DS1307 SETTINGS ------------------------
#define DS1307_ADDR 0x68
#define BASE_ADDR 0x00
#define WRITE 0
#define READ 1

char timeStr[7] = {0};
char time[64] = {0};

// ------------------------ UART FUNCTIONS ------------------------
void uart_init()
{
	DDRD |= (1 << PD1);   // TX output
	DDRD &= ~(1 << PD0);  // RX input
	UCSRA = 0x00;
	UCSRB = (1 << RXEN) | (1 << TXEN);
	UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0); // 8-bit, async

	UBRRH = 0;
	UBRRL = 51; // Baud rate 9600 @ 8MHz
}

void uart_transmit(char data)
{
	while (!(UCSRA & (1 << UDRE)));
	UDR = data;
}

void uart_transmit_str(char *str)
{
	while (*str)
	{
		uart_transmit(*str++);
	}
	uart_transmit('\n');
	uart_transmit('\r');
}

// ------------------------ I2C FUNCTIONS ------------------------
void i2c_master_init()
{
	DDRC |= (1 << PC0) | (1 << PC1); // SCL and SDA as output
	TWBR = 0x08;     // 100kHz SCL
	TWSR &= 0xF8;    // Prescaler = 1
	TWCR = (1 << TWEN);
}

void i2c_start()
{
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)));
}

void i2c_stop()
{
	TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

void i2c_write(uint8_t data)
{
	TWDR = data;
	TWCR = (1 << TWINT) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)));
}

uint8_t i2c_read_ack()
{
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
	while (!(TWCR & (1 << TWINT)));
	return TWDR;
}

uint8_t i2c_read_nack()
{
	TWCR = (1 << TWINT) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)));
	return TWDR;
}

// ------------------------ RTC FUNCTIONS ------------------------
uint8_t bcd_to_decimal(uint8_t bcd)
{
	return ((bcd >> 4) * 10) + (bcd & 0x0F);
}

void rtc_init(uint8_t sec, uint8_t min, uint8_t hr, uint8_t day, uint8_t date, uint8_t month, uint8_t year)
{
	i2c_start();
	i2c_write((DS1307_ADDR << 1) | WRITE);
	i2c_write(BASE_ADDR);
	i2c_write(sec);   // Seconds
	i2c_write(min);   // Minutes
	i2c_write(hr);    // Hours
	i2c_write(day);   // Day of week
	i2c_write(date);  // Date
	i2c_write(month); // Month
	i2c_write(year);  // Year
	i2c_stop();
}

void get_time()
{
	i2c_start();
	i2c_write((DS1307_ADDR << 1) | WRITE);
	i2c_write(BASE_ADDR);
	i2c_start(); // repeated start
	i2c_write((DS1307_ADDR << 1) | READ);

	for (int i = 0; i < 7; i++)
	{
		if (i < 6)
		timeStr[i] = i2c_read_ack();
		else
		timeStr[i] = i2c_read_nack();
	}
	i2c_stop();

	sprintf(time, "%02d:%02d:%02d %02d/%02d/20%02d (Day %d)",
	bcd_to_decimal(timeStr[2]),  // Hours
	bcd_to_decimal(timeStr[1]),  // Minutes
	bcd_to_decimal(timeStr[0]),  // Seconds
	bcd_to_decimal(timeStr[4]),  // Date
	bcd_to_decimal(timeStr[5]),  // Month
	bcd_to_decimal(timeStr[6]),  // Year
	bcd_to_decimal(timeStr[3])   // Day of week
	);

	uart_transmit_str(time);
}

// ------------------------ MAIN ------------------------
int main(void)
{
	uart_init();
	i2c_master_init();

	// Set initial time only once if needed
	rtc_init(0x00, 0x59, 0x23, 0x01, 0x31, 0x12, 0x24); // 23:59:00, 31 Dec 2024
	_delay_ms(200); // Wait for RTC to settle

	while (1)
	{
		get_time();
		_delay_ms(1000);
	}
}
