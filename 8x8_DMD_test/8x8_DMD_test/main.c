// 8x8 DMD test, i verified the connection by checking the pcb trace 
//connecting to the corresponding pins
// I will be flashing the display by using the display test register 
//which we turn on all LED of the DMD
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

#define DISPLAY_TEST_REGISTER 0x0F
#define DECODE_MODE_REGISTER 0x09
#define SHUT_DOWN_MODE_REGISTER 0x0C

#define CS_ON PORTB &= ~(1<<PB4);
#define CS_OFF PORTB |= (1<<PB4);

void SPI_init()
{
	DDRB |= (1<<PB4) | (1<<PB5) | (1<<PB7);
	DDRB &= ~(1<<PB6); //MISO Pin
	
	SPCR |= (1<<SPE) | (1<<MSTR);
	SPSR &= ~(1<<SPI2X); // SPI clock is Fosc / 4
}

void SPI_master_tx(uint8_t data)
{
	char dummy = 0x00;
	SPDR = data;
	while(!(SPSR & (1<<SPIF)))
	{
		//wait
	}
	dummy = SPDR;
}
void DMD_register_write(uint8_t addr, uint8_t data)
{
	CS_ON;
	SPI_master_tx(addr);
	SPI_master_tx(data);
	CS_OFF;
}
int main(void)
{
	uint8_t smiley[8] = {0x00,0x66,0x66,0x00,0x42,0x28,0x18,0x00};
	uint8_t heart[8] = {0x00,0x67,0xFF,0xFF,0x7E,0x3C,0x18,0x00};
	SPI_init();
	CS_ON;
	DMD_register_write(DECODE_MODE_REGISTER,0x00);
	CS_OFF;
	_delay_ms(100);
	CS_ON;
	DMD_register_write(SHUT_DOWN_MODE_REGISTER,0x01);
	CS_OFF;
    
    while (1) 
    {
		_delay_ms(100);
		for(uint8_t i = 0x01;i <= 0x08;i++)
		{
			DMD_register_write(i,smiley[i - 1]);
			//smiley++; // incrementing the pointer
			_delay_ms(10);
		}
		_delay_ms(10000);

    }
}

