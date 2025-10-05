#ifndef __AT24C02_H__
#define __AT24C02_H__

#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>

#define EEPROM_ADDR 0x50
// #define EEPROM_ADDR 0x51
// #define EEPROM_ADDR 0x52
// #define EEPROM_ADDR 0x53
// #define EEPROM_ADDR 0x54
// #define EEPROM_ADDR 0x55
// #define EEPROM_ADDR 0x56
// #define EEPROM_ADDR 0x57

void uart_init();
void transmit(char a);
void uart_send_str(char *str);

void i2c_init_master();
void i2c_start();
void i2c_stop();
void i2c_write(unsigned char data);
unsigned char i2c_read();
void i2c_read_multiplr(int n);

void at24c02_write_byte(unsigned char mem_addr, unsigned char data);
unsigned char at24c02_read_byte(unsigned char mem_addr);
void at24c02_write_sequential(unsigned char mem_addr, unsigned char *str);
void at24c02_read_sequential(unsigned char mem_addr, int n);
void at24c02_erase();
void at24c02_read();

#endif