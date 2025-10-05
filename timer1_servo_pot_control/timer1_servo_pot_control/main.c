#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

void adc0_init()
{
	DDRA &= ~(1<<PA0); //PA0 connected to channel 0 of ADC
	ADMUX = 0x60;
	ADCSRA = 0x87;
}

int readADC0()
{
	ADCSRA |= (1<<ADSC); //starting conversion
	while((ADCSRA & (1<<ADSC)))
	{
		
	}
	int adc_value = (ADCL >> 6) | (ADCH << 2); //ADCL value must be accessed first
	return adc_value;
}
int main(void)
{
	adc0_init();
	DDRD |= (1<<PB5);
	TCCR1A = 0x82;TCCR1B = 0x1B;
	ICR1 = 2499; TCNT1 = 0x00;
    while (1) 
    {
		OCR1A = 65 + (readADC0()/4.3513);
    }
}

