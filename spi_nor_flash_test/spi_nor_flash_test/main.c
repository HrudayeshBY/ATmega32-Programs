//SPI NOR flash test to get manufacture ID and Unique ID and print on serial monitor
#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#define CS_PIN (1<<PB4)
#define CS_ON PORTB &= ~(CS_PIN)
#define CS_OFF PORTB |= (CS_PIN)

#define JDECID 0x9F
#define UID 0x4B
#define WRITE_ENABLE_CMD 0x06
#define WRITE_DISABLE_CMD 0x50
#define READ_SR1_CMD 0x05
#define READ_SR2_CMD 0x35
#define READ_SR3_CMD 0x35
#define READ_DATA_CMD 0x03
#define PAGE_PROG_CMD 0x02

void uart_init()
{
	DDRD |= (1<<PD1); //Tx pin
	DDRD &= ~(1<<PD0); //Rx pin
	UCSRA &= ~(UCSRA);
	UCSRB |= (1<<RXEN) | (1<<TXEN);
	UCSRC |= (1<<URSEL) |(1<<UCSZ1) |(1<<UCSZ0);
	UBRRH &= ~(UBRRH);
	UBRRL = 0x33;
}

void uart_transmit(char data)
{
	UDR = data;
	while(!(UCSRA & (1<<TXC)))
	{
		//wait
	}
	_delay_ms(10);
}

void uart_print(char* str)
{
	int n = 0;
	while((str[n] != '\0'))
	{
		uart_transmit(str[n]);
		n++;
	}
	uart_transmit('\n');
	uart_transmit('\r');
}
void SPI_init()
{
	DDRB |= (1<<PB7) | (1<<PB5) | (1<<PB4);
	CS_OFF;
	SPCR |= (1<<SPE) | (1<<MSTR); //fosc/4 is the SPI clock frequency
	SPSR &= ~(1<<SPI2X);
}

void SPI_master_tx(char data)
{

	SPDR = data;
	while(!(SPSR & (1<<SPIF)))
	{
		//wait
	}

}

char SPI_master_rx(char dummy)
{
	SPDR = dummy;
	while(!(SPSR & (1<<SPIF)))
	{
		//wait
	}
	return SPDR;
	
}
void getID()
{
	char info[60];
	CS_ON;
	_delay_ms(100);
	SPI_master_tx(JDECID);
	char id[3];
	id[0] = SPI_master_rx(0x00);
	id[1] = SPI_master_rx(0x00);
	id[2] = SPI_master_rx(0x00);
	CS_OFF;
	sprintf(info,"Manufacture ID: 0x%02X, Device ID: 0x%02X%02X",id[0],id[1],id[2]);
	uart_print(info);
	
}

void readUID()
{
	// we need to send 5 dummy bytes and then receive 8 bytes of unique ID
	char id[13];
	char data[60];
	CS_ON;
	SPI_master_tx(UID);
	//dummy ids
	id[0] = SPI_master_rx(0x00);
	id[1] = SPI_master_rx(0x00);
	id[2] = SPI_master_rx(0x00);
	id[3] = SPI_master_rx(0x00);
	//Unique IDs
	id[0] = SPI_master_rx(0x00);
	id[1] = SPI_master_rx(0x00);
	id[2] = SPI_master_rx(0x00);
	id[3] = SPI_master_rx(0x00);
	id[4] = SPI_master_rx(0x00);
	id[5] = SPI_master_rx(0x00);
	id[6] = SPI_master_rx(0x00);
	id[7] = SPI_master_rx(0x00);
	CS_OFF;
	sprintf(data,"Unique ID: 0x%02X%02X%02X%02X%02X%02X%02X%02X",id[0],id[1],id[2],id[3],id[4],id[5],id[6],id[7]);
	uart_print(data);
}

void write_enable()
{
	_delay_ms(100);
	SPI_master_tx(WRITE_ENABLE_CMD);
	
}

void write_disable()
{	
	_delay_ms(100);
	SPI_master_tx(WRITE_DISABLE_CMD);
}

void read_sr1()
{
	char s1;
	char status[60];
	CS_ON;
	_delay_ms(100);
	SPI_master_tx(READ_SR1_CMD);
	s1 = SPI_master_rx(0x00);
	CS_OFF;
	sprintf(status,"SR1 Status: 0x%02X",s1);
	uart_print(status);
}

void read_sr2()
{
	char s2;
	char status[60];
	CS_ON;
	_delay_ms(100);
	SPI_master_tx(READ_SR2_CMD);
	s2 = SPI_master_rx(0x00);
	CS_OFF;
	sprintf(status,"SR2 Status: 0x%02X",s2);
	uart_print(status);	
}

void read_sr3()
{
	char s3;
	char status[60];
	CS_ON;
	_delay_ms(100);
	SPI_master_tx(READ_SR3_CMD);
	s3 = SPI_master_rx(0x00);
	CS_OFF;
	sprintf(status,"SR3 Status: 0x%02X",s3);
	uart_print(status);
}

void read_flash(char addr1, char addr2, char addr3)
{
	CS_ON;
	uart_print("Reading flash....");
	char data;
	char status[60];
	_delay_ms(100);
	SPI_master_tx(READ_DATA_CMD);
	SPI_master_tx(addr1);
	SPI_master_tx(addr2);
	SPI_master_tx(addr3);
	data = SPI_master_rx(0x00);
	CS_OFF;
	sprintf(status,"The data read is: 0x%02X",data);
	uart_print(status);
}

void write_flash(char addr1, char addr2, char addr3, char data)
{
	CS_ON;
	_delay_ms(100);
	write_enable();
	SPI_master_tx(PAGE_PROG_CMD);
	SPI_master_tx(addr1);
	SPI_master_tx(addr2);
	SPI_master_tx(addr3);
	SPI_master_tx(data);
	_delay_ms(1000);
	write_disable();
	CS_OFF;
}
int main(void)
{
    uart_init();
	SPI_init();
    while (1) 
    {
		getID();
		_delay_ms(1000);
		readUID();
		_delay_ms(1000);
		read_sr1();
		read_sr2();
		read_sr3();
		_delay_ms(1000);
		read_flash(0x12,0x11,0x17);
		_delay_ms(1000);
		write_flash(0x12,0x11,0x17,0x66);
		_delay_ms(1000);
		read_flash(0x12,0x11,0x17);
		_delay_ms(1000);
    }
}

