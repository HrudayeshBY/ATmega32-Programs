// program to tet the ADC interrupts, the Adc isr is called when the convesion is complete
// The ISR name is ADC_vect

#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int value = 0; //making the value variable global so it can be accessed by the ISR

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
	sendCommand(0x38);
	sendCommand(0x0E);
	sendCommand(0x01);
	sendCommand(0x80);
}

void lcd_print(char* str)
{
	short int i = 0;
	while(str[i] != '\0')
	{
		sendData(str[i]);
		i++;
	}
	
}

void adc0_init()
{
	DDRA = 0x00;
	PORTA = 0x00;
	ADMUX = 0x60; //adc0 is initialized
	ADCSRA = 0xC8; // adc enabled along with adc interrupt
	
}

int read_adc0()
{
	ADCSRA |=(1<<ADSC); //start conversion
	int result = (ADCL >> 6) | (ADCH << 2);
	return result;
}
void lcd_clear()
{
	sendCommand(0x01);
	sendCommand(0x80);
}

ISR(ADC_vect)
{
	PORTD |= (1<<PD0);
	_delay_ms(300);
	PORTD &= ~(1<<PD0);
	_delay_ms(300);

				
	sendData((value / 1000) + '0');
	sendData((value % 1000)/100 + '0');
	sendData(((value % 100)/10) + '0');
	sendData(((value % 1000)) % 10 + '0');
	_delay_ms(1000);
	sendCommand(0xC0);
	
	ADCSRA &= ~(1<<ADIF); // clearing adc interrupt flag which was set by the adc interrupt
}
int main(void)
{
	sei();// global interrupt enable
	DDRC = 0xFF; DDRD = 0xE1;
	PORTC = 0x00; PORTD = 0x00;
	adc0_init();
	lcd_init();
	lcd_print("Hello World");
	_delay_ms(1000);
	lcd_clear();
	lcd_print("I am Hrudayesh");
	lcd_clear();
	_delay_ms(1000);
	lcd_print("Raw ADC Value: ");
	sendCommand(0xC0);
		
    while (1) 
    {
			value = read_adc0();
			_delay_ms(1000);
			
    }
}

