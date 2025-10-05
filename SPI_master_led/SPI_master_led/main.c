#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

#define CS_ON PORTB &= ~(1<<PB4)
#define CS_OFF PORTB |= (1<<PB4)

void SPI_init()
{
	DDRB |= (1<<PB4) | (1<<PB5) | (1<<PB7); //SCK, MOSI, SS
	DDRB &= ~(1<<PB6);// MISO
	SPCR |= (1<<SPE) | (1<<MSTR); // Enabled as master and SPI enabled
}

void SPI_master_tx(uint8_t data)
{
	uint8_t dummy;
	SPDR = data;
	while (!(SPSR & (1<<SPIF)))
	{
		//wait for serial transfer
	}
	dummy = SPSR;
	dummy = SPDR; // to clear the SPIF flag
}
int main(void)
{
	DDRC &= ~(0xFF);
	PORTC = 0xFF; // pull up resistor enabled
	SPI_init();
	while (1)
	{
		CS_ON;
		SPI_master_tx(PINC);
		CS_OFF;
		_delay_ms(1000);
	}
}