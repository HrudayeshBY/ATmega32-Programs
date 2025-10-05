// SPI Master with DIP switch connected to PORTC
// PINC data is sent via SPI to ATmeag328p
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define CS_ON PORTB &= ~(1<<PB4)
#define CS_OFF PORTB |= (1<<PB4)

void SPI_init()
{
	DDRB |= (1<<PB7) | (1<<PB5) | (1<<PB4);
	DDRB &= ~(1<<PB6);
	SPCR |= (1<<SPE) | (1<<MSTR); // SPI as master
	SPSR &= ~(1<<SPI2X); //F osc by 4 
}
void SPI_master_tx(uint8_t data)
{
	uint8_t dummy = 0X00;
	SPDR = data;
	while(!(SPSR & (1<<SPIF)))
	{
		//wait
	}
	dummy = SPDR; // to clear the SPIF flag we need to read the SPSR register and SPDR register
}
int main(void)
{
	DDRD = 0X00; //PORTD as input
	CS_OFF;
	PORTD = 0XFF; //internal pull up resistor enabled
	
	SPI_init();
	//SPI_master_tx();
	uint8_t value = PIND;
    while (1) 
    {
		value = PIND;
		CS_ON;
		SPI_master_tx(value);
		CS_OFF;
		_delay_ms(1000);
		
    }
}

