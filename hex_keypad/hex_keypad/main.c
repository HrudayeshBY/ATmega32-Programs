//program to interface 4x4 Hex keypad with the Atmega32 microcontroller
//Row scanning method is used, each button has a unique combination, this is used to map the key

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

int button_count = 0;
int secondLine = 0;

void sendCommand(char cmd)
{
	PORTC = cmd;
	PORTD = 0x20;
	_delay_ms(100);
	PORTD = 0x00;
}

void sendData(char data)
{
	PORTC = data;
	PORTD = 0xA0;
	_delay_ms(100);
	PORTD = 0x00;
}

void lcd_init()
{
	sendCommand(0x38);
	sendCommand(0x0E);
	sendCommand(0x80);
	sendCommand(0x01);
}

int keyPad()
{
	char k_in = 0xFF;int key_out = 255;
	
	PORTB = 0xEF; //activating first row
	_delay_us(10);
	k_in = (PINB & 0x0F);
	
	if(k_in == 0x07)
		key_out = 0;
	else if(k_in == 0x0B)
		key_out = 1;
	else if(k_in == 0x0D)
		key_out = 2;
	else if(k_in == 0x0E)
		key_out = 3;
	
	PORTB = 0xDF; //activating second row
	_delay_us(10);
	k_in = (PINB & 0x0F);
	
	if(k_in == 0x07)
	key_out = 4;
	else if(k_in == 0x0B)
	key_out = 5;
	else if(k_in == 0x0D)
	key_out = 6;
	else if(k_in == 0x0E)
	key_out = 7;
	
	PORTB = 0xBF; //activating 3rd row
	_delay_us(10);
	k_in = (PINB & 0x0F);
	
	if(k_in == 0x07)
	key_out = 8;
	else if(k_in == 0x0B)
	key_out = 9;
	else if(k_in == 0x0D)
	key_out = 10;
	else if(k_in == 0x0E)
	key_out = 11;
	
	PORTB = 0x7F; //activating 4th row
	_delay_us(10);
	k_in = (PINB & 0x0F);
	
	if(k_in == 0x07)
	key_out = 12;
	else if(k_in == 0x0B)
	key_out = 13;
	else if(k_in == 0x0D)
	key_out = 14;
	else if(k_in == 0x0E)
	key_out = 15;
	
	
	return key_out;
}
int main(void)
{
	DDRD = 0xE0;DDRC = 0xFF;DDRB = 0xF0;
	PORTD = 0x00;PORTC = 0x00;PORTB = 0x0F;
	int keyValue = 0;
	lcd_init();

    while (1) 
    {
		keyValue = keyPad();
		
		switch(keyValue)
		{
			button_count++;
			if(button_count > 16)
			{
				button_count = 0;
				sendCommand(0xC0);
				
				
			}
				
			case 0:
			sendData('0');
			break;
			
			case 1:
			sendData('1');
			break;
			
			case 2:
			sendData('2');
			break;
			
			case 3:
			sendData('3');
			break;
			
			case 4:
			sendData('4');
			break;
			
			case 5:
			sendData('5');
			break;
			
			case 6:
			sendData('6');
			break;
			
			case 7:
			sendData('7');
			break;
			
			case 8:
			sendData('8');
			break;
			
			case 9:
			sendData('9');
			break;
			
			case 10:
			sendData('A');
			break;
			
			case 11:
			sendData('B');
			break;
			
			case 12:
			sendData('C');
			break;
			
			case 13:
			sendData('D');
			break;
			
			case 14:
			sendData('E');
			break;
			
			case 15:
			sendData('F');
			break;
			
			default:
			break;
			
			_delay_ms(100);
		}
    }
}

