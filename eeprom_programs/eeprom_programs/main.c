// Program to use the EEPROM api's in the avr/eeprom.h
//also in this i tried writing few lcd functions
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/eeprom.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sendCommand(char cmd)
{
	PORTC = cmd;
	PORTD = 0x20;
	_delay_ms(10);
	PORTD = 0x00;
}

void sendData(char data)
{
	PORTC = data;
	PORTD = 0xA0;
	_delay_ms(10);
	PORTD = 0x00;
}

void lcd_init()
{
	DDRC |= 0xFF; PORTC = 0x00;
	DDRD |= 0xE0; PORTD |= 0x00;
	sendCommand(0x38);
	sendCommand(0x0E);
	sendCommand(0x01);
	sendCommand(0x80);
}

void lcd_print(char* str)
{
	short int n = 0;
	while(str[n] != '\0')
	{
		sendData(str[n]);
		n++;
	}
}
void lcd_setCursor(int col, int row)
{
	if(row == 0)
	{
		sendCommand(0x80);
	}
	
	else
	{
		sendCommand(0xC0);
	}
	
	for(int i=0;i<col;col++)
	{
		sendCommand(0x06);
	}
}

void lcd_clear()
{
	sendCommand(0x01);
}
//int main(void)
//{
//
	//lcd_init();
	//uint8_t readValue = 0;
	//_delay_ms(1000);
	//
	//eeprom_busy_wait();
	//
	//eeprom_write_byte( (uint8_t *)0, (uint8_t)72);
	//eeprom_write_byte( (uint8_t *)1, (uint8_t)89);
	//eeprom_write_byte( (uint8_t *)2, (uint8_t)66);
	//readValue = eeprom_read_byte((const uint8_t*)2); //it is a good practice the address as const to avoid any accidental access to any other address
	//sendData(readValue);
	//readValue = eeprom_read_byte((const uint8_t*)1);
	//sendData(readValue);
	//readValue = eeprom_read_byte((const uint8_t*)0);
	//sendData(readValue);
	//_delay_ms(1000);
    //while (1) 
    //{
		//
    //}
//}

//int main(void)
//{
	//lcd_init();
	//char writtenString[16] = "Hrudayesh B Y";
	//char readString[16];
	//memset(readString, '\0',16 * sizeof(char));
	//eeprom_busy_wait();
	//
	//eeprom_write_block((const void*)writtenString,(void*)0,strlen(writtenString));
	//eeprom_read_block(readString,(void*)0,strlen(writtenString));
	//
	//lcd_print(readString);
//
	//while(1);
//}

int main(void)
{
	lcd_init();
	float number = 0.0;
	char fltString[6];
	eeprom_busy_wait();
	eeprom_write_float((float* )17,3.1415);
	number = eeprom_read_float((const float*)17);
	dtostrf((double)number,3,3,fltString);
	lcd_print(fltString);
	while(1);
	
}

