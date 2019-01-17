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
	uint8_t	data, status;

	mark(); // 0
	status = twi_sendto(EEPROM);
	if (status) goto failed;

	mark(); // 1
	status = twi_write(0);
	if (status) goto failed;

	mark(); // 2
	status = twi_write(1);
	if (status) goto failed;

	mark(); // 3
	twi_stop();

	mark(); // 4
	status = twi_recvfrom(EEPROM);
	if (status) goto failed;

	mark(); // 5
	status = twi_read(&data);
	if (status) goto failed;

	mark(); // 6
	twi_stop();

	serial_block_transmit_byte('*');
	return;

failed:
	twi_stop();
	serial_block_transmit_byte('!');
	serial_block_transmit_byte(status + 0x30);
	return;
}


int
main(void)
{

	serial_init(9600, 0);
	serial_block_transmit_byte('>');

	twi_init();
	read_eeprom();
	
	serial_block_transmit_byte('\r');
	serial_block_transmit_byte('\n');

	while (1) ;
}
