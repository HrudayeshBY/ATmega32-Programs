#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

#define PCF8574_ADDR (0x27 << 1)  // Change if needed after running an I2C scanner

void i2c_master_init()
{
	TWSR = 0x00;     // Prescaler = 1
	TWBR = 0x08;       // SCL = 100kHz @ 8MHz
	TWCR = (1 << TWEN);
}

void i2c_start()
{
	TWCR = (1 << TWSTA) | (1 << TWEN) | (1 << TWINT);
	while (!(TWCR & (1 << TWINT)));  // Wait for completion
}

void i2c_stop()
{
	TWCR = (1 << TWSTO) | (1 << TWINT) | (1 << TWEN);
	while (TWCR & (1 << TWSTO));  // Wait for stop to complete
}

void i2c_write(uint8_t data)
{
	TWDR = data;
	TWCR = (1 << TWINT) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)));  // Wait for completion
}

void i2c_lcd_cmd(uint8_t cmd)
{
	uint8_t high_nibble = (cmd & 0xF0) | 0x08;  // Backlight ON
	uint8_t low_nibble = ((cmd << 4) & 0xF0) | 0x08;

	i2c_start();
	i2c_write(PCF8574_ADDR);
	
	// Send high nibble
	i2c_write(high_nibble | 0x04);  // EN = 1
	_delay_us(100);
	i2c_write(high_nibble & ~0x04); // EN = 0

	// Send low nibble
	i2c_write(low_nibble | 0x04);
	_delay_us(100);
	i2c_write(low_nibble & ~0x04);

	i2c_stop();
}

void i2c_lcd_data(uint8_t data)
{
	uint8_t high_nibble = (data & 0xF0) | 0x09;  // RS = 1, Backlight ON
	uint8_t low_nibble = ((data << 4) & 0xF0) | 0x09;

	i2c_start();
	i2c_write(PCF8574_ADDR);

	// Send high nibble
	i2c_write(high_nibble | 0x04);
	_delay_us(100);
	i2c_write(high_nibble & ~0x04);

	// Send low nibble
	i2c_write(low_nibble | 0x04);
	_delay_us(100);
	i2c_write(low_nibble & ~0x04);

	i2c_stop();
}

void lcd_init()
{
	_delay_ms(50);  // LCD power-up delay

	i2c_lcd_cmd(0x33);  // Initialize in 4-bit mode
	i2c_lcd_cmd(0x32);
	i2c_lcd_cmd(0x28);  // 4-bit mode, 2 lines, 5x7 font
	i2c_lcd_cmd(0x0C);  // Display ON, Cursor OFF
	i2c_lcd_cmd(0x06);  // Entry mode: Move cursor right
	i2c_lcd_cmd(0x01);  // Clear display
	_delay_ms(5);
}

void lcd_print(char *str)
{
	while (*str != '\0')
	{
		i2c_lcd_data(*str);
		str++;
	}
}

int main(void)
{
	i2c_master_init();
	lcd_init();
	lcd_print("Hello Victus");

	while (1);
}
