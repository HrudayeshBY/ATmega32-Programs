//16x2 lcd interfacing in 8 bit and 4 bit mode for practice
//8 bit mode successful

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
void lcd_cmd(char cmd)
{
	PORTD = cmd;
	PORTA = 0x20;
	_delay_ms(10);
	PORTA = 0x00;
}

void lcd_data(char data)
{
	PORTD = data;
	PORTA = 0xA0;
	_delay_ms(10);
	PORTA = 0x80;
}
void lcd_cmd_4bit(char cmd)
{
	char temp = (cmd & 0xF0); // to reattain higher 4 bits
	PORTD = temp;
	PORTA = 0x20;
	_delay_ms(10);
	PORTA = 0x00;
	
	PORTD = ((cmd <<4) & 0xF0); // to obtain lower 4 bits
	PORTA = 0x20;
	_delay_ms(10);
	PORTA = 0x00;
}
void lcd_data_4bit(char data)
{
	char temp = (data & 0xF0); // to reattain higher 4 bits
	PORTD = temp;
	PORTA = 0xA0;
	_delay_ms(10);
	PORTA = 0x80;
	
	PORTD = ((data <<4) & 0xF0); // to obtain lower 4 bits
	PORTA = 0xA0;
	_delay_ms(10);
	PORTA = 0x80;
}
void lcd_print(char *str)
{
	while(*str != '\0')
	{
		lcd_data(*str);
		str++;
	}
}

void lcd_print_4bit(char *str)
{	
	while(*str != '\0')
	{
		lcd_data_4bit(*str);
		str++;
	}
}
void lcd_init()
{
	DDRD |= 0xFF; // for connecting the data pins to LCD
	DDRA |= 0xE0; //connecting the controller pins
	lcd_cmd(0x38);
	lcd_cmd(0x0E);
	lcd_cmd(0x01);
	lcd_cmd(0x80);
}

void lcd_4bit_init()
{
	DDRD |= 0xF0; // for connecting the data pins to LCD
	DDRA |= 0xE0; //connecting the controller pins
	lcd_cmd_4bit(0x02);
	lcd_cmd_4bit(0x28);
	lcd_cmd_4bit(0x0E);	
	lcd_cmd_4bit(0x01);	
	lcd_cmd_4bit(0x80);
}
int main(void)
{
	//lcd_init();
	//lcd_data('Hru');
	//lcd_print("Hrudayesh");
	lcd_4bit_init();
	lcd_data_4bit('H');
	//lcd_print_4bit("4 bit mode");
	while (1)
	{
	}
}