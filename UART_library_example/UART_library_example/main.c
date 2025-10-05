#define F_CPU 8000000UL
#include "UART.h"
#include <avr/io.h>

int main(void)
{
	UART_init();
    while (1) 
    {
		UART_transmit_character('h');
		UART_transmit_character('i');
		UART_transmit_character('I');
		UART_transmit_character('m');
		_delay_ms(1000);
		UART_println("I made a Library");
    }
}

