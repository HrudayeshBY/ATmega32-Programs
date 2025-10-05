#include "AT24C02.h"
#include <avr/io.h>

int main(void)
{
    unsigned char q = '\0';
    DDRD = 0x7E; PORTD &= 0x00;
    uart_init();
    i2c_init_master();
    while((PIND & (1<<7)) != 0);
    while((PIND & (1<<7)) == 0);
    uart_send_str("AT24C02 External EEPROM Testing\n\r\n\r");
    uart_send_str("Erasing External EEPROM\n\r");
    at24c02_erase();
    uart_send_str("\n\r\n\r Reading external EEPROM \n\r\n\r");
    at24c02_read();
    uart_send_str("\n\r\n\r Writing single Data to eEternal EEPROM....");
    at24c02_write_byte(0x11, 'Q');
    uart_send_str("Single Data Written\n\r\n\r Reading Single Data from external EEPROM....\n\r\n\r");
    q = at24c02_read_byte(0x11);
    uart_send_str("Data Read: ");
    trasmit(q);
    uart_send_str("\n\r\n\r Writing string to external EEPROM....");
    at24c02_write_sequential(0x30, (unsigned char *)"I ove Embedded Systems");
    uart_send_str("String Written \n\r\n\r Reading String from externa; EEPROM.....\n\r\n\r");
    at24c02_read_sequential(0x30,23);
    while (1) 
    {
    }
}

