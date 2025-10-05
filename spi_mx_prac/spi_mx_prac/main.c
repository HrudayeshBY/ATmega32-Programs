//Practicing SPI master communication to Arduino UNO slave tp turn on LED graph

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>

//MACROS to turn on of the slave select lines
#define CS_ON PORTB &= ~(1<<PB4)
#define  CS_OFF PORTB |= (1<<PB4)

char msg[] = "Greetings from master!!!\n";
void SPI_init()
{
	DDRB |= (1<<PB7) | (1<<PB5) | (1<<PB4); // SCK, MOSI and SS pins
	DDRB &= ~(1<<PB6); //MISO Pin
	SPCR |= (1<<SPE) | (1<<DORD) | (1<<MSTR) | (1<<CPOL) | (1<<CPHA);
	
}

void SPI_Master_Tx(uint8_t data)
{
	uint8_t dummy = 0x00;
	SPDR = data;
	while(!(SPSR & (1<<SPIF)))
	{
		//wait for transfer of data
	}
	dummy = SPSR;
	dummy = SPDR; // by reading status and data register we can clear the SPI flag
	
}

int main(void)
{
	int len = strlen(msg);
	SPI_init();
	
	while (1)
	{
		CS_ON;
		_delay_ms(1000);
		//for(int i = 0; i < len;i++)
		//{
			//SPI_Master_Tx(msg[i]);
		//}
		SPI_Master_Tx('h');
		CS_OFF;
		_delay_ms(1000);
	}
}