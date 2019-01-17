#include <avr/io.h>
#include "serial.h"
#include "twi.h"


#define EEPROM		0x50


static void
mark()
{
	static uint8_t	place = 0;
	serial_block_transmit_byte(place + 0x30);
	place++;
}


static void
read_eeprom(void)
{
	uint8_t	byte;
	mark();
	if (-1 == twi_sendto(EEPROM)) {
		goto failed;
	}
	if (-1 == twi_write(0)) {
		goto failed;
	}
	if (-1 == twi_write(1)) {
		goto failed;
	}
	twi_stop();
	mark();

	serial_block_transmit_byte('*');
	return;

failed:
	serial_block_transmit_byte('!');
	return;
}


int
main(void)
{

	serial_init(9600, 0);
	serial_block_transmit_byte('>');

	twi_init_fast();
	read_eeprom();
	serial_block_transmit_byte('\r');
	serial_block_transmit_byte('\n');

	while (1) ;
}
