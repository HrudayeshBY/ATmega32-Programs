//I am trying to learn the cration of cutsom made libraries properly

#ifndef UART_H_
#define UART_H_
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

void UART_init();
void UART_transmit_character(char );
char UART_receive_character();
void UART_print(char*);
void UART_println(char*);

#endif /* UART_H_ */